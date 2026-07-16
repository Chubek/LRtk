#include <iostream>
#include "Lexis/DFA.h"
#include "Toolbox/EscapeSequence.h"

namespace Lexis
{
    StateNumber DFA::getStateNumber(Set const& s) const
    {
          for (StateNumber i = 0; i < numberOfStates; ++i)
              if (state[i]->getNFAStateSet() == s)
                  return i;
          return errorState;
    }
    DFA::DFA(NFA const& nfa) :
          numberOfStates(0),
          state(maximumNumberOfStates),
          language(nfa.getLanguage())
    {
          Set nfaStates;
          nfaStates += 0;
          nfaStates = nfa.getEpsilonClosure(nfaStates);

          state[0] = new DFAState(0, nfa, nfaStates);

          numberOfStates = 1;

          for (StateNumber i = 0; i < numberOfStates; ++i)
          {
              cerr << ".";
              DFAState* const current = state[i];
              assert(current != 0);

               for (uint8_t c = 0; c < maximumCharacter; ++c)
               {
                   Set moveSet;
                   moveSet = nfa.getMoveSet(current->getNFAStateSet(), c);
                   moveSet = nfa.getEpsilonClosure(moveSet);

                     StateNumber nextState = errorState;
                     if (moveSet != 0)
                     {
                         nextState = getStateNumber(moveSet);
                         if (nextState == errorState)
                         {
                             assert(numberOfStates < maximumNumberOfStates);
                             state[numberOfStates] =
                                 new DFAState(numberOfStates, nfa, moveSet);
                             nextState = numberOfStates;
                             numberOfStates += 1;
                         }
                         current->addTransition(c, nextState);
                     }
               }
          }
      }
    DFA::~DFA()
    {
          for (StateNumber i = 0; i < numberOfStates; ++i)
              delete state[i];
    }
    DFAState const& DFA::operator[](StateNumber s) const
    {
          assert(s < numberOfStates);
          return *state[s];
    }
    ostream& DFA::put(ostream& s) const
    {
          for (StateNumber i = 0; i < numberOfStates; ++i)
              cout << *state[i];
          return s;
    }
    StateNumber DFA::initializeGroups(
             vector<Set>& group,
             vector<StateNumber>& inGroup) const
    {
         StateNumber numberOfGroups = 0;
         for (StateNumber i = 0; i < numberOfStates; ++i)
         {
             bool found = false;
             StateNumber j;
             for (j = 0; j < i; ++j)
             {
                 if (state[i]->getAction() == state[j]->getAction()
                 && state[i]->getToken() == state[j]->getToken())
                 {
                       found = true;
                       break;
                 }
             }
             if (found)
             {
                 group[inGroup[j]] += i;
                 inGroup[i] = inGroup[j];
             }
             else
             {
                 assert(numberOfGroups < numberOfStates);
                 group[numberOfGroups] += i;
                 inGroup[i] = numberOfGroups;
                 numberOfGroups += 1;
             }
         }
         return numberOfGroups;
    }
    DFA& DFA::rebuild(StateNumber numberOfGroups,
          vector<Set> const& group,
          vector<StateNumber> const& inGroup)
    {
          vector<DFAState*> oldState(state);
          state.resize(numberOfGroups);

          for (StateNumber i = 0; i < numberOfGroups; ++i)
          {
              assert(group[i] != 0);
              Set::const_iterator p(group[i].begin()), null;
              state[i] = oldState[*p];
              state[i]->setNumber(i);
              for (uint8_t c = 0; c < maximumCharacter; ++c)
              {
                  StateNumber const next = state[i]->getNextState(c);
                  if (next != errorState)
                      state[i]->addTransition(c, inGroup[next]);
              }
              for (++p; p != null; ++p)
                  delete oldState[*p];
          }
          numberOfStates = numberOfGroups;
          return *this;
      }
    void DFA::minimize()
    {
          vector<Set> group(numberOfStates);
          vector<StateNumber> inGroup(numberOfStates);

          StateNumber numberOfGroups = initializeGroups(group, inGroup);

          bool done = false;
          while (!done)
          {
              done = true;
              for (StateNumber i = 0; i < numberOfGroups; ++i)
              {
                  if (group[i].getSize() > 1)
                  {
                      Set newGroup;
                      Set::const_iterator p(group[i].begin()), null;
                      StateNumber const first = *p;
                      for (++p; p != null; ++p)
                      {
                          StateNumber const next = *p;
                          for (uint8_t c = 0; c < maximumCharacter; ++c)
                          {
                              StateNumber const firstGoto =
                                  state[first]->getNextState(c);
                              StateNumber const nextGoto =
                                  state[next]->getNextState(c);
                              if (firstGoto != nextGoto &&
                                  (firstGoto == errorState ||
                                  nextGoto == errorState ||
                                  inGroup[firstGoto] != inGroup[nextGoto]))
                              {
                                  group[i] -= next;
                                  newGroup += next;
                                  inGroup[next] = numberOfGroups;
                                  break;
                              }
                          }
                      }
                      if (newGroup != 0)
                      {
                          assert(numberOfGroups < numberOfStates);
                          group[numberOfGroups] = newGroup;
                          numberOfGroups += 1;
                          done = false;
                      }
                  }
              }
          }
          rebuild(numberOfGroups, group, inGroup);
      }
    bool DFA::isColumnEquivalent(char c1, char c2) const
    {
          for (StateNumber s = 0; s < numberOfStates; ++s)
              if (state[s]->getNextState(c1) !=
                        state[s]->getNextState(c2))
                  return false;
          return true;
    }
    bool DFA::isRowEquivalent(StateNumber s1, StateNumber s2) const
    {
          for (uint8_t c = 0; c < maximumCharacter; ++c)
              if (state[s1]->getNextState(c) !=
                        state[s2]->getNextState(c))
                  return false;
          return true;
    }
}
