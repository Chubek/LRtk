#include <iostream>
#include <list>
#include "Gramatika/Automaton.h"
#include "Gramatika/Partition.h"

namespace Gramatika
{
    Automaton::Automaton(SymbolTable const& symTbl) :
        symbolTable(&symTbl),
        state(),
        hashTable(127),
        unfinishedStates()
    {
        createStates();
        addReductions();
    }
    Automaton::~Automaton()
    {
        for (StateNumber i = 0; i < state.size(); ++i)
             delete state[i];
    }
    State const& Automaton::operator[](StateNumber i) const
    {
        assert(i < state.size());
        return *state[i];
    }
    State* Automaton::newState(ItemSet const& kernel)
    {
        HashTable<ItemSet,State*>::const_iterator
            ptr(hashTable.find(kernel)), null;
        if (ptr != null)
            return *ptr;
        State* const result = new State(state.size(), kernel);
        state.push_back(result);
        hashTable.add(kernel, result);
        return result;
    }
    State* Automaton::getUnfinishedState()
    {
        if (unfinishedStates == 0)
            return 0;
        Set::const_iterator ptr(unfinishedStates.begin());
        StateNumber unfinished = *ptr;
        assert(unfinished < state.size());
        unfinishedStates -= unfinished;
        return state[unfinished];
    }
    void Automaton::addUnfinishedState(State const* state)
        { unfinishedStates += state->getNumber(); }
    void Automaton::createStartState()
    {
        assert(state.size() == 0);
        Symbol* const startSymbol = symbolTable->getStartSymbol();
        assert(startSymbol != 0);
        assert(startSymbol->getProductionList().size() == 1);
        list<Production*>::const_iterator ptr(
            startSymbol->getProductionList().begin());
        assert(ptr != startSymbol->getProductionList().end());
        Production const* const production = *ptr;
        assert(production != 0);
        Item startItem(*production);
        Set startLookAhead;
        startLookAhead += end_of_file;
        startItem.addLookAhead(startLookAhead);
        ItemSet startKernel;
        startKernel.add(startItem);
        State* const state = newState(startKernel);
        addUnfinishedState(state);
    }
    void Automaton::createStates()
    {
        createStartState();

          for (;;)
          {
              State* const currentState = getUnfinishedState();
              if (currentState == 0)
                  break;
              cerr << ".";
              ItemSet closureItems(
                  currentState->getKernelItems().getClosure());
              closureItems.addKernelItems(
                  currentState->getKernelItems());
              Partition partition(closureItems);
              Partition::const_iterator part(partition.begin()), null;
              assert(part != null);
              currentState->addEpsilonItems(*part);
              for (++part; part != null; ++part)
              {
                  State* nextState;
                  ItemSet kernel = *part;
                  kernel.advanceDots();
                  HashTable<ItemSet,State*>::const_iterator ptr(
                       hashTable.find(kernel)), null;
                  if (ptr != null)
                  {
                       nextState = *ptr;
                       bool const modified = nextState->mergeLookAhead(kernel);
                       if (modified)
                            addUnfinishedState(nextState);
                  }
                  else
                  {
                       nextState = newState(kernel);
                       addUnfinishedState(nextState);
                  }
                  if (!currentState->isClosed())
                  {
                       Symbol const* const symbol = part.getSymbol();
                       if (symbol->isTerminal())
                            currentState->addShift(symbol->getNumber(),
                                nextState->getNumber());
                       else
                            currentState->addGoto(symbol->getNumber(),
                                nextState->getNumber());
                  }
              }
              currentState->setClosed();
          }
      }
    void Automaton::addReductions()
    {
        for (StateNumber i = 0; i < state.size(); ++i)
             state[i]->addReductions();
    }
    ostream& Automaton::put(ostream& s) const
    {
        for (StateNumber i = 0; i < state.size(); ++i)
             s << *state[i];
        return s;
    }
}
