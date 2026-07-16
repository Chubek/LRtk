#include <iostream>
#include "Gramatika/Item.h"

namespace Gramatika
{
    Item::Item() :
         production(0),
         dotPosition(0),
         lookAheadSet()
         {}
    Item::Item(Production const& p) :
         production(&p),
         dotPosition(0),
         lookAheadSet()
         {}
    Item::Item(Item const& item) :
         production(item.production),
         dotPosition(item.dotPosition),
         lookAheadSet(item.lookAheadSet)
         {}
    Item& Item::operator=(Item const& item)
    {
         production = item.production;
         dotPosition = item.dotPosition;
         lookAheadSet = item.lookAheadSet;
         return *this;
    }
    int Item::compare(Item const& item) const
    {
        assert(production != 0);
        int result =
             getDotSymbolNumber() - item.getDotSymbolNumber();
        if (result != 0)
             return result;
        result = getProductionNumber() -
             item.getProductionNumber();
        if (result != 0)
             return result;
        return dotPosition - item.dotPosition;
    }
    void Item::advanceDot()
    {
         assert(production != 0);
         dotPosition += 1;
         assert(dotPosition <= getLength());
    }
    void Item::addLookAhead(Set const& set)
    {
         assert(production != 0);
         lookAheadSet |= set;
    }
    bool Item::mergeLookAhead(Item const& i)
    {
         assert(*this == i);
         if (i.lookAheadSet <= lookAheadSet)
              return false;
         lookAheadSet |= i.lookAheadSet;
         return true;
    }
    Symbol* Item::getDotSymbol() const
    {
         assert(production != 0);
         if (dotPosition < getLength())
              return getRightHandSide(dotPosition);
         else
              return 0;
    }
    SymbolNumber Item::getDotSymbolNumber() const
    {
         assert(production != 0);
         Symbol* const symbol = getDotSymbol();
         if (symbol != 0)
              return symbol->getNumber();
         else
              return 0;
    }
    Set Item::getFirstSet(ProductionIndex lookAhead) const
    {
        assert(production != 0);
        ProductionIndex const position =
             dotPosition + lookAhead;
        Set result;
        if (position >= getLength())
             result += epsilon;
        else
        {
             for (ProductionIndex i = position;
                 i < getLength(); ++i)
             {
                 Symbol* const symbol = getRightHandSide(i);
                 if (symbol->isTerminal())
                      result += symbol->getNumber();
                 else
                      result |= symbol->getFirstSet();
                 if (!symbol->isNullable())
                      break;
             }
        }
        return result;
    }
    bool Item::isNullable(ProductionIndex lookAhead) const
    {
         assert(production != 0);
         for (ProductionIndex i = dotPosition + lookAhead;
              i < getLength(); ++i)
              if (!getRightHandSide(i)->isNullable())
                  return false;
         return true;
    }
    ostream& Item::put(ostream& s) const
    {
        assert(production != 0);
        s << getLeftHandSide()->getName() << " ->";
        ProductionIndex i;
        for (i = 0; i < dotPosition; ++i)
             s << " " << getRightHandSide(i)->getName();
        s << " ^";
        for ( ; i < getLength(); ++i)
             s << " " << getRightHandSide(i)->getName();
        s << ". ";
        return s << lookAheadSet;
    }
}
