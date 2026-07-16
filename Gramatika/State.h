#if !defined(_Gramatika_State_h)
#define _Gramatika_State_h

#include <iostream>
#include <list>
#include "Gramatika/Gramatika.h"
#include "Gramatika/ItemSet.h"
#include "Gramatika/ActionRecord.h"
#include "Gramatika/GotoRecord.h"
#include "Toolbox/List.h"

namespace Gramatika
{
    class State
    {
         private: StateNumber const number;
         private: ItemSet kernelItems;
         private: ItemSet epsilonItems;
         private: list<ActionRecord> actions;
         private: list<GotoRecord> gotos;
         private: bool closed;
         private: uint8_t reduceReduceConflicts;
         private: uint8_t shiftReduceConflicts;
         private: ActionRecord const* getAction(SymbolNumber) const;
         private: void reduce(Item const&);
         public: State(StateNumber, ItemSet const&);
         public: StateNumber getNumber() const;
         public: ItemSet const& getKernelItems() const;
         public: ItemSet const& getEpsilonItems() const;
         public: bool isClosed() const;
         public: int compare(State const&) const;
         public: bool operator==(State const&) const;
         public: void setClosed();
         public: void addEpsilonItems(ItemSet const&);
         public: void addShift(SymbolNumber, StateNumber);
         public: void addGoto(SymbolNumber, StateNumber);
         public: void addReduction(SymbolNumber, ProductionNumber);
         public: void addReductions();
         public: bool mergeLookAhead(ItemSet const&);
         public: list<ActionRecord> const& getActionList() const;
         public: list<GotoRecord> const& getGotoList() const;
         public: ostream& put(ostream&) const;
    };
    inline StateNumber State::getNumber() const
         { return number; }
    inline ItemSet const& State::getKernelItems() const
         { return kernelItems; }
    inline ItemSet const& State::getEpsilonItems() const
         { return epsilonItems; }
    inline bool State::isClosed() const
         { return closed; }
    inline bool State::operator==(State const& s) const
         { return compare(s) == 0; }
    inline void State::setClosed()
         { closed = true; }
    inline list<ActionRecord> const& State::getActionList() const
         { return actions; }
    inline list<GotoRecord> const& State::getGotoList() const
         { return gotos; }
    inline ostream& operator<<(ostream& stream, State const& state)
         { return state.put(stream); }
}

  #endif
