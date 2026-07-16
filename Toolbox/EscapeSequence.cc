#include <ctype.h>
#include <stdint.h>
#include <cassert>
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/Character.h"
#include "fixwarn.h"

  using namespace Toolbox::Character;

namespace Toolbox
{
    namespace EscapeSequence
    {
        string encode(char c, char delimiter)
        {
            string result;

              if (isprint(c))
              {
                   if (c == '\\' || c == delimiter)
                       result += '\\';
                   result += c;
              }
              else
              {
                   result += '\\';
                   switch (c)
                   {
                       case '\n': result += 'n'; break;
                       case '\t': result += 't'; break;
                       case '\b': result += 'b'; break;
                       case '\v': result += 'v'; break;
                       case '\r': result += 'r'; break;
                       case '\f': result += 'f'; break;
                       case '\a': result += 'a'; break;
                       default:
                           {
                               char buffer[3];
                               int16_t count = 0;
                               do
                               {
                                    assert(count < 3);
                                    buffer[count++] = '0' + (c & 07);
                                    c = static_cast<uint8_t>(c) >> 3;
                               }
                               while (c != 0);

                                 do { result += buffer[--count]; }
                                 while (count != 0);
                             }
                           break;
                  }
              }
              return result;
          }
        string encode(string const& s, char delimiter)
        {
            string result;
            for(string::const_iterator p(s.begin()), lim(s.end());
                     p != lim; ++p)
                result += encode(*p, delimiter);
            return result;
        }
        string decode(string const& s)
        {
            string result;
            string::const_iterator ptr(s.begin()), lim(s.end());
            while (ptr != lim)
            {
                char c = *ptr++;
                if (c == '\\')
                {
                    if (ptr == lim)
                    {
                         result += c;
                         break;
                    }
                    c = *ptr++;
                    switch (c)
                    {
                         case 'n': c = '\n'; break;
                         case 't': c = '\t'; break;
                         case 'v': c = '\v'; break;
                         case 'b': c = '\b'; break;
                         case 'r': c = '\r'; break;
                         case 'f': c = '\f'; break;
                         case 'a': c = '\a'; break;
                         case '0': case '1': case '2': case '3':
                         case '4': case '5': case '6': case '7':
                             {
                                 c = octalToBinary(c);
                                 if (ptr != lim && isOctalDigit(*ptr))
                                 {
                                     c = (c << 3) + octalToBinary(*ptr++);
                                     if (ptr != lim && isOctalDigit(*ptr))
                                          c = (c << 3) + octalToBinary(*ptr++);
                                 }
                             }
                             break;
                         case 'x':
                             {
                                 if (ptr != lim && isxdigit(*ptr))
                                 {
                                     c = hexToBinary(*ptr++);
                                     while (ptr != lim && isxdigit(*ptr))
                                     {
                                          c = (c << 4) + hexToBinary(*ptr++);
                                     }
                                 }
                             }
                             break;
                         default:
                             break;
                    }
                }
                result += c;
            }
            return result;
        }
    }
}
