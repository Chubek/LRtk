#include <iostream>
#include "Lexis/DFAState.h"
#include "Lexis/DFA.h"
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/CharacterSet.h"

  using namespace Toolbox;

namespace Lexis
{
    DFAState::DFAState(StateNumber n, NFA const& nfa, Set const& s) :
        State(n, nfa.getDominantAnchor(s),
             nfa.getDominantAction(s), nfa.getDominantToken(s)),
        nfaStateSet(s),
        transition(maximumCharacter)
    {
        for (uint8_t i = 0; i < maximumCharacter; ++i)
             transition[i] = errorState;
    }
    DFAState::~DFAState()
        {}
    DFAState& DFAState::addTransition(char c, StateNumber to)
    {
        assert(static_cast<uint8_t>(c) < maximumCharacter);
        transition[c] = to;
        return *this;
    }
    StateNumber DFAState::getNextState(char c) const
    {
        assert(static_cast<uint8_t>(c) < maximumCharacter);
        return transition[c];
    }
    ostream& DFAState::put(ostream& s) const
    {
        s << "DFAState {";
        State::put(s);
        s << "\n";
        for (StateNumber n = 0; n < DFA::maximumNumberOfStates; ++n)
        {
            CharacterSet set;
            for (uint8_t c = 0; c < maximumCharacter; ++c)
                 if (transition[c] == n)
                     set += c;
            if (set != 0)
            {
                 cout << " goto " << n;
                 cout << " on " << set << "\n";
            }
        }
        return s << "}\n";
    }
}
