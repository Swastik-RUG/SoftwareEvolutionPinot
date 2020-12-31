#ifndef Assoc_NAME_H
#define Assoc_NAME_H

#include "../declarations/platform/platform.h"
#include "../declarations/symbol/symbol.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>

    class Assoc
    {
        friend class AssocTable;

    public:
        enum Kind
        {
            CF, // Class Field, assocates with a mode
            IM, // Instance Member, assocates with a mode
            MP, // Method Parameter, assicoates with a method
            MI, // Method Invocation, called method is in name, invoker is in type
            OC, // Object Creation, assicoates with a method. No name entry
            MR, // Method Return Type, associates with a method
            CM  // Class Method Return Type, associates with a method
        };

        enum Mode
        {
            PRIVATE,
            PROTECTED,
            PUBLIC
        };

        Assoc(Kind k, Mode m, wchar_t *n, wchar_t *t, wchar_t *pkg, wchar_t *cls, wchar_t *mtd)
            : kind(k), mode(m), name(n), type(t), package_name(pkg), class_name(cls), method_name(mtd)
        {
        }
        ~Assoc();

    private:
        Kind kind;
        Mode mode;
        wchar_t *name;
        wchar_t *type;
        wchar_t *package_name;
        wchar_t *class_name;
        wchar_t *method_name;
    };

    class AssocTable
    {
    public:
        AssocTable()
        {
            table = new vector<Assoc *>();
        }
        ~AssocTable() { delete table; }

        void addAssociation(Assoc::Kind, Assoc::Mode, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);
        bool isAssociated(wchar_t *, wchar_t *);
        Assoc::Kind getKindAt(int i) { return (*table)[i]->kind; }
        Assoc::Mode getModeAt(int i) { return (*table)[i]->mode; }
        wchar_t *getNameAt(int i) { return (*table)[i]->name; }
        wchar_t *getTypeAt(int i) { return (*table)[i]->type; }
        wchar_t *getClassNameAt(int i) { return (*table)[i]->class_name; }
        wchar_t *getMethodNameAt(int i) { return (*table)[i]->method_name; }
        wchar_t *getPackageNameAt(int i) { return (*table)[i]->package_name; }
        wchar_t *getName(Assoc::Kind, Assoc::Mode, wchar_t *, wchar_t *);
        bool isInvoked(wchar_t *, wchar_t *);
        wchar_t *getType(Assoc::Kind, Assoc::Mode, wchar_t *, wchar_t *, wchar_t *);
        int getSize() { return table->size(); }
        void dumpTable();

    private:
        vector<Assoc *> *table;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif