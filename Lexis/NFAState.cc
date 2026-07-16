#include <iostream>
#include "Lexis/NFAState.h"
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/Stack.h"

  using namespace Toolbox;

namespace Lexis
{
    NFAState& NFAState::operator=(NFAState const& s)
    {
        State::operator=(s);
        fanout = s.fanout;
        for (uint8_t i = 0; i < fanout; ++i)
            next[i] = s.next[i];
        labelType = s.labelType;
        labelChar = s.labelChar;
        labelSet = s.labelSet;
        return *this;
    }
    void NFAState::connect(StateNumber nxt)
    {
        fanout = 1;
        next[0] = nxt - number;
        labelType = epsilon;
        labelChar = 0;
        labelSet = CharacterSet(0);
    }
    void NFAState::connect(StateNumber nxt0, StateNumber nxt1)
    {
        fanout = 2;
        next[0] = nxt0 - number;
        next[1] = nxt1 - number;
        labelType = epsilon;
        labelChar = 0;
        labelSet = CharacterSet(0);
    }
    void NFAState::connect(char lab, StateNumber nxt)
    {
        assert(lab != 0);
        fanout = 1;
        next[0] = nxt - number;
        labelType = character;
        labelChar = lab;
        labelSet = CharacterSet(0);
    }
    void NFAState::connect(CharacterSet const& set, StateNumber nxt)
    {
        fanout = 1;
        next[0] = nxt - number;
        labelType = characterSet;
        labelChar = 0;
        labelSet = set;
    }
    bool NFAState::isTransitionLabelled(char c) const
    {
        switch (labelType)
        {
            case epsilon: return false;
            case character: return labelChar == c;
            case characterSet: return labelSet.contains(c);
        }
        assert(false);
        return false;
    }
    StateNumber NFAState::getNextState(uint8_t i) const
    {
        assert(i < fanout);
        return number + next[i];
    }
    ostream& NFAState::put(ostream& s) const
    {
        s << "NFAState {";
        State::put(s);
        s << "\n";
        if (fanout > 0)
        {
            s << " goto ";
            uint8_t i = 0;
            for (;;)
            {
                s << (number + next[i]);
                i += 1;
                if (i == fanout)
                     break;
                s << ", ";
            }
            s << " on ";
            switch (labelType)
            {
                case epsilon:
                     s << "epsilon"; break;
                case character:
                     s << "'" << EscapeSequence::encode(
                          labelChar, '\'') << "'";
                     break;
                case characterSet:
                     s << labelSet; break;
            }
            s << "\n";
        }
        return s << "}\n";
    }
}
