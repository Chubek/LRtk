#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <climits>
#include <cassert>
#include "Toolbox/Set.h"

namespace Toolbox
{
    Set::Set(uint16_t size) :
        data((size + CHAR_BIT - 1U) >> divShift, 0),
        fill(0)
        {}
    Set::~Set()
        {}
    Set::Set(Set const& s) :
        data(s.data),
        fill(s.fill)
        {}
    Set& Set::enlarge(uint16_t size)
    {
        if (data.size() < size)
        {
            data.resize(size, fill);
        }
        return *this;
    }
    Set& Set::operator=(Set const& s)
    {
        if (this != &s)
        {
            data = s.data;
            fill = s.fill;
        }
        return *this;
    }
    Set& Set::operator=(uint16_t arg)
    {
        assert(arg == 0);
        for (uint16_t i = 0; i < data.size(); ++i)
            data[i] = 0;
        fill = 0;
        return *this;
    }
    Set Set::operator|(Set const& s) const
    {
        Set result(*this);
        result |= s;
        return result;
    }
    Set& Set::operator|=(Set const& s)
    {
        enlarge(s.data.size());
        uint16_t i;
        for (i = 0; i < s.data.size(); ++i)
            data[i] |= s.data[i];
        for ( ; i < data.size(); ++i)
            data[i] |= s.fill;
        fill |= s.fill;
        return *this;
    }
    Set Set::operator&(Set const& s) const
    {
        Set result(*this);
        result &= s;
        return result;
    }
    Set& Set::operator&=(Set const& s)
    {
        enlarge(s.data.size());
        uint16_t i;
        for (i = 0; i < s.data.size(); ++i)
            data[i] &= s.data[i];
        for ( ; i < data.size(); ++i)
            data[i] &= s.fill;
        fill &= s.fill;
        return *this;
    }
    Set Set::operator^(Set const& s) const
    {
        Set result(*this);
        result ^= s;
        return result;
    }
    Set& Set::operator^=(Set const& s)
    {
        enlarge(s.data.size());
        uint16_t i;
        for (i = 0; i < s.data.size(); ++i)
            data[i] ^= s.data[i];
        for ( ; i < data.size(); ++i)
            data[i] ^= s.fill;
        fill ^= s.fill;
        return *this;
    }
    Set& Set::operator+=(uint16_t i)
    {
        uint16_t const byte = i >> divShift;
        uint16_t const bit = i & modMask;
        enlarge(byte + 1);
        data[byte] |= 1 << bit;
        return *this;
    }
    Set& Set::operator-=(uint16_t i)
    {
        uint16_t const byte = i >> divShift;
        uint16_t const bit = i & modMask;
        enlarge(byte + 1);
        data[byte] &= ~(1 << bit);
        return *this;
    }
    Set Set::operator~() const
    {
        Set result(*this);
        for (uint16_t i = 0; i < result.data.size(); ++i)
            result.data[i] = ~result.data[i];
        result.fill = ~result.fill;
        return result;
    }
    bool Set::operator==(Set const& s) const
    {
        if (data.size() <= s.data.size())
        {
             uint16_t i;
             for (i = 0; i < data.size(); ++i)
                 if (data[i] != s.data[i])
                      return false;
             for ( ; i < s.data.size(); ++i)
                 if (fill != s.data[i])
                      return false;
        }
        else
        {
             uint16_t i;
             for (i = 0; i < s.data.size(); ++i)
                 if (data[i] != s.data[i])
                      return false;
             for ( ; i < data.size(); ++i)
                 if (data[i] != s.fill)
                      return false;
        }
        if (fill != s.fill)
             return false;
        return true;
    }
    bool Set::operator!=(Set const& s) const
        { return !Set::operator==(s); }
    bool Set::operator<=(Set const& s) const
    {
        if (data.size() <= s.data.size())
        {
             uint16_t i;
             for (i = 0; i < data.size(); ++i)
                 if ((data[i] & s.data[i]) != data[i])
                      return false;
             for ( ; i < s.data.size(); ++i)
                 if ((fill & s.data[i]) != fill)
                      return false;
        }
        else
        {
             uint16_t i;
             for (i = 0; i < s.data.size(); ++i)
                 if ((data[i] & s.data[i]) != data[i])
                      return false;
             for ( ; i < data.size(); ++i)
                 if ((data[i] & s.fill) != data[i])
                      return false;
        }
        if ((fill & s.fill) != fill)
             return false;
        return true;
    }
    bool Set::operator==(int arg) const
    {
        assert(arg == 0);
        for (uint16_t i = 0; i < data.size(); ++i)
            if (data[i] != 0)
                 return false;
        if (fill != 0)
            return false;
        return true;
    }
    bool Set::operator!=(int arg) const
        { return !Set::operator==(arg); }
    bool Set::contains(uint16_t i) const
    {
        uint16_t const byte = i >> divShift;
        uint16_t const bit = i & modMask;
        if (byte < data.size())
             return (data[byte] & (1 << bit)) != 0;
        else
             return fill != 0;
    }
    uint32_t Set::getSize() const
    {
        uint32_t result = 0;
        for (uint16_t i = 0; i < data.size(); ++i)
        {
            uint8_t c = data[i];
            while (c != 0)
            {
                 c = c & (c ^ ((~c) + 1));
                 result += 1;
            }
        }
        if (fill != 0)
            result += UINT16_MAX + 1L - (data.size() << divShift);
        return result;
    }
    ostream& Set::put(ostream& s) const
    {
        bool comma = false;

          s << "{";
          for (uint16_t i = 0; i < data.size(); ++i)
          {
              for (uint16_t bit = 0; bit < CHAR_BIT; ++bit)
              {
                  if ((data[i] & (1 << bit)) != 0)
                  {
                      if (comma)
                          s << ",";
                      s << ((i << divShift) | bit);
                      comma = true;
                  }
              }
          }
          if (fill != 0)
              s << "...";
          s << "}";
          return s;
      }
    Set::const_iterator Set::begin() const
    {
        for (uint16_t i = 0; i < data.size(); ++i)
        {
             for (uint16_t bit = 0; bit < CHAR_BIT; ++bit)
             {
                 if ((data[i] & (1 << bit)) != 0)
                 {
                      uint16_t referent = (i << divShift) | bit;
                      return const_iterator(this, referent);
                 }
             }
        }
        if (fill != 0)
        {
             uint16_t referent = data.size() << divShift;
             return const_iterator(this, referent);
        }
        else
        {
             return const_iterator(this, UINT16_MAX);
        }
    }
    Set::const_iterator& Set::const_iterator::operator++()
    {
         ++referent;
         for (;;)
         {
             uint16_t const byte = referent >> Set::divShift;
             if (byte < set->data.size())
             {
                 uint16_t const bit = referent & Set::modMask;
                 if ((set->data[byte] & (1 << bit)) != 0)
                 {
                      break;
                 }
             }
             else
             {
                 if (set->fill == 0)
                 {
                      referent = UINT16_MAX;
                 }
                 break;
             }
             ++referent;
         }
         return *this;
    }
}
