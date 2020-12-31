#ifndef CreationAnalysis_NAME_H
#define CreationAnalysis_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif
    class AstClassCreationExpression;
    class AstBlock;

    class CreationAnalysis
    {
    public:
        CreationAnalysis() {}
        void visit(AstBlock *);
        void visit(AstClassCreationExpression *);
        ~CreationAnalysis() {}

        vector<TypeSymbol *> return_types;

    private:
        SymbolSet cache; // cache visited method symbols.
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif