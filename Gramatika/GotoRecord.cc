#include <iostream>
#include "Gramatika/GotoRecord.h"

namespace Gramatika
{
    GotoRecord::GotoRecord(SymbolNumber sym, StateNumber state)
    {
        symbol = sym;
        action = 0;
        number = state;
    }
    int GotoRecord::compare(GotoRecord const& arg) const
    {
        int result = symbol - arg.symbol;
        if (result != 0)
            return result;
        return number - arg.number;
    }
    ostream& GotoRecord::put(ostream& s) const
    {
        s << "Goto { symbol = " << static_cast<uint16_t>(symbol);
        s << ", state = " << static_cast<uint16_t>(number);
        return s << " }";
    }
}
