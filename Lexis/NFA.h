#if !defined(_Lexis_NFA_h)
#define _Lexis_NFA_h

#include <iostream>
#include <vector>
#include <string>
#include "Lexis/NFAState.h"
#include "Toolbox/CharacterSet.h"

  using namespace Toolbox;

namespace Lexis
{
    class NFA
    {
          public: string language;
          public: StateNumber const numberOfStates;
          public: vector<NFAState> state;
          public: explicit NFA(StateNumber = 1);
          public: explicit NFA(string const&);
          public: explicit NFA(CharacterSet const&);
          public: NFA(NFA const&);
          public: ~NFA();
          public: NFAState const& operator[](StateNumber) const;
          public: NFAState& operator[](StateNumber);
          public: StateNumber getNumberOfStates() const;
          public: void setAnchor(Anchor);
          public: void setAction(Action);
          public: void setToken(string const&);
          public: void setLanguage(string const&);
          public: ostream& put(ostream&) const;
          public: Set getEpsilonClosure(Set const&) const;
          public: Set getMoveSet(Set const&, char) const;
          public: Action getDominantAction(Set const&) const;
          public: Anchor getDominantAnchor(Set const&) const;
          public: string getDominantToken(Set const&) const;
          public: string const& getLanguage() const;
          friend NFA operator*(NFA const&, NFA const&);
          friend NFA operator|(NFA const&, NFA const&);
          friend NFA operator!(NFA const&);
          friend NFA operator~(NFA const&);
    };
    inline void NFA::setLanguage(string const& s)
          { language = s; }
    inline string const& NFA::getLanguage() const
          { return language; }
    inline StateNumber NFA::getNumberOfStates() const
          { return numberOfStates; }
    inline ostream& operator<<(ostream& stream, NFA const& nfa)
          { return nfa.put(stream); }
}

  #endif
