
#include "../precompiled.h" //always first

#include "SymbolVisitors.h"
#include "DataStructs.h"
#include "UtilVisitors.h"
#include "ParseError.h"
#include <assert.h>

void BuildScriptSymbols::caseScript(ASTScript &host,void *param)
{
    list<ASTDecl *> ad = host.getScriptBlock()->getDeclarations();

    for(list<ASTDecl *>::iterator it = ad.begin(); it != ad.end(); it++)
    {
        (*it)->execute(*this,param);
    }
}

void BuildScriptSymbols::caseExprDot(ASTExprDot &host, void *param)
{
    pair<Scope *, SymbolTable *> *p = (pair<Scope *, SymbolTable *> *)param;
    BuildFunctionSymbols bfs;
    BFSParam newp = {p->first,p->second,ScriptParser::TYPE_VOID};
    host.execute(bfs, &newp);

    if(!bfs.isOK())
    {
        failure=true;
    }
}

void BuildScriptSymbols::caseExprArray(ASTExprArray &host, void *param)
{
    pair<Scope *, SymbolTable *> *p = (pair<Scope *, SymbolTable *> *)param;
    BuildFunctionSymbols bfs;
    BFSParam newp = {p->first,p->second,ScriptParser::TYPE_VOID};
    host.execute(bfs, &newp);

    if(!bfs.isOK())
    {
        failure=true;
    }

    host.getIndex()->execute(bfs, &newp);
}

void BuildScriptSymbols::caseExprArrow(ASTExprArrow &host, void *)
{
    printErrorMsg(&host, BADGLOBALINIT, "");
    failure=true;
}

void BuildScriptSymbols::caseFuncCall(ASTFuncCall &host, void *)
{
    printErrorMsg(&host, BADGLOBALINIT, "");
    failure=true;
}

////////////////
// Function Declaration

void BuildScriptSymbols::caseFuncDecl(ASTFuncDecl &host, void *param)
{
    pair<Scope *, SymbolTable *> *p = (pair<Scope *, SymbolTable *> *)param;
    string name = host.getName();
    list<ASTFuncParam *> params = host.getParams();
    vector<int> paramtypes;

    for(list<ASTFuncParam *>::iterator it = params.begin(); it != params.end(); it++)
    {
				ASTType *type = (*it)->getType();
				int simpleid = type->getSimpleId();
				paramtypes.push_back(simpleid);
        if(simpleid == ScriptParser::TYPE_VOID)
        {
            failure = true;
            printErrorMsg(&host, FUNCTIONVOIDPARAM, name);
        }
    }

    int rettypeid = host.getReturnType()->getSimpleId();
    int id = p->first->getFuncSymbols().addFunction(name, rettypeid, paramtypes);

    if (id == -1)
    {
        failure = true;
        printErrorMsg(&host, FUNCTIONREDEF, name);
        return;
    }

    p->second->putAST(&host, id);
    p->second->putFunc(id, rettypeid);
    p->second->putFuncDecl(id, paramtypes);
}

////////////////
// Variable Declaration

void BuildScriptSymbols::caseVarDeclList(ASTVarDeclList &host, void *param)
{
		list<ASTVarDecl *> decls = host.getDeclarations();
		for (list<ASTVarDecl *>::iterator it = decls.begin(); it != decls.end(); ++it)
		{
				ASTVarDecl *decl = *it;
				decl->execute(*this, param);
		}
}

void BuildScriptSymbols::caseSingleVarDecl(ASTSingleVarDecl &host, void *param)
{
    pair<Scope *, SymbolTable *> *p = (pair<Scope *, SymbolTable *> *)param;
		Scope *scope = p->first;
		SymbolTable *symbols = p->second;

		int type = host.getType()->getSimpleId();
    string name = host.getName();

    if (type == ScriptParser::TYPE_VOID)
    {
        failure = true;
        printErrorMsg(&host, VOIDVAR, name);
    }

    if (type == ScriptParser::TYPE_FFC || type == ScriptParser::TYPE_ITEM
				|| type == ScriptParser::TYPE_ITEMCLASS || type == ScriptParser::TYPE_NPC
				|| type == ScriptParser::TYPE_LWPN || type == ScriptParser::TYPE_EWPN)
    {
        failure = true;
        printErrorMsg(&host, REFVAR, name);
    }

    // Var is always visible
    int id = scope->getVarSymbols().addVariable(name, type);

    if(id == -1)
    {
        failure = true;
        printErrorMsg(&host, VARREDEF, name);
        return;
    }

    symbols->putAST(&host, id);
    symbols->putVar(id, type);

    if (this->deprecateGlobals)
    {
        printErrorMsg(&host, DEPRECATEDGLOBAL, name);
    }

		if (host.hasInitializer())
		{
				host.getInitializer()->execute(*this, param);
		}
}

void BuildScriptSymbols::caseArrayDecl(ASTArrayDecl &host, void *param)
{
    pair<Scope *, SymbolTable *> *p = (pair<Scope *, SymbolTable *> *)param;
		Scope *scope = p->first;
		SymbolTable *symbols = p->second;

    int type = host.getType()->getSimpleId();
    string name = host.getName();

    if (type == ScriptParser::TYPE_VOID)
    {
        failure = true;
        printErrorMsg(&host, VOIDARR, name);
    }

    if(type == ScriptParser::TYPE_FFC || type == ScriptParser::TYPE_ITEM
			 || type == ScriptParser::TYPE_ITEMCLASS || type == ScriptParser::TYPE_NPC
			 || type == ScriptParser::TYPE_LWPN || type == ScriptParser::TYPE_EWPN)
    {
        failure = true;
        printErrorMsg(&host, REFARR, name);
    }

    // Var is always visible
    int id = scope->getVarSymbols().addVariable(name, type);

    if(id == -1)
    {
        failure = true;
        printErrorMsg(&host, ARRREDEF, name);
        return;
    }

    symbols->putAST(&host, id);
    symbols->putVar(id, type);

    if (this->deprecateGlobals)
    {
        printErrorMsg(&host, DEPRECATEDGLOBAL, name);
    }

		host.getSize()->execute(*this, param);
		if (host.hasInitializer())
		{
				host.getInitializer()->execute(*this, param);
		}
}

////////////////////////////////////////////////////////////////

void BuildFunctionSymbols::caseBlock(ASTBlock &host, void *param)
{
    //push in  a new scope
    BFSParam *p = (BFSParam *)param;
    Scope *newscope = new Scope(p->scope);
    BFSParam newparam = {newscope, p->table,p->type};
    list<ASTStmt *> stmts = host.getStatements();

    for(list<ASTStmt *>::iterator it = stmts.begin(); it != stmts.end(); it++)
    {
        (*it)->execute(*this, &newparam);
    }

    delete newscope;
}

void BuildFunctionSymbols::caseStmtFor(ASTStmtFor &host, void *param)
{
    //push in new scope
    //in accordance with C++ scoping
    BFSParam *p = (BFSParam *)param;
    Scope *newscope = new Scope(p->scope);
    BFSParam newparam = {newscope, p->table, p->type};
    host.getPrecondition()->execute(*this, &newparam);
    host.getTerminationCondition()->execute(*this, &newparam);
    host.getIncrement()->execute(*this, &newparam);
    ASTStmt * stmt = host.getStmt();

    stmt->execute(*this,&newparam);
    delete newscope;
}

void BuildFunctionSymbols::caseFuncCall(ASTFuncCall &host, void *param)
{
    BFSParam *p = (BFSParam *)param;
    ASTExpr *ident = host.getName();
    //ident could be a dotexpr, or an arrow exp.
    //if an arrow exp, it is not my problem right now
    bool isdot = false;
    IsDotExpr temp;
    ident->execute(temp, &isdot);

    if(!isdot)
    {
        //recur to get any dotexprs inside
        ident->execute(*this,param);
				host.setIsVar(false);
    }
    else
    {
        // Find functions matching name.
        ASTExprDot *dotname = (ASTExprDot *)host.getName();
        string name = dotname->getName();
        string nspace = dotname->getNamespace();
        vector<int> possibleFuncs = p->scope->getFuncsInScope(nspace, name);

				// There's at least one function matching the name, so store them for later.
				if(possibleFuncs.size() > 0)
				{
					p->table->putAmbiguousFunc(&host, possibleFuncs);
					host.setIsVar(false);
				}
				// There aren't any functions with that name.
				else
				{
					// Check for a variable.
					int var_id = p->scope->getVarInScope(nspace, name);
					if (var_id != -1)
					{
						p->table->putAST(&host, var_id);
						host.setIsVar(true);
					}
					else
					{
            string fullname;

            if(nspace == "")
							fullname=name;
            else
							fullname = nspace + "." + name;

            printErrorMsg(&host, FUNCUNDECLARED, fullname);
            failure = true;
            return;
					}

				}

    }

    for(list<ASTExpr *>::iterator it = host.getParams().begin(); it != host.getParams().end(); it++)
    {
        (*it)->execute(*this,param);
    }
}

void BuildFunctionSymbols::caseFuncId(ASTFuncId &host, void *param)
{
	BFSParam *p = (BFSParam *)param;
	vector<int> possibleFuncs = p->scope->getFuncsInScope("", host.getName());

	if (possibleFuncs.size() == 0)
	{
		printErrorMsg(&host, FUNCUNDECLARED, host.getName());
		failure = true;
		return;
	}

	p->table->putAmbiguousFunc(&host, possibleFuncs);
}

void BuildFunctionSymbols::caseExprDot(ASTExprDot &host, void *param)
{
    BFSParam *p = (BFSParam *)param;
    string name = host.getName();
    string nspace = host.getNamespace();
    int id = p->scope->getVarInScope(nspace, name);

    if(id == -1 && !(nspace == "" && p->table->isConstant(name)))
    {
        string fullname;

        if(nspace == "")
            fullname=name;
        else
            fullname = nspace + "." + name;

        printErrorMsg(&host, VARUNDECLARED, fullname);
        failure = true;
        return;
    }

    p->table->putAST(&host, id);
}

void BuildFunctionSymbols::caseExprArrow(ASTExprArrow &host, void *param)
{
    //recur on the name
    host.getLVal()->execute(*this,param);

    //recur on the index, if it exists
    if(host.getIndex())
        host.getIndex()->execute(*this,param);

    //wait for type-checking to do rest of work
}

void BuildFunctionSymbols::caseExprArray(ASTExprArray &host, void *param)
{
    BFSParam *p = (BFSParam *)param;
    string name = host.getName();
    string nspace = host.getNamespace();
    int id = p->scope->getVarInScope(nspace, name);

    if(id == -1 && !(nspace == "" && p->table->isConstant(name)))
    {
        string fullname;

        if(nspace == "")
            fullname=name;
        else
            fullname = nspace + "." + name;

        printErrorMsg(&host, VARUNDECLARED, fullname);
        failure = true;
        return;
    }

    p->table->putAST(&host, id);

    if(host.getIndex())
        host.getIndex()->execute(*this,param);
}

////////////////
// Function Declaration

void BuildFunctionSymbols::caseFuncDecl(ASTFuncDecl &host, void *param)
{
    BFSParam *p = (BFSParam *)param;

    // Push in the scope
    Scope *subscope = new Scope(p->scope);
    BFSParam subparam = {subscope, p->table, p->type};

    // If it's a run method, add this.
		int type = host.getReturnType()->getSimpleId();
    if (host.getName() == "run" && type == ScriptParser::TYPE_VOID)
    {
        thisvid = subscope->getVarSymbols().addVariable("this", p->type);
        subparam.table->putVar(thisvid, p->type);
    }

    // Add the params.
    list<ASTFuncParam *> params = host.getParams();
    for (list<ASTFuncParam *>::iterator it = params.begin(); it != params.end(); it++)
    {
				ASTFuncParam *fp = *it;
        int type = fp->getType()->getSimpleId();
        string name = fp->getName();
        int id = subscope->getVarSymbols().addVariable(name, type);

        if(id == -1)
        {
            printErrorMsg(fp, VARREDEF, name);
            failure = true;
            delete subscope;
            return;
        }

        p->table->putVar(id, type);
        p->table->putAST(fp, id);
    }

    // Shortcut the block
    list<ASTStmt *> stmts = host.getBlock()->getStatements();
    for(list<ASTStmt *>::iterator it = stmts.begin(); it != stmts.end(); it++)
    {
        (*it)->execute(*this, &subparam);
    }

    delete subscope;
}

////////////////
// Variable Declaration

void BuildFunctionSymbols::caseVarDeclList(ASTVarDeclList &host, void *param)
{
		list<ASTVarDecl *> decls = host.getDeclarations();
		for (list<ASTVarDecl *>::iterator it = decls.begin(); it != decls.end(); ++it)
		{
				ASTVarDecl *decl = *it;
				decl->execute(*this, param);
		}
}

void BuildFunctionSymbols::caseSingleVarDecl(ASTSingleVarDecl &host, void *param)
{
    BFSParam *p = (BFSParam *)param;
    int type = host.getType()->getSimpleId();
    string name = host.getName();
    int id = p->scope->getVarSymbols().addVariable(name, type);

    if(id == -1)
    {
        printErrorMsg(&host, VARREDEF, name);
        failure = true;
        return;
    }

    p->table->putAST(&host, id);
    p->table->putVar(id, type);

		if (host.hasInitializer())
		{
				host.getInitializer()->execute(*this, param);
		}
}

void BuildFunctionSymbols::caseArrayDecl(ASTArrayDecl &host, void *param)
{
    BFSParam *p = (BFSParam *)param;
    int type = host.getType()->getSimpleId();
    string name = host.getName();
    int id = p->scope->getVarSymbols().addVariable(name, type);

    if(id == -1)
    {
        printErrorMsg(&host, ARRREDEF, name);
        failure = true;
        return;
    }

    p->table->putAST(&host, id);
    p->table->putVar(id, type);

    host.getSize()->execute(*this, param);

		if (host.hasInitializer())
		{
				host.getInitializer()->execute(*this, param);
		}
}

