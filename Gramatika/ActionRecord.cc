#include <iostream>
#include "Gramatika/ActionRecord.h"

namespace Gramatika
{
    ActionRecord::ActionRecord(SymbolNumber sym, Action act, uint16_t num)
    {
        symbol = sym;
        action = act;
        number = num;
    }
    int ActionRecord::compare(ActionRecord const& arg) const
    {
        int result = symbol - arg.symbol;
        if (result != 0)
            return result;
        result = action - arg.action;
        if (result != 0)
            return result;
        return number - arg.number;
    }
    ostream& ActionRecord::put(ostream& s) const
    {
        s << "Action { symbol = " << static_cast<uint16_t>(symbol);
        s << ", action = " << static_cast<uint16_t>(action);
        switch (action)
        {
            case shiftAction:
                s << ", state = " << number; break;
            case reduceAction:
                s << ", production = " << number; break;
        }
        return s << " }";
    }
}
