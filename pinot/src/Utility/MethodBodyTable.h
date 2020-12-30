#ifndef MethodBodyTable_NAME_H
#define MethodBodyTable_NAME_H

#include "../declarations/platform.h"
#include "../declarations/symbol/symbol.h"
#include "../declarations/tuple.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>

class AstDeclared;

class MethodBodyAddr
{
friend class MethodBodyTable;

public:
     MethodBodyAddr(wchar_t* pkg, wchar_t* cls, wchar_t* mtd, AstDeclared* ptr)
         : ast_location(ptr), package_name(pkg), class_name(cls), method_name(mtd) {}

     ~MethodBodyAddr();	
private:
     AstDeclared* ast_location;
     wchar_t* package_name;
     wchar_t* class_name;
     wchar_t* method_name;     
};

class MethodBodyTable
{
public:
    MethodBodyTable()
    {
        table = new vector<MethodBodyAddr*>();
    }
    ~MethodBodyTable() { delete table; }

    void addMethodBodyAddr(wchar_t*, wchar_t*, wchar_t*, AstDeclared*);
    wchar_t* getClassNameAt(int i) {return (*table )[i] -> class_name;}
    wchar_t* getMethodNameAt(int i) {return (*table )[i] -> method_name;}
    AstDeclared* getAstLocationAt(int i) {return (*table)[i] -> ast_location;}
    wchar_t* getPackageNameAt(int i) {return (*table)[i] -> package_name;}
    vector<wchar_t*>* getModifiersAt(int i);
    AstDeclared* getAstLocation(wchar_t*, wchar_t*);
    int getSize() {return table -> size();}
    void dumpTable();
private:
    vector<MethodBodyAddr*>* table;
};


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif