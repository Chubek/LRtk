#include <iostream>
#include "Lexis/NFA.h"
#include "Lexis/NFAState.h"
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/Stack.h"

namespace Lexis
{
    NFA::NFA(StateNumber states) :
          numberOfStates(states),
          state(numberOfStates)
    {
          for (StateNumber n = 0; n < numberOfStates; ++n)
              state[n].setNumber(n);
    }
    NFA::NFA(string const& s) :
          numberOfStates(s.size() + 1),
          state(numberOfStates)
    {
          for (StateNumber n = 0; n < numberOfStates; ++n)
              state[n].setNumber(n);
          for (StateNumber n = 0; n < numberOfStates - 1U; ++n)
              state[n].connect(s[n], n + 1);
    }
    NFA::NFA(CharacterSet const& s) :
          numberOfStates(2),
          state(2)
    {
          for (StateNumber n = 0; n < numberOfStates; ++n)
              state[n].setNumber(n);
          state[0].connect(s, 1);
    }
    NFA::NFA(NFA const& nfa) :
         numberOfStates(nfa.numberOfStates),
         state(numberOfStates)
    {
         for (StateNumber n = 0; n < numberOfStates; ++n)
         {
             state[n].setNumber(n);
             state[n] = nfa.state[n];
         }
    }
    NFA::~NFA()
          {}
    NFAState const& NFA::operator[](StateNumber n) const
    {
          assert(n < numberOfStates);
          return state[n];
    }
    NFAState& NFA::operator[](StateNumber n)
    {
          assert(n < numberOfStates);
          return state[n];
    }
    void NFA::setAnchor(Anchor a)
    {
          assert(numberOfStates > 0);
          state[numberOfStates - 1].setAnchor(a);
    }
    void NFA::setAction(Action a)
    {
          assert(numberOfStates > 0);
          state[numberOfStates - 1].setAction(a);
    }
    void NFA::setToken(string const& s)
    {
          assert(numberOfStates > 0);
          state[numberOfStates - 1].setToken(s);
    }
    ostream& NFA::put(ostream& s) const
    {
          for (StateNumber n = 0; n < numberOfStates; ++n)
              s << state[n];
          return s;
    }
    Set NFA::getEpsilonClosure(Set const& inputSet) const
    {
          Stack<StateNumber> stack;

          Set result(inputSet);

          for (Set::const_iterator p(inputSet.begin()), null; p != null; ++p)
          {
              stack.push(*p);
          }

          while (!stack.isEmpty())
          {
              StateNumber const s = stack.pop();
              if (state[s].getLabelType() == NFAState::epsilon)
              {
                  for (uint8_t i = 0;
                      i < state[s].getFanout(); ++i)
                  {
                      StateNumber const next =
                          state[s].getNextState(i);
                      if (!result.contains(next))
                      {
                          result += next;
                          stack.push(next);
                      }
                  }
              }
          }
          return result;
      }
    Set NFA::getMoveSet(Set const& inputSet, char c) const
    {
          Set result;

          for (Set::const_iterator p(inputSet.begin()), null; p != null; ++p)
          {
              StateNumber const s = *p;
              if (state[s].isTransitionLabelled(c))
              {
                  assert(state[s].getFanout() == 1);
                  result += state[s].getNextState(0);
              }
          }
          return result;
      }
    Action NFA::getDominantAction(Set const& inputSet) const
    {
         for (Set::const_iterator p(inputSet.begin()), null; p != null; ++p)
         {
             Action const a = state[*p].getAction();
             if (a != advance)
                 return a;
         }
         return advance;
    }
    Anchor NFA::getDominantAnchor(Set const& inputSet) const
    {
         for (Set::const_iterator p(inputSet.begin()), null; p != null; ++p)
         {
             Action const a = state[*p].getAction();
             if (a != advance)
                 return state[*p].getAnchor();
         }
         return none;
    }
    string NFA::getDominantToken(Set const& inputSet) const
    {
         for (Set::const_iterator p(inputSet.begin()), null; p != null; ++p)
         {
             Action const a = state[*p].getAction();
             if (a != advance)
                 return state[*p].getToken();
         }
         return "";
    }
    NFA operator*(NFA const& nfa0, NFA const& nfa1)
    {
         StateNumber const size0 = nfa0.getNumberOfStates();
         StateNumber const size1 = nfa1.getNumberOfStates();
         StateNumber const resultSize = size0 + size1 - 1;
         NFA result(resultSize);
         for (StateNumber n = 0; n < size0 - 1U; ++n)
             result[n] = nfa0[n];
         for (StateNumber n = 0; n < size1; ++n)
             result[size0 - 1 + n] = nfa1[n];
         return result;
    }
    NFA operator|(NFA const& nfa0, NFA const& nfa1)
    {
         StateNumber const size0 = nfa0.getNumberOfStates();
         StateNumber const size1 = nfa1.getNumberOfStates();
         StateNumber const resultSize = size0 + size1 + 2;
         NFA result(resultSize);
         result[0].connect(static_cast<StateNumber>(1), 1 + size0);
         for (StateNumber n = 0; n < size0; ++n)
             result[1 + n] = nfa0[n];
         for (StateNumber n = 0; n < size1; ++n)
             result[1 + size0 + n] = nfa1[n];
         result[size0].connect(resultSize - 1);
         result[size0 + size1].connect(resultSize - 1);
         return result;
    }
    NFA operator!(NFA const& nfa)
    {
         StateNumber const size = nfa.getNumberOfStates();
         StateNumber const resultSize = size + 1;
         NFA result(resultSize);
         result[0].connect(static_cast<StateNumber>(1), resultSize - 1);
         for (StateNumber n = 0; n < size; ++n)
             result[1 + n] = nfa[n];
         return result;
    }
    NFA operator~(NFA const& nfa)
    {
         StateNumber const size = nfa.getNumberOfStates();
         StateNumber const resultSize = size + 2;
         NFA result(resultSize);
         result[0].connect(static_cast<StateNumber>(1), resultSize - 1);
         for (StateNumber n = 0; n < size - 1U; ++n)
             result[1 + n] = nfa[n];
         result[size].connect(static_cast<StateNumber>(1), resultSize - 1);
         return result;
    }
}
