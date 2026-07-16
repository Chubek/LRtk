#if !defined(_Toolbox_String_h)
#define _Toolbox_String_h

  #include <string>
  #include <stdint.h>

namespace Toolbox
{
    namespace String
    {
        uint16_t hash(string const& s);
        uint16_t getWidth(string const& s);
    }
}

  #endif
