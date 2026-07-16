#if !defined(_Lexis_DFA_h)
#define _Lexis_DFA_h

#include <iostream>
#include <string>
#include "Lexis/State.h"
#include "Lexis/NFA.h"
#include "Lexis/DFAState.h"
#include "Toolbox/Set.h"

  using namespace Toolbox;

namespace Lexis
{
    class DFA
    {
          public: enum Constants
          {
               maximumNumberOfStates = errorState - 1
          };
          private: StateNumber numberOfStates;
          private: vector<DFAState*> state;
          private: string language;
          private: StateNumber getStateNumber(Set const&) const;
          private: StateNumber initializeGroups(
                vector<Set>&, vector<StateNumber>&) const;
          private: DFA& rebuild(
                StateNumber, vector<Set> const&, vector<StateNumber> const&);
          public: explicit DFA(NFA const&);
          public: ~DFA();
          public: void minimize();
          public: StateNumber getNumberOfStates() const;
          public: DFAState const& operator[](StateNumber) const;
          public: bool isColumnEquivalent(char, char) const;
          public: bool isRowEquivalent(StateNumber, StateNumber) const;
          public: string const& getLanguage() const;
          public: ostream& put(ostream&) const;
    };
    inline StateNumber DFA::getNumberOfStates() const
          { return numberOfStates; }
    inline string const& DFA::getLanguage() const
          { return language; }
    inline ostream& operator<<(ostream& stream, DFA const& dfa)
          { return dfa.put(stream); }
}

  #endif
