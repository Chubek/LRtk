#include <iostream>
#include "Lexis/State.h"

namespace Lexis
{
    State& State::operator=(State const& s)
    {
        anchor = s.anchor;
        action = s.action;
        token = s.token;
        return *this;
    }
    void State::setNumber(StateNumber n)
        { number = n; }
    void State::setAnchor(Anchor a)
        { anchor = a; }
    void State::setAction(Action a)
        { action = a; }
    void State::setToken(string const& s)
        { token = s; }
    ostream& State::put(ostream& s) const
    {
        s << "number = " << number;
        s << ", anchor = " << anchor;
        s << ", action = " << action;
        return s;
    }
}
