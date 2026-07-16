#if !defined(_Lexis_ParserData_h)
#define _Lexis_ParserData_h

#include <string>
#include "Lexis/NFA.h"
#include "Toolbox/HashTable.h"
#include "Toolbox/String.h"

  using namespace Toolbox;
  using namespace Toolbox::String;

namespace Lexis
{
    class ParserData
    {
        protected: HashTable<string,NFA*> definitionsTable;
        protected: ParserData();
    };
    inline ParserData::ParserData() :
        definitionsTable()
        {}
}

  #endif
