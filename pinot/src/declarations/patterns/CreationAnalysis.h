#ifndef CreationAnalysis_NAME_H
#define CreationAnalysis_NAME_H

#include "../platform/platform.h"
#include "../symbol/symbol.h"
#include "../set.h"
#include "../tuple.h"
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
