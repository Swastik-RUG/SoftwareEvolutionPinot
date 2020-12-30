#ifndef Table_NAME_H
#define Table_NAME_H

#include "declarations/platform.h"
#include "declarations/symbol/symbol.h"
#include "declarations/tuple.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>
#include <map>

    class ReadAccessTable
    {
        // Actually records every method that returns nonlocal vars.
    public:
        ReadAccessTable() { table = new multimap<VariableSymbol *, MethodSymbol *>(); }
        ~ReadAccessTable() { delete table; }
        void InsertReadAccess(VariableSymbol *vsym, MethodSymbol *msym)
        {
            table->insert(pair<VariableSymbol *, MethodSymbol *>(vsym, msym));
        }
        int size() { return table->size(); }
        multimap<VariableSymbol *, MethodSymbol *>::iterator begin() { return table->begin(); }
        multimap<VariableSymbol *, MethodSymbol *>::iterator end() { return table->end(); }
        void DumpTable();

    private:
        multimap<VariableSymbol *, MethodSymbol *> *table;
    };

    class WriteAccessTable
    {
    public:
        WriteAccessTable() { table = new multimap<VariableSymbol *, MethodSymbol *>(); }
        ~WriteAccessTable() { delete table; }
        void InsertWriteAccess(VariableSymbol *vsym, MethodSymbol *msym)
        {
            table->insert(pair<VariableSymbol *, MethodSymbol *>(vsym, msym));
        }
        bool IsWrittenBy(VariableSymbol *, MethodSymbol *);
        bool IsWrittenBy(VariableSymbol *, MethodSymbol *, DelegationTable *);
        int size() { return table->size(); }
        multimap<VariableSymbol *, MethodSymbol *>::iterator begin() { return table->begin(); }
        multimap<VariableSymbol *, MethodSymbol *>::iterator end() { return table->end(); }
        void DumpTable();

    private:
        multimap<VariableSymbol *, MethodSymbol *> *table;
    };

    class ClassSymbolTable
    {
    public:
        ClassSymbolTable() { table = new vector<TypeSymbol *>(); }
        void AddClassSymbol(TypeSymbol *);
        unsigned size() { return table->size(); }
        int ConcreteClasses();
        //multimap<char*, TypeSymbol*>::iterator begin() { return table -> begin(); }
        //multimap<char*, TypeSymbol*>::iterator end() { return table -> end(); }
        TypeSymbol *operator[](unsigned i) { return (*table)[i]; }
        TypeSymbol *GetSymbol(char *, char *, char *);
        TypeSymbol *GetSymbol(wchar_t *); // to be eleiminated.
        bool HasSubclasses(TypeSymbol *);
        bool HasSubtypes(TypeSymbol *);
        void PrintSubclasses(TypeSymbol *);
        void PrintSubinterfaces(TypeSymbol *);
        void PrintSubtypes(TypeSymbol *);
        bool Converge(TypeSymbol *, TypeSymbol *);
        bool IsFamily(TypeSymbol *, TypeSymbol *);
        vector<TypeSymbol *> *GetAncestors(TypeSymbol *);
        void ExpandSubtypes();
        void PrintDeclaration(char *, char *);
        ~ClassSymbolTable() { delete table; }

    private:
        vector<TypeSymbol *> *table;
    };

    class MethodSymbolTable
    {
    public:
        MethodSymbolTable() { table = new vector<MethodSymbol *>(); }
        void AddMethodSymbol(MethodSymbol *);
        unsigned size() { return table->size(); }
        vector<MethodSymbol *>::iterator begin() { return table->begin(); }
        vector<MethodSymbol *>::iterator end() { return table->end(); }
        MethodSymbol *operator[](unsigned i) { return (*table)[i]; }
        MethodSymbol *GetSymbol(char *, char *, char *);
        Ast *GetAstDeclaration(wchar_t *, wchar_t *, wchar_t *); // to be eliminated.
        void PrintDeclaration(char *, char *, char *);
        void PrintBody(char *, char *, char *);
        void ExpandCallDependents();
        void ClearMarks();
        ~MethodSymbolTable() { delete table; }

    private:
        //multimap<char*, MethodSymbol*> *table;
        vector<MethodSymbol *> *table;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif