#if !defined(_Loma_Output_h)
#define _Loma_Output_h

  #include <string>
  #include <stdint.h>

namespace Loma
{
    string textIndent(uint16_t);
    string texIndent(uint16_t);
    string texCode(string const&);
    string clearText(string const&);
    string noBlanks(string const&);
}

  #endif
