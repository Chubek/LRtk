#include <ctype.h>
#include <limits.h>
#include <cstdint>
#include "Toolbox/String.h"
#include "Toolbox/fixwarn.h"

namespace Toolbox
{
    namespace String
    {
        uint16_t const UINT16_BITS = sizeof(uint16_t) * CHAR_BIT;
        uint16_t const oneEighth = UINT16_BITS / 8;
        uint16_t const threeQuarters = UINT16_BITS * 3 / 4;
        uint16_t const highBits = (UINT16_MAX >> oneEighth);
        uint16_t hash(string const& s)
        {
             uint16_t hash = 0;

              for (string::const_iterator ptr(s.begin()), lim(s.end());
                      ptr != lim; ++ptr)
              {
                  hash = (hash << oneEighth) + *ptr;
                  uint16_t const top = hash & highBits;
                  if ((hash & highBits) != 0)
                      hash = (hash ^ (top >> threeQuarters)) & ~highBits;
              }
              return hash;
          }
        uint16_t getWidth(string const& s)
        {
            uint16_t result = 0;
            for (string::const_iterator p(s.begin()), lim(s.end());
                     p != lim; ++p)
            {
                 if (*p == '\t')
                     result = (result + 8U) & ~07U;
                 else if (isprint(*p))
                     result += 1U;
            }
            return result;
        }
    }
}
