#ifndef Env_NAME_H
#define Env_NAME_H

#include "platform.h"
#include "symbol.h"
#include "tuple.h"
#include "State.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>

    class State;

    class Env
    {
        friend class EnvTable;

    public:
        enum State
        {
            NIL,  // variable is assigned null
            INIT, // variable is initialized with a value
            MOD   // variable's value changed through assignment statement
        };

        Env(wchar_t *v, State s) : state(s), var(v) {}

    private:
        State state;
        wchar_t *var;
    };

    class EnvTable
    {
    public:
        EnvTable()
        {
            table = new vector<Env *>();
        }
        void addEnvironment(wchar_t *, Env::State);
        Env::State getState(wchar_t *);
        void changeState(wchar_t *, Env::State);
        ~EnvTable() { delete table; }

    private:
        vector<Env *> *table;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif