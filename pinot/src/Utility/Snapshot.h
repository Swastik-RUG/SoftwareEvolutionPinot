#ifndef Snapshot_NAME_H
#define Snapshot_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif
    class AstExpression;

    class Snapshot
    {
        friend class SingletonAnalysis;
        friend class FlyweightAnalysis;
        friend class FactoryAnalysis;
        friend class ChainAnalysis;
        friend class Flatten;

    public:
        Snapshot() : statements(NULL), conditions(NULL), condition(NULL), roles(NULL), index(0), number(-1) {}

    private:
        vector<Ast *> *statements;
        vector<AstExpression *> *conditions;
        AstExpression *condition;
        vector<Role *> *roles;
        signed index; // for IsFlyweightFactory
        signed number;
        set<signed> previous, next;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif