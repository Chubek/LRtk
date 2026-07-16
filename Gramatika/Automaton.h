#if !defined(_Gramatika_Automaton_h)
#define _Gramatika_Automaton_h

#include <iostream>
#include <vector>
#include "Gramatika/SymbolTable.h"
#include "Gramatika/State.h"
#include "Toolbox/HashTable.h"
#include "Toolbox/String.h"

  using namespace Toolbox;
  using namespace Toolbox::String;

namespace Gramatika
{
    class Automaton
    {
        private: SymbolTable const* const symbolTable;
        private: vector<State*> state;
        private: HashTable<ItemSet,State*> hashTable;
        private: Set unfinishedStates;
        private: State* getUnfinishedState();
        private: State* newState(ItemSet const&);
        private: void createStartState();
        private: void createStates();
        private: void addReductions();
        private: void addUnfinishedState(State const*);
        public: explicit Automaton(SymbolTable const&);
        public: ~Automaton();
        public: State const& operator[](StateNumber) const;
        public: SymbolTable const& getSymbolTable() const;
        public: StateNumber getNumberOfStates() const;
        public: ostream& put(ostream&) const;
    };
    inline SymbolTable const& Automaton::getSymbolTable() const
        { return *symbolTable; }
    inline StateNumber Automaton::getNumberOfStates() const
        { return state.size(); }
    inline ostream& operator<<(ostream& stream, Automaton const& tbl)
        { return tbl.put(stream); }
}

  #endif
