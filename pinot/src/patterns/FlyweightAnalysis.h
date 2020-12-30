#ifndef FlyWeightAnalysis_NAME_H
#define FlyWeightAnalysis_NAME_H

#include "../declarations/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    class Flatten;
    class StoragePool;

    class AstBlock;
    class AstIfStatement;
    class AstWhileStatement;
    class AstForStatement;
    class AstTryStatement;
    class AstStatement;
    class AstExpression;
    class AstAssignmentExpression;
    class AstLocalVariableStatement;
    class AstVariableDeclarator;
    class AstReturnStatement;
    class AstMethodInvocation;
    class AstSynchronizedStatement;
    class AstConditionalExpression;
    class AstArrayAccess;

    class FlyweightAnalysis
    {
    private:
        MethodSymbol *GetFlyweight;
        TypeSymbol *flyweight;
        SymbolSet key;
        ContainerType *container_type;
        vector<Ast *> statements;
        vector<AstExpression *> conditions;
        vector<Snapshot *> summary;
        vector<Snapshot *> traces;
        //SymbolSet vcache;
        char bitmap[10];
        int n;
        // include some kind of summary for the resulting flow analysis
        void AssignRoles();

    public:
        FlyweightAnalysis(MethodSymbol *GetMethod)
        {
            container_type = NULL;
            GetFlyweight = GetMethod;
            flyweight = GetFlyweight->Type();
            for (unsigned i = 0; i < GetFlyweight->NumFormalParameters(); i++)
                key.AddElement(GetFlyweight->FormalParameter(i));
            for (int i = 0; i < 10; i++)
                bitmap[i] = 'X';
            n = 0;
        }
        ~FlyweightAnalysis() { delete container_type; }
        bool IsFlyweightFactory();
        void UpdateSummary();
        void DumpSummary();
        VariableSymbol *GetFlyweightPool() { return (container_type) ? container_type->GetContainer() : NULL; }
        void visit(AstBlock *);
        void visit(AstIfStatement *);
        void visit(AstWhileStatement *);
        void visit(AstForStatement *);
        void visit(AstTryStatement *);
        void visit(AstStatement *);
        void visit(AstExpression *);
        void visit(AstAssignmentExpression *);
        void visit(AstLocalVariableStatement *);
        void visit(AstVariableDeclarator *);
        void visit(AstReturnStatement *);
        void visit(AstMethodInvocation *);
        void visit(AstSynchronizedStatement *) {}
        void visit(AstConditionalExpression *) {}
    };

    class Role
    {
        friend class FlyweightAnalysis;
        friend class Snapshot;
        friend class Flatten;

    private:
        enum RoleTag
        {
            CREATE,
            REGISTER,
            RETRIEVE,
            ALLOCATE,
            RETURN,
            NIL
        };

    public:
        Role(AstArrayAccess *v, RoleTag t) : array_access(v), tag(t) { vsym = NULL; }
        Role(VariableSymbol *v, RoleTag t) : vsym(v), tag(t) { array_access = NULL; }

    private:
        VariableSymbol *vsym;
        AstArrayAccess *array_access;
        RoleTag tag;
        char *TagName();
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif