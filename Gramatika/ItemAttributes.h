#if !defined(_Gramatika_ItemAttributes_h)
#define _Gramatika_ItemAttributes_h

#include <list>
#include <string>
#include "Gramatika/Symbol.h"
#include "Gramatika/Production.h"
#include "Gramatika/SymbolTable.h"

namespace Gramatika
{
    class ItemAttributes
    {
        public: union
        {
            Production* production;
            list<Production*>* productionList;
            Symbol* symbol;
            SymbolTable* symbolTable;
            string* language;
        };
        public: ItemAttributes();
    };
    inline ItemAttributes::ItemAttributes()
        { symbolTable = 0; }
}

  #endif
