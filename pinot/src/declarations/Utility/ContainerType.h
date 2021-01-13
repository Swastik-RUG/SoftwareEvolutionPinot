#ifndef ContainerType_NAME_H
#define ContainerType_NAME_H

#include "../platform/platform.h"
#include "../symbol/symbol.h"
#include "../tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

class AstMethodInvocation;

class ContainerType
{
	public:
		enum ContainerKind
		{
			ARRAY,
			MAP,
			COLLECTION,
			ARRAYLIST,
			HASHSET,
			LINKEDHASHSET,
			LINKEDLIST,
			TREESET,
			VECTOR
		};
		ContainerType(ContainerKind k, VariableSymbol *v):kind(k),container(v){}
		virtual bool IsGetMethod(MethodSymbol*){ return false; }
		virtual bool IsPutMethod(MethodSymbol*){ return false; }
		virtual VariableSymbol *GetPutValue(AstMethodInvocation*){ return NULL; }
		virtual TypeSymbol *GetPutType(AstMethodInvocation*){ return NULL; }
		virtual VariableSymbol *GetContainer(){ return container; }
		ContainerKind kind;
	private:
		VariableSymbol *container;
};
class MapContainer : public ContainerType
{
	public:
		MapContainer(VariableSymbol *v):ContainerType(MAP, v){}
		bool IsGetMethod(MethodSymbol*);
		bool IsPutMethod(MethodSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation*);
		//VariableSymbol *GetContainer(){ return container; }
};
class ArrayContainer : public ContainerType
{
	public:
		ArrayContainer(VariableSymbol *array_symbol):ContainerType(ARRAY, array_symbol){}
		//VariableSymbol *GetContainer(){ return container; }
};
class ArrayListContainer : public ContainerType
{
	public:
		ArrayListContainer(VariableSymbol *v):ContainerType(ARRAYLIST, v){}
		bool IsPutMethod(MethodSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation*);
};
class HashSetContainer : public ContainerType
{
	public:
		HashSetContainer(VariableSymbol *v):ContainerType(HASHSET, v){}
		bool IsPutMethod(MethodSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation*);
};
class LinkedHashSetContainer : public ContainerType
{
	public:
		LinkedHashSetContainer(VariableSymbol *v):ContainerType(LINKEDHASHSET, v){}
};
class LinkedListContainer : public ContainerType
{
	public:
		LinkedListContainer(VariableSymbol *v):ContainerType(LINKEDLIST, v){}
		bool IsPutMethod(MethodSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation*);
};
class TreeSetContainer : public ContainerType
{
	public:
		TreeSetContainer(VariableSymbol *v):ContainerType(TREESET, v){}
};
class VectorContainer : public ContainerType
{
	public:
		VectorContainer(VariableSymbol *v):ContainerType(VECTOR, v){}
		bool IsPutMethod(MethodSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation*);
};
class CollectionContainer : public ContainerType
{
	public:
		CollectionContainer(VariableSymbol *v):ContainerType(COLLECTION, v){}
		bool IsGetMethod(MethodSymbol*){ return false; }
		bool IsPutMethod(MethodSymbol*);
		bool IsPutType(AstMethodInvocation*, TypeSymbol*);
		VariableSymbol *GetPutValue(AstMethodInvocation*);
		TypeSymbol *GetPutType(AstMethodInvocation *);
		//VariableSymbol *GetContainer(){ return container; }
};


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif