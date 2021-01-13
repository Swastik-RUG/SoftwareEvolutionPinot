#ifndef Utility_NAME_H
#define Utility_NAME_H

#include "../platform/platform.h"
#include "../symbol/symbol.h"
#include "../tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif
class AstExpression;

class Utility
{
	public:
		static ContainerType *IdentifyContainerType(VariableSymbol*);
		static void RemoveJavaBaseClass(SymbolSet&);
		static TypeSymbol *GetTypeSymbol(Symbol*);
		static void RemoveBuiltinInterfaces(SymbolSet&);
		static AstExpression *RemoveCasting(AstExpression*);
		static void Intersection(vector<signed>&, vector<signed>&, vector<signed>&);
		static void RemoveDuplicates(vector<signed>&);
		static bool Aliasing(VariableSymbol*, VariableSymbol*);
};


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif