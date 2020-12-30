#ifndef FactoryAnalysis_NAME_H
#define FactoryAnalysis_NAME_H

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
    // template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    // class vector: protected _Vector_base<_Tp, _Alloc>;

    class FactoryAnalysis
    {
    private:
        MethodSymbol *method;
        Flatten flatten;
        static SymbolSet visited; // visited methods, avoid analysis on recursion methods.
        StoragePool *ast_pool;

    public:
        static SymbolSet types;
        FactoryAnalysis(MethodSymbol *msym, StoragePool *pool) : method(msym), ast_pool(pool) { flatten.init(msym, pool); }
        bool IsFactoryMethod();
        bool IsCreationMethod();
        void CleanUp()
        {
            types.SetEmpty();
            visited.SetEmpty();
        }
        ~FactoryAnalysis() {}
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif