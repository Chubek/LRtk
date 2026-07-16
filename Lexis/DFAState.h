#if !defined(_Lexis_DFAState_h)
#define _Lexis_DFAState_h

#include <iostream>
#include <string>
#include "Lexis/State.h"
#include "Lexis/NFA.h"
#include "Toolbox/Set.h"

  using namespace Toolbox;

namespace Lexis
{
    class DFAState : public State
    {
        private: Set const nfaStateSet;
        private: vector<StateNumber> transition;
        public: DFAState(StateNumber, NFA const&, Set const&);
        public: ~DFAState();
        public: DFAState& addTransition(char, StateNumber);
        public: StateNumber getNextState(char) const;
        public: Set getNFAStateSet() const;
        public: ostream& put(ostream&) const;
    };
    inline Set DFAState::getNFAStateSet() const
        { return nfaStateSet; }
    inline ostream& operator<<(ostream& stream, DFAState const& state)
        { return state.put(stream); }
}

  #endif
