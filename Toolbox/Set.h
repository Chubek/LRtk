#if !defined(_Toolbox_Set_h)
#define _Toolbox_Set_h

#include <iostream>
#include <vector>
#include <stdint.h>

namespace Toolbox
{
    class Set
    {
          public: class const_iterator
          {
                private: Set const* set;
                private: uint16_t referent;
                public: const_iterator();
                public: const_iterator(Set const*, uint16_t);
                public: const_iterator(const_iterator const& i);
                public: uint16_t operator*() const;
                public: const_iterator& operator++();
                public: bool operator!=(const_iterator const&) const;
                public: bool operator<(const_iterator const&) const;
                friend class Set;
          };
          protected: enum Constants
          {
               divShift = 3,
               modMask = 0x07
          };
          protected: vector<uint8_t> data;
          protected: uint8_t fill;
          protected: Set& enlarge(uint16_t);
          public: explicit Set(uint16_t = 1);
          public: ~Set();
          public: Set(Set const&);
          public: Set& operator=(Set const&);
          public: Set& operator=(uint16_t);
          public: Set operator|(Set const&) const;
          public: Set& operator|=(Set const&);
          public: Set operator&(Set const&) const;
          public: Set& operator&=(Set const&);
          public: Set operator^(Set const&) const;
          public: Set& operator^=(Set const&);
          public: Set& operator+=(uint16_t);
          public: Set& operator-=(uint16_t);
          public: Set operator~() const;
          public: bool operator==(Set const&) const;
          public: bool operator!=(Set const&) const;
          public: bool operator<=(Set const&) const;
          public: bool operator==(int) const;
          public: bool operator!=(int) const;
          public: bool contains(uint16_t) const;
          public: uint32_t getSize() const;
          public: ostream& put(ostream&) const;
          public: const_iterator begin() const;
          friend class const_iterator;
    };
    inline ostream& operator<<(ostream& stream, Set const& set)
          { return set.put(stream); }
    inline Set::const_iterator::const_iterator() :
          set(0),
          referent(UINT16_MAX)
          {}
    inline Set::const_iterator::const_iterator(const_iterator const& i) :
          set(i.set),
          referent(i.referent)
          {}
    inline Set::const_iterator::const_iterator(
          Set const* _set, uint16_t _referent) :
          set(_set),
          referent(_referent)
          {}
    inline uint16_t Set::const_iterator::operator*() const
          { return referent; }
    inline bool Set::const_iterator::operator!=(const_iterator const& i) const
          { return referent != i.referent; }
    inline bool Set::const_iterator::operator<(const_iterator const& i) const
          { return referent < i.referent; }
}

  #endif
