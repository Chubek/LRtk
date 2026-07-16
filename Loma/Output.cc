#include <string>
#include <ctype.h>
#include "Loma/Output.h"
#include <cctype>
#include "Toolbox/fixwarn.h"

namespace Loma
{
    string textIndent(uint16_t indent)
    {
         string result;

          for (uint16_t i = indent / 8; i > 0; --i)
              result += "\t";
          for (uint16_t i = indent % 8; i > 0; --i)
              result += " ";
          return result;
      }
    string texIndent(uint16_t indent)
    {
         string result;

          for (uint16_t i = 0; i < indent; i += 4)
              result += "\\> ";
          return result;
      }
    string texCode(string const& t)
    {
         string result;

          for (string::const_iterator p(t.begin()), lim(t.end()); p != lim; ++p)
          {
              char const c = *p;
              switch (c)
              {
                  case '$': case '{': case '}': case '%':
                  case '&': case '#': case '_': case '\\':
                  case '~': case '^':
                  case '.': case '!': case '?': case ':':
                      result += "\\verb’";
                      result += c;
                      result += "’"; break;
                  default:
                      result += c;
                      break;
              }
          }
          return result;
      }
    string clearText(string const& t)
    {
         string result;

          string::const_iterator p(t.begin()), lim(t.end());
          while (p != lim)
          {
              if (*p == '\\')
                   {
                       ++p;
                       while (p != lim && isalpha(*p))
                           ++p;
                  }
              else if (isspace(*p))
                  {
                       if (result.size() != 0 &&
                                result [result.size() - 1U] != ' ')
                           result += ' ';
                       ++p;
                  }
              else if (isalnum(*p) || *p == '.')
                  {
                       result += *p;
                       ++p;
                  }
              else
                  ++p;
          }
          return result;
      }
    string noBlanks(const string& t)
    {
         string result;

          for (string::const_iterator p(t.begin()), lim(t.end()); p != lim; ++p)
          {
              if (!isspace(*p))
                  result += *p;
          }
          return result;
      }
}
