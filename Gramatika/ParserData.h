#if !defined(_Gramatika_ParserData_h)
#define _Gramatika_ParserData_h

  #include "Gramatika/SymbolTable.h"

namespace Gramatika
{
    class ParserData
    {
        protected: SymbolTable* symbolTable;
        protected: ParserData();
    };
    inline ParserData::ParserData() :
        symbolTable(new SymbolTable())
        {}
}

  #endif
