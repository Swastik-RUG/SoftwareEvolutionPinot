#ifndef SingletonAnalysis_NAME_H
#define SingletonAnalysis_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"
#include "../declarations/set.h"
#include "../declarations/set.h"
#include "../Utility/Flatten.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes { // Open namespace Jikes block
#endif

class Flatten;
class StoragePool;
class Snapshot;
// template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
// class vector: protected _Vector_base<_Tp, _Alloc>;

class SingletonAnalysis
{
	private:
		VariableSymbol *variable;
		MethodSymbol *method;
		Flatten flatten;
		static SymbolSet visited; // visited methods, avoid analysis on recursion methods.
		StoragePool *ast_pool;
		vector<vector<signed> > exec_paths;
		vector<signed> path;
		vector<signed> footprints; // point of creating the Singleton instance
		vector<signed> fingerprints; // point of returning the Singleton instance
	public:
		SingletonAnalysis(VariableSymbol *vsym, MethodSymbol *msym, StoragePool *pool)
			:variable(vsym),method(msym), ast_pool(pool){ flatten.init(msym, pool); }
		void TracePath(Snapshot*);
		bool ReturnsSingleton();
		bool ReturnsSingleton1();
		void CleanUp() { visited.SetEmpty(); }
		~SingletonAnalysis(){}
};

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
