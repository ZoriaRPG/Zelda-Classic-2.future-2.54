
#include "../precompiled.h" //always first
#include "AST.h"
#include "UtilVisitors.h"

// ASTList

ASTList::ASTList(LocationData Loc)
		: AST(Loc), asts()
{}

ASTList::~ASTList()
{
		list<AST *>::iterator it;
		for (it = asts.begin(); it != asts.end(); it++)
		{
				delete *it;
		}
		asts.clear();
}

// ASTProgram

ASTProgram::~ASTProgram()
{
    delete decls;
}

ASTDeclList::~ASTDeclList()
{
    list<ASTDecl *>::iterator it;

    for(it = decls.begin(); it != decls.end(); it++)
    {
        delete *it;
    }

    decls.clear();
}

void ASTDeclList::addDeclaration(ASTDecl *newdecl)
{
    decls.push_front(newdecl);
}

// ASTFuncCall

ASTFuncCall::~ASTFuncCall()
{
    list<ASTExpr *>::iterator it;

    for(it = params.begin(); it != params.end(); it++)
    {
        delete *it;
    }

    params.clear();
    delete name;
}

ASTFuncId::~ASTFuncId()
{
	list<ASTType *>::iterator it;
	for (it = params.begin(); it != params.end(); it++)
	{
		delete *it;
	}

	params.clear();
}

void ASTFuncId::addParam(ASTType *param)
{
	params.push_front(param);
}

void ASTBlock::addStatement(ASTStmt *stmt)
{
    statements.push_back(stmt);
}

ASTBlock::~ASTBlock()
{
    list<ASTStmt *>::iterator it;

    for(it=statements.begin(); it != statements.end(); it++)
    {
        delete *it;
    }

    statements.clear();
}

ASTScript::~ASTScript()
{
    delete sblock;
    delete type;
}

pair<string, string> ASTFloat::parseValue()
{
    string f = getValue();
    string intpart;
    string fpart;

    switch(getType())
    {
    case TYPE_DECIMAL:
    {
        bool founddot = false;

        for(unsigned int i=0; i<f.size(); i++)
        {
            if(f.at(i) == '.')
            {
                intpart = f.substr(0, i);
                fpart = f.substr(i+1,f.size()-i-1);
                founddot = true;
                break;
            }
        }

        if(!founddot)
        {
            intpart = f;
            fpart = "";
        }

        if(negative) intpart = "-" + intpart;

        break;
    }

    case TYPE_HEX:
    {
        //trim off the "0x"
        f = f.substr(2,f.size()-2);
        //parse the hex
        long val2=0;

        for(unsigned int i=0; i<f.size(); i++)
        {
            char d = f.at(i);
            val2*=16;

            if('0' <= d && d <= '9')
                val2+=(d-'0');
            else if('A' <= d && d <= 'F')
                val2+=(10+d-'A');
            else
                val2+=(10+d-'a');
        }

        if(negative && val2 > 0) val2 *= -1;

        char temp[60];
        sprintf(temp, "%ld", val2);
        intpart = temp;
        fpart = "";
        break;
    }

    case TYPE_BINARY:
    {
        //trim off the 'b'
        f = f.substr(0,f.size()-1);
        long val2=0;

        for(unsigned int i=0; i<f.size(); i++)
        {
            char b = f.at(i);
            val2<<=1;
            val2+=b-'0';
        }

        if(negative && val2 > 0) val2 *= -1;

        char temp[60];
        sprintf(temp, "%ld", val2);
        intpart = temp;
        fpart = "";
        break;
    }
    }

    return pair<string,string>(intpart, fpart);
}

////////////////////////////////////////////////////////////////
// Function Declaration

// ASTFuncDecl

ASTFuncDecl::ASTFuncDecl(LocationData Loc)
		: ASTDecl(Loc), rettype(NULL), params(), block(NULL)
{}

ASTFuncDecl::ASTFuncDecl(ASTFuncDecl const &base)
		: ASTDecl(base.getLocation()), params()
{
		Clone c;

		base.rettype->execute(c, NULL);
		rettype = (ASTType *)c.getResult();

		name = base.name;

		for (list<ASTFuncParam *>::const_iterator it = base.params.begin(); it != base.params.end(); it++)
		{
				copyParam(*it);
		}

		base.block->execute(c, NULL);
		block = (ASTBlock *)c.getResult();
}

ASTFuncDecl::~ASTFuncDecl()
{
    delete rettype;

    list<ASTFuncParam *>::iterator it;
    for(it = params.begin(); it != params.end(); it++)
    {
        delete *it;
    }
    params.clear();

    delete block;
}

void ASTFuncDecl::copyParam(ASTFuncParam *param)
{
		Clone c;
		param->execute(c, NULL);
    params.push_back((ASTFuncParam *)c.getResult());
}

void ASTFuncDecl::copyParamList(ASTList *astlist)
{
		list<AST *> params = astlist->getList();
		list<AST *>::iterator it;
		for (it = params.begin(); it != params.end(); it++)
		{
				ASTFuncParam *param = dynamic_cast<ASTFuncParam *>(*it);
				if (param) copyParam(param);
		}
}

// ASTFuncParam

ASTFuncParam::ASTFuncParam(ASTType *Type, string Name, LocationData Loc)
		: AST(Loc), type(Type), name(Name)
{}

ASTFuncParam::ASTFuncParam(ASTFuncParam const &base)
		: AST(base.getLocation())
{
		Clone c;

		base.type->execute(c, NULL);
		type = (ASTType *)c.getResult();

		name = base.name;
}

ASTFuncParam::~ASTFuncParam()
{
		delete type;
}

////////////////////////////////////////////////////////////////
// Types

////////////////////////////////////////////////////////////////
// Variable Declaration

// ASTVarDeclList

ASTVarDeclList::ASTVarDeclList(LocationData Loc)
		: ASTDecl(Loc), type(NULL), decls()
{}

ASTVarDeclList::ASTVarDeclList(ASTVarDeclList const &base)
		: ASTDecl(base.getLocation()), decls()
{
		copyType(base.type);

		for (list<ASTVarDecl *>::const_iterator it = base.decls.begin(); it != base.decls.end(); it++)
		{
				Clone c;
				(*it)->execute(c, NULL);
				decls.push_back((ASTVarDecl *)c.getResult());
		}
}

ASTVarDeclList::~ASTVarDeclList()
{
		delete type;

    list<ASTVarDecl *>::iterator it;
    for (it = decls.begin(); it != decls.end(); it++)
    {
        delete *it;
    }
    decls.clear();
}

void ASTVarDeclList::addVarDecl(ASTVarDecl *vd)
{
		decls.push_back(vd);
		if (type) vd->copyType(type);
}

void ASTVarDeclList::copyType(ASTType *t)
{
		delete type;

		Clone c;
		t->execute(c, NULL);
		type = (ASTType *)c.getResult();

		list<ASTVarDecl *>::iterator it;
	  for (it = decls.begin(); it != decls.end(); it++)
		{
				(*it)->copyType(type);
	  }
}

// ASTVarDecl

ASTVarDecl::ASTVarDecl(string Name, LocationData Loc)
		: ASTDecl(Loc), name(Name), type(NULL)
{}

ASTVarDecl::ASTVarDecl(ASTVarDecl const &base)
		: ASTDecl(base.getLocation())
{
		copyType(base.type);
		name = base.name;
}

ASTVarDecl::~ASTVarDecl()
{
		delete type;
}

void ASTVarDecl::copyType(ASTType *t)
{
		delete type;

    Clone c;
    t->execute(c, NULL);
    type = (ASTType *)c.getResult();
}

// ASTSingleVarDecl

ASTSingleVarDecl::ASTSingleVarDecl(string Name, LocationData Loc)
		: ASTVarDecl(Name, Loc), initializer(NULL)
{}

ASTSingleVarDecl::ASTSingleVarDecl(string Name, ASTExpr *Init, LocationData Loc)
		: ASTVarDecl(Name, Loc), initializer(Init)
{}

ASTSingleVarDecl::ASTSingleVarDecl(ASTSingleVarDecl const &base)
		: ASTVarDecl(base.getName(), base.getLocation()), initializer(NULL)
{
		copyType(base.getType());

		if (base.hasInitializer())
		{
				Clone c;
				base.initializer->execute(c, NULL);
				initializer = (ASTExpr *)c.getResult();
		}
}

ASTSingleVarDecl::~ASTSingleVarDecl()
{
		delete initializer;
}

// ASTArrayDecl

ASTArrayDecl::ASTArrayDecl(string Name, ASTExpr *Size, LocationData Loc)
		: ASTVarDecl(Name, Loc), size(Size), initializer(NULL)
{}

ASTArrayDecl::ASTArrayDecl(string Name, ASTArrayInitializer *Init, LocationData Loc)
		: ASTVarDecl(Name, Loc), initializer(Init)
{
		size = new ASTNumConstant(new ASTFloat(initializer->getSize(), 0, Loc), Loc);
}

ASTArrayDecl::ASTArrayDecl(string Name, ASTExpr *Size, ASTArrayInitializer *Init, LocationData Loc)
		: ASTVarDecl(Name, Loc), size(Size), initializer(Init)
{}

ASTArrayDecl::ASTArrayDecl(ASTArrayDecl const &base)
		: ASTVarDecl(base.getName(), base.getLocation()), size(NULL), initializer(NULL)
{
		if (base.size != NULL)
		{
				Clone c;
				base.size->execute(c, NULL);
				size = (ASTExpr *)c.getResult();
		}

		if (base.initializer != NULL)
				initializer = new ASTArrayInitializer(*base.initializer);
}

ASTArrayDecl::~ASTArrayDecl()
{
    delete size;
    delete initializer;
}

// ASTArrayInitializer

ASTArrayInitializer::ASTArrayInitializer(LocationData Loc)
		: AST(Loc), elements(), _isString(false)
{}

ASTArrayInitializer::ASTArrayInitializer(ASTString *data, LocationData Loc)
		: AST(Loc), elements(), _isString(true)
{
		string s = data->getValue();
		for (unsigned int i = 1; i < s.length() - 1; i++)
				elements.push_back(new ASTNumConstant(new ASTFloat(long(s[i]), 0, Loc), Loc));
		elements.push_back(new ASTNumConstant(new ASTFloat(0L, 0, Loc), Loc));
}

ASTArrayInitializer::ASTArrayInitializer(ASTArrayInitializer const &base)
		: AST(base.getLocation()), elements(), _isString(base._isString)
{
		for (list<ASTExpr *>::const_iterator it = base.elements.begin(); it != base.elements.end(); it++)
		{
				Clone c;
				ASTExpr *expr = (ASTExpr *)(*it);
				expr->execute(c, NULL);
				addElement((ASTExpr *)c.getResult());
		}
}

ASTArrayInitializer::~ASTArrayInitializer()
{
    list<ASTExpr *>::iterator it;
    for (it = elements.begin(); it != elements.end(); it++)
    {
        delete *it;
    }
    elements.clear();
}


