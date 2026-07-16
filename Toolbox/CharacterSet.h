#if !defined(_Toolbox_CharacterSet_h)
#define _Toolbox_CharacterSet_h

  #include <stdint.h>
  #include "Toolbox/Set.h"

namespace Toolbox
{
    class CharacterSet : public Set
    {
        public: explicit CharacterSet(uint16_t = 1);
        public: CharacterSet(Set const&);
        public: CharacterSet(CharacterSet const&);
        public: ostream& put(ostream&) const;
    };
    inline CharacterSet::CharacterSet(uint16_t size) :
        Set(size)
        {}
    inline CharacterSet::CharacterSet(Set const& s) :
        Set(s)
        {}
    inline CharacterSet::CharacterSet(CharacterSet const& s) :
        Set(s)
        {}
    inline ostream& operator<<(ostream& stream, CharacterSet const& set)
        { return set.put(stream); }
}

  #endif
