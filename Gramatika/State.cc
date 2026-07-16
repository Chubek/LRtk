#include <iostream>
#include "Gramatika/State.h"
#include "Toolbox/List.h"

  using namespace Toolbox;

namespace Gramatika
{
    State::State(StateNumber num, ItemSet const& kernel) :
        number(num),
        kernelItems(kernel),
        epsilonItems(),
        actions(),
        gotos(),
        closed(false),
        reduceReduceConflicts(0),
        shiftReduceConflicts(0)
        {}
    int State::compare(State const& s) const
         { return kernelItems.compare(s.kernelItems); }
    void State::addEpsilonItems(ItemSet const& itemSet)
         { epsilonItems.add(itemSet); }
    void State::addShift(SymbolNumber sym, StateNumber stat)
    {
         List::sortedInsert(actions,
                  ActionRecord(sym, shiftAction, stat));
    }
    void State::addGoto(SymbolNumber sym, StateNumber stat)
    {
         List::sortedInsert(gotos, GotoRecord(sym, stat));
    }
    void State::addReduction(SymbolNumber sym, ProductionNumber prod)
    {
         List::sortedInsert(actions,
                  ActionRecord(sym, reduceAction, prod));
    }
    bool State::mergeLookAhead(ItemSet const& itemSet)
         { return kernelItems.mergeLookAhead(itemSet); }
    ActionRecord const* State::getAction(SymbolNumber symbol) const
    {
         for (list<ActionRecord>::const_iterator ptr(actions.begin()),
                  lim(actions.end()); ptr != lim; ++ptr)
             if ((*ptr).getSymbolNumber() == symbol)
                  return &(*ptr);
         return 0;
    }
    void State::reduce(Item const& item)
    {
        if (item.getDotPosition() != item.getLength())
            return;
        for (Set::const_iterator ptr(item.getLookAheadSet().begin()), null;
                 ptr != null; ++ptr)
        {
            SymbolNumber symbol = *ptr;
            ActionRecord const* action = getAction(symbol);
            if (action != 0)
            {
                 if (action->getAction() == shiftAction)
                 {
                      shiftReduceConflicts += 1;
                      cerr << "Shift/reduce conflict." << endl;
                 }
                 else
                 {
                      assert(action->getAction() == reduceAction);
                      reduceReduceConflicts += 1;
                      cerr << "Reduce/reduce conflict." << endl;
                 }
            }
            addReduction(symbol, item.getProductionNumber());
        }
    }
    void State::addReductions()
    {
        for (ItemSet::const_iterator ptr(kernelItems.begin()), null;
                 ptr != null; ++ptr)
        {
            reduce(*ptr);
        }
        for (ItemSet::const_iterator ptr(epsilonItems.begin()), null;
                 ptr != null; ++ptr)
        {
            reduce(*ptr);
        }
    }
    ostream& State::put(ostream& s) const
    {
        s << "State { number = " << number
            << ", closed = " << closed << ",\n";
        s << "reduce/reduce conflicts = " <<
            static_cast<uint16_t>(reduceReduceConflicts)
            << ", shift/reduce conflicts = " <<
            static_cast<uint16_t>(shiftReduceConflicts) << "\n";
        s << "Kernel Items:\n";
        s << kernelItems;
        s << "Epsilon Items:\n";
        s << epsilonItems;
        s << "ActionList:\n";
        List::put(s, actions);
        s << "GotoList:\n";
        List::put(s, gotos);
        return s << "}\n";
    }
}
