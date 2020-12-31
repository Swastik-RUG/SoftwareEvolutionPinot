#ifndef Delegation_NAME_H
#define Delegation_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    class AstExpression;
    class AstMethodInvocation;

    class DelegationEntry
    {
    public:
        DelegationEntry(TypeSymbol *f, TypeSymbol *t,
                        AstExpression *b, VariableSymbol *v, MethodSymbol *m,
                        MethodSymbol *e, AstMethodInvocation *c)
            : from(f), to(t), base_opt(b), vsym(v), method(m), enclosing(e), call(c) {}
        ~DelegationEntry();
        TypeSymbol *from;
        TypeSymbol *to;
        AstExpression *base_opt;
        VariableSymbol *vsym;
        MethodSymbol *method;
        MethodSymbol *enclosing;
        AstMethodInvocation *call;
    };

    class DelegationTable
    {
    public:
        DelegationTable() { table = new vector<DelegationEntry *>(); }
        int UniqueDirectedCalls();
        void InsertDelegation(TypeSymbol *, TypeSymbol *, AstExpression *, VariableSymbol *, MethodSymbol *, MethodSymbol *, AstMethodInvocation *);
        bool TraceCall(MethodSymbol *, MethodSymbol *);
        DelegationEntry *Entry(int i) { return (*table)[i]; }
        MethodSymbol *Delegates(TypeSymbol *, TypeSymbol *);
        int size() { return table->size(); }
        TypeSymbol *ResolveType(AstExpression *);
        bool DelegatesSuccessors(TypeSymbol *, TypeSymbol *);
        void ShowDelegations(TypeSymbol *, TypeSymbol *);
        int IsBidirectional(TypeSymbol *, TypeSymbol *);
        void DumpTable();
        void ConcretizeDelegations();
        ~DelegationTable() { delete table; }

    private:
        vector<DelegationEntry *> *table;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif