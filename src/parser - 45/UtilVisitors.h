#ifndef UTILVISITORS_H
#define UTILVISITORS_H

#include <assert.h>
#include "AST.h"


class Clone : public ASTVisitor
{
public:
    virtual void caseDefault(void *param);
    virtual void caseProgram(ASTProgram &host, void *param);
    virtual void caseFloat(ASTFloat &host, void *param);
    virtual void caseString(ASTString &host, void *param);
    virtual void caseDeclList(ASTDeclList &host, void *param);
    virtual void caseImportDecl(ASTImportDecl &host, void *param);
    virtual void caseConstDecl(ASTConstDecl &host, void *param);
    virtual void caseExprAnd(ASTExprAnd &host, void *param);
    virtual void caseExprOr(ASTExprOr &host, void *param);
    virtual void caseExprGT(ASTExprGT &host, void *param);
    virtual void caseExprGE(ASTExprGE &host, void *param);
    virtual void caseExprLT(ASTExprLT &host, void *param);
    virtual void caseExprLE(ASTExprLE &host, void *param);
    virtual void caseExprEQ(ASTExprEQ &host, void *param);
    virtual void caseExprNE(ASTExprNE &host, void *param);
    virtual void caseExprPlus(ASTExprPlus &host, void *param);
    virtual void caseExprMinus(ASTExprMinus &host, void *param);
    virtual void caseExprTimes(ASTExprTimes &host, void *param);
    virtual void caseExprDivide(ASTExprDivide &host, void *param);
    virtual void caseExprNot(ASTExprNot &host, void *param);
    virtual void caseExprNegate(ASTExprNegate &host, void *param);
    virtual void caseNumConstant(ASTNumConstant &host, void *param);
    virtual void caseFuncCall(ASTFuncCall &host, void *param);
    virtual void caseFuncId(ASTFuncId &host, void *param);
    virtual void caseBoolConstant(ASTBoolConstant &host, void *param);
    virtual void caseBlock(ASTBlock &host, void *param);
    virtual void caseStmtAssign(ASTStmtAssign &host, void *param);
    virtual void caseExprDot(ASTExprDot &host, void *param);
    virtual void caseExprArrow(ASTExprArrow &host, void *param);
    virtual void caseExprArray(ASTExprArray &host, void *param);
    virtual void caseStmtFor(ASTStmtFor &host, void *param);
    virtual void caseStmtIf(ASTStmtIf &host, void *param);
    virtual void caseStmtIfElse(ASTStmtIfElse &host, void *param);
    virtual void caseStmtReturn(ASTStmtReturn &host, void *param);
    virtual void caseStmtReturnVal(ASTStmtReturnVal &host, void *param);
    virtual void caseStmtEmpty(ASTStmtEmpty &host, void *param);
    virtual void caseScript(ASTScript &host, void *param);
    virtual void caseStmtWhile(ASTStmtWhile &host, void *param);
    virtual void caseStmtDo(ASTStmtDo &host, void *param);
    virtual void caseExprBitOr(ASTExprBitOr &host, void *param);
    virtual void caseExprBitXor(ASTExprBitXor &host, void *param);
    virtual void caseExprBitAnd(ASTExprBitAnd &host, void *param);
    virtual void caseExprLShift(ASTExprLShift &host, void *param);
    virtual void caseExprRShift(ASTExprRShift &host, void *param);
    virtual void caseExprModulo(ASTExprModulo &host, void *param);
    virtual void caseExprBitNot(ASTExprBitNot &host, void *param);
    virtual void caseExprIncrement(ASTExprIncrement &host, void *param);
    virtual void caseExprPreIncrement(ASTExprPreIncrement &host, void *param);
    virtual void caseExprDecrement(ASTExprDecrement &host, void *param);
    virtual void caseExprPreDecrement(ASTExprPreDecrement &host, void *param);
    virtual void caseStmtBreak(ASTStmtBreak &host, void *param);
    virtual void caseStmtContinue(ASTStmtContinue &host, void *param);
		// Types
    void caseTypeVoid(ASTTypeVoid &host, void *) {result = new ASTTypeVoid(host);}
    void caseTypeGlobal(ASTTypeGlobal &host, void *) {result = new ASTTypeGlobal(host);}
    void caseTypeFloat(ASTTypeFloat &host, void *) {result = new ASTTypeFloat(host);}
    void caseTypeBool(ASTTypeBool &host, void *) {result = new ASTTypeBool(host);}
    void caseTypeFFC(ASTTypeFFC &host, void *) {result = new ASTTypeFFC(host);}
    void caseTypeItem(ASTTypeItem &host, void *) {result = new ASTTypeItem(host);}
    void caseTypeItemclass(ASTTypeItemclass &host, void *) {result = new ASTTypeItemclass(host);}
    void caseTypeNPC(ASTTypeNPC &host, void *) {result = new ASTTypeNPC(host);}
    void caseTypeLWpn(ASTTypeLWpn &host, void *) {result = new ASTTypeLWpn(host);}
    void caseTypeEWpn(ASTTypeEWpn &host, void *) {result = new ASTTypeEWpn(host);}
		// Function Declaration
    void caseFuncDecl(ASTFuncDecl &host, void *) {result = new ASTFuncDecl(host);}
    void caseFuncParam(ASTFuncParam &host, void *) {result = new ASTFuncParam(host);}
		// Variable Declaration
		void caseVarDeclList(ASTVarDeclList &host, void *) {result = new ASTVarDeclList(host);}
    void caseSingleVarDecl(ASTSingleVarDecl &host, void *) {result = new ASTSingleVarDecl(host);}
    void caseArrayDecl(ASTArrayDecl &host, void *) {result = new ASTArrayDecl(host);}
    void caseArrayInitializer(ASTArrayInitializer &host, void *) {result = new ASTArrayInitializer(host);}

    AST *getResult()
    {
        return result;
    }
private:
    AST *result;
};

class RecursiveVisitor : public ASTVisitor
{
public:
		virtual void caseDefault(void *) {}
    virtual void caseProgram(ASTProgram &host, void *param)
    {
        host.getDeclarations()->execute(*this,param);
    }
    virtual void caseDeclList(ASTDeclList &host, void *param)
    {
        list<ASTDecl *> l = host.getDeclarations();

        for(list<ASTDecl *>::iterator it = l.begin(); it != l.end(); it++)
        {
            (*it)->execute(*this,param);
        }
    }
    virtual void caseExprAnd(ASTExprAnd &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprOr(ASTExprOr &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprGT(ASTExprGT &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprGE(ASTExprGE &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprLT(ASTExprLT &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprLE(ASTExprLE &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprEQ(ASTExprEQ &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprNE(ASTExprNE &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprPlus(ASTExprPlus &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprMinus(ASTExprMinus &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprTimes(ASTExprTimes &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprDivide(ASTExprDivide &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprBitOr(ASTExprBitOr &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprBitXor(ASTExprBitXor &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprBitAnd(ASTExprBitAnd &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprLShift(ASTExprLShift &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprRShift(ASTExprRShift &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprModulo(ASTExprModulo &host, void *param)
    {
        host.getFirstOperand()->execute(*this,param);
        host.getSecondOperand()->execute(*this,param);
    }
    virtual void caseExprNot(ASTExprNot &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprBitNot(ASTExprBitNot &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprIncrement(ASTExprIncrement &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprPreIncrement(ASTExprPreIncrement &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprDecrement(ASTExprDecrement &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprPreDecrement(ASTExprPreDecrement &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprNegate(ASTExprNegate &host, void *param)
    {
        host.getOperand()->execute(*this,param);
    }
    virtual void caseExprArrow(ASTExprArrow &host, void*param)
    {
        host.getLVal()->execute(*this,param);

        if(host.getIndex())
            host.getIndex()->execute(*this,param);
    }
    virtual void caseExprArray(ASTExprArray &host, void*param)
    {
        if(host.getIndex()) host.getIndex()->execute(*this,param);
    }
    virtual void caseNumConstant(ASTNumConstant &host, void *param)
    {
        host.getValue()->execute(*this,param);
    }
    virtual void caseFuncCall(ASTFuncCall &host, void *param)
    {
        list<ASTExpr *> l = host.getParams();

        for(list<ASTExpr *>::iterator it = l.begin(); it != l.end(); it++)
        {
            (*it)->execute(*this,param);
        }
    }
    virtual void caseFuncId(ASTNumConstant &host, void *param)
    {
    }
    virtual void caseBlock(ASTBlock &host, void *param)
    {
        list<ASTStmt *> l = host.getStatements();

        for(list<ASTStmt *>::iterator it = l.begin(); it != l.end(); it++)
            (*it)->execute(*this,param);
    }
    virtual void caseStmtAssign(ASTStmtAssign &host, void *param)
    {
        host.getLVal()->execute(*this,param);
        host.getRVal()->execute(*this,param);
    }
    virtual void caseStmtFor(ASTStmtFor &host, void *param)
    {
        host.getPrecondition()->execute(*this,param);
        host.getIncrement()->execute(*this,param);
        host.getTerminationCondition()->execute(*this,param);
        host.getStmt()->execute(*this,param);
    }
    virtual void caseStmtIf(ASTStmtIf &host, void *param)
    {
        host.getCondition()->execute(*this,param);
        host.getStmt()->execute(*this,param);
    }
    virtual void caseStmtIfElse(ASTStmtIfElse &host, void *param)
    {
        host.getCondition()->execute(*this,param);
        host.getStmt()->execute(*this,param);
        host.getElseStmt()->execute(*this,param);
    }
    virtual void caseStmtReturnVal(ASTStmtReturnVal &host, void *param)
    {
        host.getReturnValue()->execute(*this,param);
    }
    virtual void caseScript(ASTScript &host, void *param)
    {
        host.getType()->execute(*this,param);
        host.getScriptBlock()->execute(*this,param);
    }
    virtual void caseStmtWhile(ASTStmtWhile &host, void *param)
    {
        host.getCond()->execute(*this,param);
        host.getStmt()->execute(*this,param);
    }
    virtual void caseStmtDo(ASTStmtDo &host, void *param)
    {
        host.getStmt()->execute(*this,param);
        host.getCond()->execute(*this,param);
    }
		// Function Declaration
    virtual void caseFuncDecl(ASTFuncDecl &host, void *param);
		// Variable Declaration
		virtual void caseVarDeclList(ASTVarDeclList &host, void *param);
    virtual void caseSingleVarDecl(ASTSingleVarDecl &host, void *param);
    virtual void caseArrayDecl(ASTArrayDecl &host, void *param);
    virtual void caseArrayInitializer(ASTArrayInitializer &host, void *param);
};

//removes all import declarations from a program
//call with param=NULL
//NOT responsible for freeing said imports
class GetImports : public ASTVisitor
{
public:
    GetImports() : result() {}
    virtual void caseDefault(void *param);
    virtual void caseDeclList(ASTDeclList &host, void *param);
    virtual void caseProgram(ASTProgram &host, void *param);
    virtual void caseImportDecl(ASTImportDecl &host, void *param);
    vector<ASTImportDecl *> &getResult()
    {
        return result;
    }
private:
    vector<ASTImportDecl *> result;
};

class GetConsts : public ASTVisitor
{
public:
    GetConsts() : result() {}
    virtual void caseDefault(void *param);
    virtual void caseDeclList(ASTDeclList &host, void *param);
    virtual void caseProgram(ASTProgram &host, void *param);
    virtual void caseConstDecl(ASTConstDecl &host, void *param);
    vector<ASTConstDecl *> &getResult()
    {
        return result;
    }
private:
    vector<ASTConstDecl *> result;
};

class GetGlobalFuncs : public ASTVisitor
{
public:
    GetGlobalFuncs() : result() {}
    virtual void caseDefault(void *param);
    virtual void caseDeclList(ASTDeclList &host, void *param);
    virtual void caseProgram(ASTProgram &host, void *param) {host.getDeclarations()->execute(*this, param);}
    virtual void caseFuncDecl(ASTFuncDecl &host, void *param);
    vector<ASTFuncDecl *> getResult()
    {
        return result;
    }
private:
    vector<ASTFuncDecl *> result;
};

class GetGlobalVars : public ASTVisitor
{
public:
    GetGlobalVars() : vars() {}
    void caseDefault(void *) {var = false;}
    void caseProgram(ASTProgram &host, void *) {host.getDeclarations()->execute(*this, NULL);}
    void caseDeclList(ASTDeclList &host, void *param);
		void caseVarDeclList(ASTVarDeclList &host, void *);
    void caseSingleVarDecl(ASTSingleVarDecl &host, void *) {vars.push_back(&host); var = true;}
    void caseArrayDecl(ASTArrayDecl &host, void *) {arrays.push_back(&host); var = true;}
    vector<ASTSingleVarDecl *> getVars() {return vars;}
    vector<ASTArrayDecl *> getArrays() {return arrays;}
private:
		bool var;
    vector<ASTSingleVarDecl *> vars;
    vector<ASTArrayDecl *> arrays;
};

class GetScripts : public ASTVisitor
{
public:
    GetScripts() : result() {}
    virtual void caseDefault(void *) {assert(false);}
    virtual void caseProgram(ASTProgram &host, void *) {host.getDeclarations()->execute(*this, NULL);}
    virtual void caseDeclList(ASTDeclList &host, void *param);
    virtual void caseScript(ASTScript &, void *) {}
    vector<ASTScript *> getResult()
    {
        return result;
    }
private:
    vector<ASTScript *> result;
};

//Merges one AST into another. Pass the AST that will be destroyed in the process
//as the param.
//The param AST gets completely consumed and deleted
class MergeASTs : public ASTVisitor
{
public:
    virtual void caseDefault(void *param);
    virtual void caseProgram(ASTProgram &host, void *param);
};

class CheckForExtraneousImports : public RecursiveVisitor
{
public:
    CheckForExtraneousImports() : ok(true) {}
    bool isOK() {return ok;}
    virtual void caseDefault(void *param) {}
    virtual void caseImportDecl(ASTImportDecl &host, void *param);
private:
    bool ok;
};

class ExtractType : public ASTVisitor
{
public:
    virtual void caseDefault(void *param);
    virtual void caseTypeVoid(ASTTypeVoid &host, void *param);
    virtual void caseTypeFloat(ASTTypeFloat &host, void *param);
    virtual void caseTypeBool(ASTTypeBool &host, void *param);
    virtual void caseTypeFFC(ASTTypeFFC &host, void *param);
    virtual void caseTypeItem(ASTTypeItem &host, void *param);
    virtual void caseTypeItemclass(ASTTypeItemclass &host, void *param);
    virtual void caseTypeGlobal(ASTTypeGlobal &host, void *param);
    virtual void caseTypeNPC(ASTTypeNPC &host, void *param);
    virtual void caseTypeLWpn(ASTTypeLWpn &host, void *param);
    virtual void caseTypeEWpn(ASTTypeEWpn &host, void *param);
};

class IsDotExpr : public ASTVisitor
{
public:
    virtual void caseDefault(void *param)
    {
        *(bool *)param = false;
    }
    virtual void caseExprDot(ASTExprDot &, void *param)
    {
        *(bool *)param = true;
    }
};

class IsArrayDecl : public ASTVisitor
{
public:
    virtual void caseDefault(void *param)
    {
        *(bool *)param = false;
    }
    virtual void caseArrayDecl(ASTArrayDecl &, void *param)
    {
        *(bool *)param = true;
    }
};

class IsBlock : public ASTVisitor
{
public:
    virtual void caseDefault(void *param)
    {
        *(bool *)param = false;
    }
    virtual void caseBlock(ASTBlock &, void *param)
    {
        *(bool *)param = true;
    }
};

class IsFuncDecl : public ASTVisitor
{
public:
    virtual void caseDefault(void *param)
    {
        param=param; /*these are here to bypass compiler warnings about unused arguments*/ *(bool *)param = false;
    }
    virtual void caseFuncDecl(ASTFuncDecl &host, void *param)
    {
        void *temp;
        temp=&host;
        param=param; /*these are here to bypass compiler warnings about unused arguments*/ *(bool *)param = true;
    }
};

#endif
