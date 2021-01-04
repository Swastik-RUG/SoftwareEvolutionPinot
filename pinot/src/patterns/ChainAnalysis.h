#ifndef ChainAnalysis_NAME_H
#define ChainAnalysis_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include "../Utility/Flatten.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    class Flatten;
    class AstBinaryExpression;
    class StoragePool;
    class Snapshot;
    // template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    // class vector: protected _Vector_base<_Tp, _Alloc>;

    class ChainAnalysis
    {
    private:
        VariableSymbol *variable;
        MethodSymbol *method;
        Flatten flatten;
        //static SymbolSet visited; // visited methods, avoid analysis on recursion methods.
        StoragePool *ast_pool;
        vector<vector<signed>> paths;
        vector<signed> path;
        vector<signed> footprints;

    public:
        enum ResultTag
        {
            CoR,
            DECORATOR,
            NONE
        };
        ChainAnalysis(VariableSymbol *vsym, MethodSymbol *msym, StoragePool *pool)
            : variable(vsym), method(msym), ast_pool(pool) { flatten.init(msym, pool); }
        void TracePath(Snapshot *);
        void TraceBinaryExpression(AstBinaryExpression *, Snapshot *);
        ResultTag AnalyzeCallChain();
        void CleanUp() { paths.clear(); /*visited.SetEmpty();*/ }
        ~ChainAnalysis() {}
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
