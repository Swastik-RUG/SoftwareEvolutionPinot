#ifndef State_NAME_H
#define State_NAME_H

#include "../declarations/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>

    class State
    {
        friend class Statechart;

    public:
        enum StateKind
        {
            SET,       // target being changed
            GET,       // target being used/read
            CONDITION, // target in condition of if statement
            CREATE,    // target being created
            RETURN     // target begin returned
        };
        State(StateKind k, vector<wchar_t *> *p) : kind(k), true_branch(0), false_branch(0), participants(p) {}
        ~State() {}
        void addTrueBranch(State *tb) { true_branch = tb; }
        void addFalseBranch(State *fb) { false_branch = fb; }

    private:
        StateKind kind;
        State *true_branch, *false_branch;
        vector<wchar_t *> *participants;
    };

    class Statechart
    {
    public:
        Statechart() { statechart = new vector<State *>(); }
        void addState(State *s) { statechart->push_back(s); }
        State::StateKind getStateKindAt(int i) { return (*statechart)[i]->kind; }
        vector<wchar_t *> *getStateParticipantsAt(int i) { return (*statechart)[i]->participants; }
        int getSize() { return statechart->size(); }
        void Print();
        ~Statechart() {}

    private:
        vector<State *> *statechart;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif