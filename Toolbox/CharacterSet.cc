#include <iostream>
#include <limits.h>
#include "Toolbox/CharacterSet.h"
#include "Toolbox/EscapeSequence.h"

  using namespace Toolbox;

namespace Toolbox
{
    ostream& CharacterSet::put(ostream& s) const
    {
        s << "{\"";
        for (uint16_t i = 0; i < data.size(); ++i)
        {
            for (uint16_t bit = 0; bit < CHAR_BIT; ++bit)
            {
                if ((data[i] & (1 << bit)) != 0)
                    s << EscapeSequence::encode(
                         (i << divShift) | bit, '"');
            }
        }
        s << "\"";
        if (fill != 0)
            s << "...";
        s << "}";
        return s;
    }
}
