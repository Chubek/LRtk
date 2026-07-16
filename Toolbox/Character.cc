#include <ctype.h>
#include <cassert>
#include "Toolbox/Character.h"
#include "fixwarn.h"

namespace Toolbox
{
    namespace Character
    {
        char octalToBinary(char c)
        {
            assert(isOctalDigit(c));
            return c - '0';
        }
        char hexToBinary(char c)
        {
            assert(isxdigit(c));
            if (isdigit(c))
                 return c - '0';
            else
                 return toupper(c) - 'A' + 10;
        }
        bool isOctalDigit(char c)
            { return isdigit(c) && c < '8'; }
    }
}
