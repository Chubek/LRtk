#if !defined(_Lexis_NFAState_h)
#define _Lexis_NFAState_h

#include <iostream>
#include <vector>
#include <string>
#include "Lexis/State.h"
#include "Toolbox/CharacterSet.h"

  using namespace Toolbox;

namespace Lexis
{
    class NFAState : public State
    {
        public: enum LabelType
        {
            epsilon,
            character,
            characterSet
        };
        private: enum Constants
        {
            maximumFanout = 2
        };
        private: uint8_t fanout;
        private: int16_t next[maximumFanout];
        private: LabelType labelType;
        private: char labelChar;
        private: CharacterSet labelSet;
        public: NFAState();
        public: NFAState& operator=(NFAState const&);
        public: void connect(StateNumber);
        public: void connect(StateNumber, StateNumber);
        public: void connect(char, StateNumber);
        public: void connect(CharacterSet const&, StateNumber);
        public: uint8_t getFanout() const;
        public: LabelType getLabelType() const;
        public: bool isTransitionLabelled(char) const;
        public: StateNumber getNextState(uint8_t) const;
        public: ostream& put(ostream&) const;
    };
    inline NFAState::NFAState() :
        State(),
        fanout(0),
        labelType(epsilon),
        labelChar(0),
        labelSet()
        {}
    inline uint8_t NFAState::getFanout() const
        { return fanout; }
    inline NFAState::LabelType NFAState::getLabelType() const
        { return labelType; }
    inline ostream& operator<<(ostream& stream, NFAState const& state)
        { return state.put(stream); }
}

  #endif
