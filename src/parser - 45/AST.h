#ifndef AST_H
#define AST_H

class AST;
// for flex and bison
#define YYSTYPE AST*

#include "y.tab.hpp"
#include "Compiler.h"
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

#define RECURSIONLIMIT 30

extern string curfilename;
int go(const char *f);

class ASTScript;
class ASTImportDecl;
class ASTConstDecl;
class ASTFloat;
class ASTString;
class ASTProgram;
class ASTDeclList;
class ASTDecl;
class ASTType;
class ASTBlock;
class ASTExpr;
class ASTExprAnd;
class ASTExprOr;
class ASTExprGT;
class ASTExprGE;
class ASTExprLT;
class ASTExprLE;
class ASTExprEQ;
class ASTExprNE;
class ASTExprPlus;
class ASTExprMinus;
class ASTExprTimes;
class ASTExprDivide;
class ASTExprNot;
class ASTExprNegate;
class ASTExprArrow;
class ASTExprArray;
class ASTNumConstant;
class ASTFuncCall;
class ASTFuncId;
class ASTBoolConstant;
class ASTBlock;
class ASTStmt;
class ASTStmtAssign;
class ASTExprDot;
class ASTStmtFor;
class ASTStmtIf;
class ASTStmtIfElse;
class ASTStmtReturn;
class ASTStmtReturnVal;
class ASTStmtEmpty;
class ASTScript;
class ASTStmtWhile;
class ASTStmtDo;
class ASTExprBitOr;
class ASTExprBitAnd;
class ASTExprBitXor;
class ASTExprLShift;
class ASTExprRShift;
class ASTExprModulo;
class ASTExprBitNot;
class ASTExprIncrement;
class ASTExprPreIncrement;
class ASTExprDecrement;
class ASTExprPreDecrement;
class ASTStmtBreak;
class ASTStmtContinue;
// Types
class ASTTypeVoid;
class ASTTypeGlobal;
class ASTTypeFloat;
class ASTTypeBool;
class ASTTypeFFC;
class ASTTypeItem;
class ASTTypeItemclass;
class ASTTypeNPC;
class ASTTypeLWpn;
class ASTTypeEWpn;
// Function Declaration
class ASTFuncDecl;
class ASTFuncParam;
// Variable Declaration
class ASTVarDeclList;
class ASTVarDecl;
class ASTSingleVarDecl;
class ASTArrayDecl;
class ASTArrayInitializer;

class ASTVisitor
{
public:
    virtual void caseDefault(void *param) = 0;
    virtual void caseProgram(ASTProgram &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseFloat(ASTFloat &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseString(ASTString &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseDeclList(ASTDeclList &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseImportDecl(ASTImportDecl &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseConstDecl(ASTConstDecl &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprAnd(ASTExprAnd &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprOr(ASTExprOr &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprGT(ASTExprGT &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprGE(ASTExprGE &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprLT(ASTExprLT &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprLE(ASTExprLE &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprEQ(ASTExprEQ &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprNE(ASTExprNE &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprPlus(ASTExprPlus &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprMinus(ASTExprMinus &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprTimes(ASTExprTimes &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprDivide(ASTExprDivide &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprNot(ASTExprNot &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprArrow(ASTExprArrow &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprArray(ASTExprArray &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprNegate(ASTExprNegate &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseNumConstant(ASTNumConstant &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseFuncCall(ASTFuncCall &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseFuncId(ASTFuncId &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseBoolConstant(ASTBoolConstant &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseBlock(ASTBlock &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtAssign(ASTStmtAssign &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprDot(ASTExprDot &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtFor(ASTStmtFor &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtIf(ASTStmtIf &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtIfElse(ASTStmtIfElse &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtReturn(ASTStmtReturn &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtReturnVal(ASTStmtReturnVal &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtEmpty(ASTStmtEmpty &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseScript(ASTScript &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtWhile(ASTStmtWhile &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtDo(ASTStmtDo &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprBitOr(ASTExprBitOr &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprBitXor(ASTExprBitXor &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprBitAnd(ASTExprBitAnd &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprLShift(ASTExprLShift &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprRShift(ASTExprRShift &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprBitNot(ASTExprBitNot &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprIncrement(ASTExprIncrement &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprPreIncrement(ASTExprPreIncrement &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprDecrement(ASTExprDecrement &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprPreDecrement(ASTExprPreDecrement &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseExprModulo(ASTExprModulo &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtBreak(ASTStmtBreak &, void *param)
    {
        caseDefault(param);
    }
    virtual void caseStmtContinue(ASTStmtContinue &, void *param)
    {
        caseDefault(param);
    }
    virtual ~ASTVisitor() {}
		// Types
    virtual void caseTypeVoid(ASTTypeVoid &, void *param) {caseDefault(param);}
    virtual void caseTypeGlobal(ASTTypeGlobal &, void *param) {caseDefault(param);}
    virtual void caseTypeFloat(ASTTypeFloat &, void *param) {caseDefault(param);}
    virtual void caseTypeBool(ASTTypeBool &, void *param) {caseDefault(param);}
    virtual void caseTypeFFC(ASTTypeFFC &, void *param) {caseDefault(param);}
    virtual void caseTypeItem(ASTTypeItem &, void *param) {caseDefault(param);}
    virtual void caseTypeItemclass(ASTTypeItemclass &, void *param) {caseDefault(param);}
    virtual void caseTypeNPC(ASTTypeNPC &, void *param) {caseDefault(param);}
    virtual void caseTypeLWpn(ASTTypeLWpn &, void *param) {caseDefault(param);}
    virtual void caseTypeEWpn(ASTTypeEWpn &, void *param) {caseDefault(param);}
		// Function Declaration
    virtual void caseFuncDecl(ASTFuncDecl &, void *param) {caseDefault(param);}
    virtual void caseFuncParam(ASTFuncParam &, void *param) {caseDefault(param);}
		// Variable Declaration
		virtual void caseVarDeclList(ASTVarDeclList &, void *param) {caseDefault(param);}
    virtual void caseSingleVarDecl(ASTSingleVarDecl &, void *param) {caseDefault(param);}
    virtual void caseArrayDecl(ASTArrayDecl &, void *param) {caseDefault(param);}
    virtual void caseArrayInitializer(ASTArrayInitializer &, void *param) {caseDefault(param);}
};

//////////////////////////////////////////////////////////////////////////////
class LocationData
{
public:
    LocationData(YYLTYPE loc)
    {
        first_line = loc.first_line;
        last_line = loc.last_line;
        first_column = loc.first_column;
        last_column = loc.last_column;
        fname = curfilename;
    }
    int first_line;
    int last_line;
    int first_column;
    int last_column;
    string fname;
};
//////////////////////////////////////////////////////////////////////////////
class AST
{
public:
    AST(LocationData Loc) : loc(Loc) {}
    virtual void execute(ASTVisitor &visitor, void *param) = 0;
    virtual ~AST() {}
    LocationData const &getLocation() const {return loc;}
private:
    LocationData loc;
};

// Helper class for AST construction - not part of final AST.
class ASTList : public AST
{
public:
		ASTList(LocationData Loc);
		~ASTList();
		list<AST *> &getList() {return asts;}
		void addAST(AST* ast) {asts.push_back(ast);}
		void execute(ASTVisitor &, void *) {}
private:
		list<AST *> asts;
};

class ASTStmt : public AST
{
public:
    ASTStmt(LocationData Loc) : AST(Loc) {}
    virtual ~ASTStmt() {}
};

class ASTProgram : public AST
{
public:
    ASTProgram(ASTDeclList *Decls, LocationData Loc) : AST(Loc), decls(Decls) {};

    ASTDeclList *getDeclarations()
    {
        return decls;
    }

    ~ASTProgram();

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseProgram(*this,param);
    }
private:
    ASTDeclList *decls;
};

class ASTFloat : public AST
{
public:
    ASTFloat(char *Value, int Type, LocationData Loc) : AST(Loc), type(Type), negative(false)
    {
        val = string(Value);
    }
    ASTFloat(const char *Value, int Type, LocationData Loc) : AST(Loc), type(Type), negative(false)
    {
        val = string(Value);
    }
    ASTFloat(long Value, int Type, LocationData Loc) : AST(Loc), type(Type), negative(false)
    {
        char tmp[15];
        sprintf(tmp, "%ld", Value);
        val = string(tmp);
    }
    string getValue()
    {
        return val;
    }
    pair<string,string> parseValue();
    int getType()
    {
        return type;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseFloat(*this, param);
    }
    void set_negative(bool neg)
    {
        negative = neg;
    }
    static const int TYPE_DECIMAL=0;
    static const int TYPE_BINARY=1;
    static const int TYPE_HEX=2;
private:
    int type;
    string val;
    bool negative;
};

class ASTString : public AST
{
public:
    ASTString(const char *strval, LocationData Loc) : AST(Loc)
    {
        str = string(strval);
    }
    string getValue()
    {
        return str;
    }

    void execute(ASTVisitor &visitor, void *param)
    {
        return visitor.caseString(*this,param);
    }
private:
    string str;
};

class ASTDeclList : public AST
{
public:
    ASTDeclList(LocationData Loc) : AST(Loc), decls() {}
    ~ASTDeclList();

    void addDeclaration(ASTDecl *newdecl);

    list<ASTDecl *> &getDeclarations() {return decls;}

    void execute(ASTVisitor &visitor, void *param) {visitor.caseDeclList(*this, param);}
private:
    list<ASTDecl *> decls;
};

class ASTDecl : public ASTStmt
{
public:
    ASTDecl(LocationData Loc) : ASTStmt(Loc) {}
    virtual ~ASTDecl() {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTDecl(ASTDecl &);
    ASTDecl &operator=(ASTDecl &);
};

class ASTImportDecl : public ASTDecl
{
public:
    ASTImportDecl(string file, LocationData Loc) : ASTDecl(Loc), filename(file) {}

    string getFilename()
    {
        return filename;
    }

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseImportDecl(*this,param);
    }
private:
    string filename;
    //NOT IMPLEMENTED; DO NOT USE
    ASTImportDecl(ASTImportDecl &);
    ASTImportDecl &operator=(ASTImportDecl &);
};

class ASTConstDecl : public ASTDecl
{
public:
    ASTConstDecl(string Name, ASTFloat *Val, LocationData Loc) : ASTDecl(Loc), name(Name), val(Val) {}
    string getName()
    {
        return name;
    }
    ASTFloat *getValue()
    {
        return val;
    }
    ~ASTConstDecl()
    {
        delete val;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseConstDecl(*this,param);
    }
private:
    string name;
    ASTFloat *val;
    //NOT IMPLEMENTED; DO NOT USE
    ASTConstDecl(ASTConstDecl &);
    ASTConstDecl &operator=(ASTConstDecl &);
};

class ASTExpr : public ASTStmt
{
public:
	  ASTExpr(LocationData Loc) : ASTStmt(Loc), hasval(false), constonly(false), intval(0), type(-1) {}
    virtual ~ASTExpr() {}
    long getIntValue()
    {
        return intval;
    }
    bool hasIntValue()
    {
        return hasval;
    }
    int getType()
    {
        return type;
    }
    void setIntValue(long val)
    {
        hasval = true;
        intval=val;
    }
    void setType(int t)
    {
        type=t;
    }
		void forceConstant()
		{
			  constonly = true;
		}
		bool isConstantOnly()
		{
		    return constonly;
		}
private:
    bool hasval;
    long intval;
    int type;
		bool constonly;
    //NOT IMPLEMENTED; DO NOT USE
    ASTExpr(ASTExpr &);
    ASTExpr &operator=(ASTExpr &);
};

class ASTUnaryExpr : public ASTExpr
{
public:
    ASTUnaryExpr(LocationData Loc) : ASTExpr(Loc) {}
    virtual ~ASTUnaryExpr()
    {
        delete operand;
    }

    void setOperand(ASTExpr *e)
    {
        operand=e;
    }
    ASTExpr *getOperand()
    {
        return operand;
    }
private:
    ASTExpr *operand;
    //NOT IMPLEMENTED; DO NOT USE
    ASTUnaryExpr(ASTUnaryExpr &);
    ASTUnaryExpr&operator=(ASTUnaryExpr&);
};

class ASTBinaryExpr : public ASTExpr
{
public:
    ASTBinaryExpr(LocationData Loc) : ASTExpr(Loc) {}
    virtual ~ASTBinaryExpr()
    {
        delete first;
        delete second;
    }
    void setFirstOperand(ASTExpr *e)
    {
        first=e;
    }
    void setSecondOperand(ASTExpr *e)
    {
        second=e;
    }
    ASTExpr *getFirstOperand()
    {
        return first;
    }
    ASTExpr *getSecondOperand()
    {
        return second;
    }
private:
    ASTExpr *first;
    ASTExpr *second;
};

class ASTLogExpr : public ASTBinaryExpr
{
public:
    ASTLogExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTLogExpr(ASTLogExpr &);
    ASTLogExpr &operator=(ASTLogExpr &);
};

class ASTBitExpr : public ASTBinaryExpr
{
public:
    ASTBitExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTBitExpr &operator=(ASTBitExpr &);
    ASTBitExpr(ASTBitExpr &);
};

class ASTShiftExpr : public ASTBinaryExpr
{
public:
    ASTShiftExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTShiftExpr(ASTShiftExpr &);
    ASTShiftExpr &operator=(ASTShiftExpr &);
};

class ASTExprAnd : public ASTLogExpr
{
public:
    ASTExprAnd(LocationData Loc) : ASTLogExpr(Loc) {}

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprAnd(*this,param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTExprAnd(ASTExprAnd &);
    ASTExprAnd &operator=(ASTExprAnd &);
};

class ASTExprOr : public ASTLogExpr
{
public:
    ASTExprOr(LocationData Loc) : ASTLogExpr(Loc) {}

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprOr(*this,param);
    }
};

class ASTRelExpr : public ASTBinaryExpr
{
public:
    ASTRelExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTRelExpr(ASTRelExpr &);
    ASTRelExpr &operator=(ASTRelExpr&);
};

class ASTExprGT : public ASTRelExpr
{
public:
    ASTExprGT(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprGT(*this, param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTExprGT(ASTExprGT &);
    ASTExprGT &operator=(ASTExprGT &);
};

class ASTExprGE : public ASTRelExpr
{
public:
    ASTExprGE(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprGE(*this, param);
    }
};

class ASTExprLT : public ASTRelExpr
{
public:
    ASTExprLT(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprLT(*this, param);
    }
};

class ASTExprLE : public ASTRelExpr
{
public:
    ASTExprLE(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprLE(*this, param);
    }
};

class ASTExprEQ : public ASTRelExpr
{
public:
    ASTExprEQ(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprEQ(*this, param);
    }
};

class ASTExprNE : public ASTRelExpr
{
public:
    ASTExprNE(LocationData Loc) : ASTRelExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprNE(*this, param);
    }
};

class ASTAddExpr : public ASTBinaryExpr
{
public:
    ASTAddExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTAddExpr(ASTAddExpr &);
    ASTAddExpr &operator=(ASTAddExpr &);
};

class ASTExprPlus : public ASTAddExpr
{
public:
    ASTExprPlus(LocationData Loc) : ASTAddExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprPlus(*this,param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTExprPlus(ASTExprPlus &);
    ASTExprPlus &operator=(ASTExprPlus &);
};

class ASTExprMinus : public ASTAddExpr
{
public:
    ASTExprMinus(LocationData Loc) : ASTAddExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprMinus(*this, param);
    }
};

class ASTMultExpr : public ASTBinaryExpr
{
public:
    ASTMultExpr(LocationData Loc) : ASTBinaryExpr(Loc) {}
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTMultExpr(ASTMultExpr &);
    ASTMultExpr &operator=(ASTMultExpr &);
};

class ASTExprTimes : public ASTMultExpr
{
public:
    ASTExprTimes(LocationData Loc) : ASTMultExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprTimes(*this, param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTExprTimes(ASTExprTimes &);
    ASTExprTimes &operator=(ASTExprTimes &);
};

class ASTExprDivide : public ASTMultExpr
{
public:
    ASTExprDivide(LocationData Loc) : ASTMultExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprDivide(*this,param);
    }
};

class ASTExprBitOr : public ASTBitExpr
{
public:
    ASTExprBitOr(LocationData Loc) : ASTBitExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprBitOr(*this,param);
    }
};

class ASTExprBitXor : public ASTBitExpr
{
public:
    ASTExprBitXor(LocationData Loc) : ASTBitExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprBitXor(*this,param);
    }
};

class ASTExprBitAnd : public ASTBitExpr
{
public:
    ASTExprBitAnd(LocationData Loc) : ASTBitExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprBitAnd(*this,param);
    }
};

class ASTExprLShift : public ASTShiftExpr
{
public:
    ASTExprLShift(LocationData Loc) : ASTShiftExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprLShift(*this,param);
    }
};

class ASTExprRShift : public ASTShiftExpr
{
public:
    ASTExprRShift(LocationData Loc) : ASTShiftExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprRShift(*this,param);
    }
};

class ASTExprNegate : public ASTUnaryExpr
{
public:
    ASTExprNegate(LocationData Loc) : ASTUnaryExpr(Loc) {}

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprNegate(*this,param);
    }
};

class ASTExprNot : public ASTUnaryExpr
{
public:
    ASTExprNot(LocationData Loc) : ASTUnaryExpr(Loc) {}

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprNot(*this,param);
    }
};

class ASTExprBitNot : public ASTUnaryExpr
{
public:
    ASTExprBitNot(LocationData Loc) : ASTUnaryExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprBitNot(*this,param);
    }
};

class ASTExprIncrement : public ASTUnaryExpr
{
public:
    ASTExprIncrement(LocationData Loc) : ASTUnaryExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprIncrement(*this,param);
    }
};

class ASTExprPreIncrement : public ASTUnaryExpr
{
public:
    ASTExprPreIncrement(LocationData Loc) : ASTUnaryExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprPreIncrement(*this,param);
    }
};

class ASTExprDecrement : public ASTUnaryExpr
{
public:
    ASTExprDecrement(LocationData Loc) : ASTUnaryExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprDecrement(*this,param);
    }
};

class ASTExprPreDecrement : public ASTUnaryExpr
{
public:
    ASTExprPreDecrement(LocationData Loc) : ASTUnaryExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprPreDecrement(*this,param);
    }
};

class ASTExprModulo : public ASTMultExpr
{
public:
    ASTExprModulo(LocationData Loc) : ASTMultExpr(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprModulo(*this,param);
    }
};

class ASTNumConstant : public ASTExpr
{
public:
    ASTNumConstant(ASTFloat *value, LocationData Loc) : ASTExpr(Loc), val(value) {}

    ASTFloat *getValue()
    {
        return val;
    }

    ~ASTNumConstant()
    {
        delete val;
    }

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseNumConstant(*this,param);
    }
private:
    ASTFloat *val;
};

class ASTFuncCall : public ASTExpr
{
public:
    ASTFuncCall(LocationData Loc) : ASTExpr(Loc), params() {}

    list<ASTExpr *> &getParams()
    {
        return params;
    }

    void setName(ASTExpr *n)
    {
        name=n;
    }
    ASTExpr * getName()
    {
        return name;
    }
    void addParam(ASTExpr *param)
    {
        params.push_front(param);
    }

		bool getIsVar()
		{
			return isVar;
		}
		void setIsVar(bool value)
		{
			isVar = value;
		}

    ~ASTFuncCall();

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseFuncCall(*this,param);
    }
private:
    ASTExpr *name;
    list<ASTExpr *> params;
		bool isVar = false;
};

class ASTFuncId : public ASTExpr
{
public:
	ASTFuncId(string Name, LocationData Loc) : ASTExpr(Loc), name(Name), params() {}
	ASTFuncId(LocationData Loc) : ASTExpr(Loc), params() {}
	~ASTFuncId();

	string getName()
	{
		return name;
	}
	void setName(string n)
	{
		name = n;
	}

	void addParam(ASTType *param);
	list<ASTType *> &getParams()
	{
		return params;
	}

	void execute(ASTVisitor &visitor, void *param)
	{
		visitor.caseFuncId(*this,param);
	}
private:
	string name;
	list<ASTType *> params;
};

class ASTBoolConstant : public ASTExpr
{
public:
    ASTBoolConstant(bool Value, LocationData Loc) : ASTExpr(Loc), value(Value) {}
    bool getValue()
    {
        return value;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseBoolConstant(*this, param);
    }
private:
    bool value;
};

class ASTBlock : public ASTStmt
{
public:
    ASTBlock(LocationData Loc) : ASTStmt(Loc), statements() {}
    ~ASTBlock();

    list<ASTStmt *> &getStatements()
    {
        return statements;
    }
    list<long> *getArrayRefs()
    {
        return &arrayRefs;
    }
    void addStatement(ASTStmt *Stmt);

    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseBlock(*this,param);
    }
private:
    list<ASTStmt *> statements;
    list<long> arrayRefs;
    //NOT IMPLEMENTED; DO NOT USE
    ASTBlock(ASTBlock &);
    ASTBlock &operator=(ASTBlock &);
};

class ASTStmtAssign : public ASTStmt
{
public:
    ASTStmtAssign(ASTStmt *Lval, ASTExpr *Rval, LocationData Loc) : ASTStmt(Loc), lval(Lval), rval(Rval) {}
    ASTStmt *getLVal()
    {
        return lval;
    }
    ASTExpr *getRVal()
    {
        return rval;
    }
    ~ASTStmtAssign()
    {
        delete lval;
        delete rval;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtAssign(*this,param);
    }
private:
    ASTStmt *lval;
    ASTExpr *rval;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtAssign(ASTStmtAssign &);
    ASTStmtAssign &operator=(ASTStmtAssign &);
};

class ASTExprDot : public ASTExpr
{
public:
    ASTExprDot(string Nspace, string Name, LocationData Loc) : ASTExpr(Loc), name(Name), nspace(Nspace) {}
    string getName()
    {
        return name;
    }
    string getNamespace()
    {
        return nspace;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprDot(*this,param);
    }
private:
    string name;
    string nspace;
};

class ASTExprArrow : public ASTExpr
{
public:
    ASTExprArrow(ASTExpr *Lval, string Rval, LocationData Loc) : ASTExpr(Loc), lval(Lval), rval(Rval), index(NULL) {}
    string getName()
    {
        return rval;
    }
    ASTExpr *getLVal()
    {
        return lval;
    }
    ~ASTExprArrow()
    {
        delete lval;

        if(index) delete index;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprArrow(*this,param);
    }
    ASTExpr *getIndex()
    {
        return index;
    }
    void setIndex(ASTExpr *e)
    {
        index = e;
    }
private:
    ASTExpr *lval;
    string rval;
    ASTExpr *index;
};

class ASTExprArray : public ASTExpr
{
public:
    ASTExprArray(string Nspace, string Name, LocationData Loc) : ASTExpr(Loc), name(Name), index(NULL), nspace(Nspace) {}
    string getName()
    {
        return name;
    }
    string getNamespace()
    {
        return nspace;
    }
    ~ASTExprArray()
    {
        if(index) delete index;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseExprArray(*this,param);
    }
    ASTExpr *getIndex()
    {
        return index;
    }
    void setIndex(ASTExpr *e)
    {
        index = e;
    }
private:
    string name;
    ASTExpr *index;
    string nspace;
};

class ASTStmtFor : public ASTStmt
{
public:
    ASTStmtFor(ASTStmt *Prec, ASTExpr *Term, ASTStmt *Incr, ASTStmt *Stmt, LocationData Loc) :
        ASTStmt(Loc), prec(Prec), term(Term), incr(Incr), stmt(Stmt) {}
    ~ASTStmtFor()
    {
        delete prec;
        delete term;
        delete incr;
        delete stmt;
    }
    ASTStmt *getPrecondition()
    {
        return prec;
    }
    ASTExpr *getTerminationCondition()
    {
        return term;
    }
    ASTStmt *getIncrement()
    {
        return incr;
    }
    ASTStmt *getStmt()
    {
        return stmt;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        return visitor.caseStmtFor(*this,param);
    }
private:
    ASTStmt *prec;
    ASTExpr *term;
    ASTStmt *incr;
    ASTStmt *stmt;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtFor(ASTStmtFor &);
    ASTStmtFor &operator=(ASTStmtFor &);
};

class ASTStmtIf : public ASTStmt
{
public:
    ASTStmtIf(ASTExpr *Cond, ASTStmt *Stmt, LocationData Loc) : ASTStmt(Loc), cond(Cond), stmt(Stmt) {}
    ASTExpr *getCondition()
    {
        return cond;
    }
    ASTStmt *getStmt()
    {
        return stmt;
    }
    virtual ~ASTStmtIf()
    {
        delete cond;
        delete stmt;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        return visitor.caseStmtIf(*this,param);
    }
private:
    ASTExpr *cond;
    ASTStmt *stmt;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtIf(ASTStmtIf &);
    ASTStmtIf &operator=(ASTStmtIf &);
};

class ASTStmtIfElse : public ASTStmtIf
{
public:
    ASTStmtIfElse(ASTExpr *Cond, ASTStmt *Ifstmt, ASTStmt *Elsestmt, LocationData Loc) :
        ASTStmtIf(Cond,Ifstmt,Loc), elsestmt(Elsestmt) {}
    ~ASTStmtIfElse()
    {
        delete elsestmt;
    }
    ASTStmt *getElseStmt()
    {
        return elsestmt;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtIfElse(*this, param);
    }
private:
    ASTStmt *elsestmt;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtIfElse(ASTStmtIfElse &);
    ASTStmtIfElse &operator=(ASTStmtIfElse &);
};

class ASTStmtReturn : public ASTStmt
{
public:
    ASTStmtReturn(LocationData Loc) : ASTStmt(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtReturn(*this, param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtReturn(ASTStmtReturn &);
    ASTStmtReturn &operator=(ASTStmtReturn &);
};

class ASTStmtReturnVal : public ASTStmt
{
public:
    ASTStmtReturnVal(ASTExpr *Retval, LocationData Loc) : ASTStmt(Loc), retval(Retval) {}
    ASTExpr *getReturnValue()
    {
        return retval;
    }
    ~ASTStmtReturnVal()
    {
        delete retval;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtReturnVal(*this,param);
    }
private:
    ASTExpr *retval;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtReturnVal(ASTStmtReturnVal &);
    ASTStmtReturnVal &operator=(ASTStmtReturnVal &);
};

class ASTStmtBreak : public ASTStmt
{
public:
    ASTStmtBreak(LocationData Loc) : ASTStmt(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtBreak(*this,param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtBreak(ASTStmtBreak &);
    ASTStmtBreak &operator=(ASTStmtBreak &);
};

class ASTStmtContinue : public ASTStmt
{
public:
    ASTStmtContinue(LocationData Loc) : ASTStmt(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtContinue(*this, param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtContinue(ASTStmtContinue &);
    ASTStmtContinue &operator=(ASTStmtContinue &);
};

class ASTStmtEmpty : public ASTStmt
{
public:
    ASTStmtEmpty(LocationData Loc) : ASTStmt(Loc) {}
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtEmpty(*this, param);
    }
private:
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtEmpty(ASTStmtEmpty &);
    ASTStmtEmpty &operator=(ASTStmtEmpty&);
};

class ASTScript : public ASTDecl
{
public:
    ASTScript(ASTType *Type, string Name, ASTDeclList *Sblock, LocationData Loc) : ASTDecl(Loc), type(Type), name(Name), sblock(Sblock) {}
    ~ASTScript();
    ASTDeclList *getScriptBlock()
    {
        return sblock;
    }
    ASTType *getType()
    {
        return type;
    }
    string getName()
    {
        return name;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseScript(*this,param);
    }
private:
    ASTType *type;
    string name;
    ASTDeclList *sblock;
};

class ASTStmtWhile : public ASTStmt
{
public:
    ASTStmtWhile(ASTExpr *Cond, ASTStmt *Stmt, LocationData Loc) : ASTStmt(Loc), cond(Cond), stmt(Stmt) {}
    ~ASTStmtWhile()
    {
        delete cond;
        delete stmt;
    }
    ASTExpr *getCond()
    {
        return cond;
    }
    ASTStmt *getStmt()
    {
        return stmt;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtWhile(*this,param);
    }
private:
    ASTExpr *cond;
    ASTStmt *stmt;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtWhile(ASTStmtWhile &);
    ASTStmtWhile &operator=(ASTStmtWhile &);
};

class ASTStmtDo : public ASTStmt
{
public:
    ASTStmtDo(ASTExpr *Cond, ASTStmt *Stmt, LocationData Loc) : ASTStmt(Loc), cond(Cond), stmt(Stmt) {}
    ~ASTStmtDo()
    {
        delete cond;
        delete stmt;
    }
    ASTExpr *getCond()
    {
        return cond;
    }
    ASTStmt *getStmt()
    {
        return stmt;
    }
    void execute(ASTVisitor &visitor, void *param)
    {
        visitor.caseStmtDo(*this,param);
    }
private:
    ASTExpr *cond;
    ASTStmt *stmt;
    //NOT IMPLEMENTED; DO NOT USE
    ASTStmtDo(ASTStmtDo &);
    ASTStmtDo &operator=(ASTStmtDo &);
};

////////////////////////////////////////////////////////////////
// Types

class ASTType : public AST
{
public:
    ASTType(LocationData Loc) : AST(Loc) {}
		virtual bool isSimple() const = 0;
		virtual int getSimpleId() const = 0;
    virtual void execute(ASTVisitor &visitor, void *param) = 0;
};

class ASTTypeVoid : public ASTType
{
public:
    ASTTypeVoid(LocationData Loc) : ASTType(Loc) {}
		ASTTypeVoid(ASTTypeVoid const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_VOID;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeVoid(*this, param);}
};

class ASTTypeGlobal : public ASTType
{
public:
    ASTTypeGlobal(LocationData Loc) : ASTType(Loc) {}
		ASTTypeGlobal(ASTTypeGlobal const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_GLOBAL;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeGlobal(*this, param);}
};

class ASTTypeFloat : public ASTType
{
public:
    ASTTypeFloat(LocationData Loc) : ASTType(Loc) {}
		ASTTypeFloat(ASTTypeFloat const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_FLOAT;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeFloat(*this, param);}
};

class ASTTypeBool : public ASTType
{
public:
    ASTTypeBool(LocationData Loc) : ASTType(Loc) {}
		ASTTypeBool(ASTTypeBool const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_BOOL;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeBool(*this, param);}
};

class ASTTypeFFC : public ASTType
{
public:
    ASTTypeFFC(LocationData Loc) : ASTType(Loc) {}
		ASTTypeFFC(ASTTypeFFC const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_FFC;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeFFC(*this, param);}
};

class ASTTypeItem : public ASTType
{
public:
    ASTTypeItem(LocationData Loc) : ASTType(Loc) {}
		ASTTypeItem(ASTTypeItem const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_ITEM;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeItem(*this, param);}
};

class ASTTypeItemclass : public ASTType
{
public:
    ASTTypeItemclass(LocationData Loc) : ASTType(Loc) {}
		ASTTypeItemclass(ASTTypeItemclass const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_ITEMCLASS;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeItemclass(*this, param);}
};

class ASTTypeNPC : public ASTType
{
public:
    ASTTypeNPC(LocationData Loc) : ASTType(Loc) {}
		ASTTypeNPC(ASTTypeNPC const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_NPC;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeNPC(*this, param);}
};

class ASTTypeLWpn : public ASTType
{
public:
    ASTTypeLWpn(LocationData Loc) : ASTType(Loc) {}
		ASTTypeLWpn(ASTTypeLWpn const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_LWPN;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeLWpn(*this, param);}
};

class ASTTypeEWpn : public ASTType
{
public:
    ASTTypeEWpn(LocationData Loc) : ASTType(Loc) {}
		ASTTypeEWpn(ASTTypeEWpn const &base) : ASTType(base.getLocation()) {} // Copy Constructor
		bool isSimple() const {return true;}
		int getSimpleId() const {return ScriptParser::TYPE_EWPN;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseTypeEWpn(*this, param);}
};

////////////////////////////////////////////////////////////////
// Function Declaration

class ASTFuncDecl : public ASTDecl
{
public:
    ASTFuncDecl(LocationData Loc);
		ASTFuncDecl(ASTFuncDecl const &base); // Copy Constructor
		~ASTFuncDecl();

    ASTType *getReturnType() const {return rettype;}
    void setReturnType(ASTType *type) {rettype = type;}

    string getName() const {return name;}
    void setName(string n) {name = n;}

    list<ASTFuncParam *> const &getParams() const {return params;}
    void copyParam(ASTFuncParam *param);
    void copyParamList(ASTList *list);

    ASTBlock *getBlock() const {return block;}
    void setBlock(ASTBlock *b) {block = b;}

    void execute(ASTVisitor &visitor, void *param) {visitor.caseFuncDecl(*this, param);}
private:
    ASTType *rettype;
    string name;
    list<ASTFuncParam *> params;
    ASTBlock *block;
};

class ASTFuncParam : public AST
{
public:
		ASTFuncParam(ASTType *Type, string Name, LocationData Loc);
		ASTFuncParam(ASTFuncParam const &base); // Copy Constructor
		~ASTFuncParam();

		ASTType *getType() const {return type;}
		string getName() {return name;}

		void execute(ASTVisitor &visitor, void *param) {visitor.caseFuncParam(*this, param);}
private:
		ASTType *type;
		string name;
};

////////////////////////////////////////////////////////////////
// Variable Declaration

class ASTVarDeclList : public ASTDecl
{
public:
		ASTVarDeclList(LocationData Loc);
		ASTVarDeclList(ASTVarDeclList const &base); // Copy Constructor
		~ASTVarDeclList();

		ASTType *getType() const {return type;}
		void copyType(ASTType *type);

		list<ASTVarDecl *> &getDeclarations() {return decls;}
		void addVarDecl(ASTVarDecl *vd);

    void execute(ASTVisitor &visitor, void *param) {visitor.caseVarDeclList(*this, param);}
private:
		ASTType *type;
		list<ASTVarDecl *> decls;
};

class ASTVarDecl : public ASTDecl
{
public:
		ASTVarDecl(string Name, LocationData Loc);
		ASTVarDecl(ASTVarDecl const &base); // Copy Constructor
		virtual ~ASTVarDecl();

    ASTType *getType() const {return type;}
	  void copyType(ASTType *t);
    string getName() const {return name;}

    virtual void execute(ASTVisitor &visitor, void *param) = 0;
private:
		ASTType *type;
		string name;
};

class ASTSingleVarDecl : public ASTVarDecl
{
public:
		ASTSingleVarDecl(string Name, LocationData Loc);
		ASTSingleVarDecl(string Name, ASTExpr *Init, LocationData Loc);
		ASTSingleVarDecl(ASTSingleVarDecl const &base); // Copy Constructor
    ~ASTSingleVarDecl();

		bool hasInitializer() const {return initializer != NULL;}
		ASTExpr *getInitializer() const {return initializer;}

    void execute(ASTVisitor &visitor, void *param) {visitor.caseSingleVarDecl(*this, param);}
private:
    ASTExpr *initializer;
};

class ASTArrayDecl : public ASTVarDecl
{
public:
    ASTArrayDecl(string Name, ASTExpr *Size, LocationData Loc);
    ASTArrayDecl(string Name, ASTArrayInitializer *Init, LocationData Loc);
    ASTArrayDecl(string Name, ASTExpr *Size, ASTArrayInitializer *Init, LocationData Loc);
		ASTArrayDecl(ASTArrayDecl const &base); // Copy Constructor
    ~ASTArrayDecl();
    ASTExpr *getSize() const {return size;}
		bool hasInitializer() const {return initializer != NULL;}
    ASTArrayInitializer *getInitializer() const {return initializer;}
    void execute(ASTVisitor &visitor, void *param) {visitor.caseArrayDecl(*this, param);}
private:
    ASTExpr *size;
    ASTArrayInitializer *initializer;
};

class ASTArrayInitializer : public AST
{
public:
    ASTArrayInitializer(LocationData Loc);
    ASTArrayInitializer(ASTString *String, LocationData Loc);
		ASTArrayInitializer(ASTArrayInitializer const &base); // Copy Constructor
    ~ASTArrayInitializer();

    list<ASTExpr *> const &getElements() const {return elements;}
    void addElement(ASTExpr *element) {elements.push_back(element);}
    bool isString() const {return _isString;}
		long getSize() const {return long(elements.size());}

    void execute(ASTVisitor &visitor, void *param) {visitor.caseArrayInitializer(*this, param);}
private:
    list<ASTExpr *> elements;
    bool _isString;
};


#endif
