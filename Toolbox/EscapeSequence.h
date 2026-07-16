#if !defined(_Toolbox_EscapeSequence_h)
#define _Toolbox_EscapeSequence_h

#include <string>
#include <ctype.h>
#include "fixwarn.h"

namespace Toolbox
{
    namespace EscapeSequence
    {
        string encode(char, char = 0);
        string encode(string const&, char = 0);
        string decode(string const&);
    }
}

  #endif
