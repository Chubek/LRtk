#if !defined(_Lexis_ItemAttributes_h)
#define _Lexis_ItemAttributes_h

  #include <string>
  #include "Lexis/NFA.h"

  using namespace Toolbox;
  using namespace Toolbox::String;

namespace Lexis
{
    class ItemAttributes
    {
        public: NFA* nfa;
        public: string language;
        public: ItemAttributes();
    };
    inline ItemAttributes::ItemAttributes() :
        nfa(0),
        language()
        {}
}

  #endif
