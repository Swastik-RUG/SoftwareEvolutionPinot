#ifndef Gen_NAME_H
#define Gen_NAME_H

#include "platform.h"
#include "symbol.h"
#include "tuple.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

#include <vector>

    class Gen
    {
        friend class GenTable;

    public:
        enum Kind
        {
            CLASS,
            INTERFACE,
            ABSTRACT,
            FINAL
        };

        Gen(wchar_t *pkg, wchar_t *cls, wchar_t *spr, vector<wchar_t *> *ifcs, Kind k, char *f)
            : class_name(cls), super_name(spr), interfaces(ifcs), kind(k), package_name(pkg), file_name(f)
        {
        }
        ~Gen();

    private:
        wchar_t *class_name;
        wchar_t *super_name;
        vector<wchar_t *> *interfaces;
        Kind kind;
        wchar_t *package_name;
        char *file_name;
    };

    class GenTable
    {
    public:
        enum Kind
        {
            SUBC, // Subclass
            IMPL  // Implmentor
        };

        GenTable()
        {
            table = new vector<Gen *>();
        }
        ~GenTable() { delete table; }

        void addGeneralization(wchar_t *, wchar_t *, wchar_t *, vector<wchar_t *> *, Gen::Kind, char *);
        wchar_t *getSuper(wchar_t *, wchar_t *);
        vector<wchar_t *> *getAncestors(Kind, wchar_t *, wchar_t *);
        vector<wchar_t *> *getInterfaces(wchar_t *, wchar_t *);
        vector<wchar_t *> *getSuccessors(wchar_t *, Kind);
        bool hasSuccessors(wchar_t *, Kind);
        Gen::Kind getKind(wchar_t *, wchar_t *);
        wchar_t *getClassNameAt(int i) { return (*table)[i]->class_name; }
        wchar_t *getPackageNameAt(int i) { return (*table)[i]->package_name; }
        Gen::Kind getKindAt(int i) { return (*table)[i]->kind; }
        char *getFileName(wchar_t *, wchar_t *);
        int getSize() { return table->size(); }
        void dumpTable();

    private:
        vector<Gen *> *table;
    };

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif