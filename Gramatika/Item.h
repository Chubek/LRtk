#if !defined(_Gramatik_Item_h)
#define _Gramatik_Item_h

#include <iostream>
#include "Gramatika/Gramatika.h"
#include "Gramatika/Symbol.h"

namespace Gramatika
{
    class Item
    {
         private: Production const* production;
         private: ProductionIndex dotPosition;
         private: Set lookAheadSet;
         public: Item();
         public: explicit Item(Production const&);
         public: Item(Item const&);
         public: Item& operator=(Item const&);
         public: Production const* getProduction() const;
         public: ProductionNumber getProductionNumber() const;
         public: Symbol* getLeftHandSide() const;
         public: Symbol* getRightHandSide(ProductionIndex) const;
         public: ProductionIndex getDotPosition() const;
         public: ProductionIndex getLength() const;
         public: Set const& getLookAheadSet() const;
         public: int compare(Item const&) const;
         public: bool operator==(Item const&) const;
         public: bool operator<=(Item const&) const;
         public: bool isMoreToRightOfDot() const;
         public: void advanceDot();
         public: void addLookAhead(Set const&);
         public: bool mergeLookAhead(Item const&);
         public: Symbol* getDotSymbol() const;
         public: SymbolNumber getDotSymbolNumber() const;
         public: Set getFirstSet(ProductionIndex) const;
         public: bool isNullable(ProductionIndex) const;
         public: ostream& put(ostream&) const;
    };
    inline Production const* Item::getProduction() const
         { return production; }
    inline ProductionNumber Item::getProductionNumber() const
         { return production->getNumber(); }
    inline Symbol* Item::getLeftHandSide() const
         { return production->getLeftHandSide(); }
    inline Symbol* Item::getRightHandSide(ProductionIndex i) const
         { return production->getRightHandSide(i); }
    inline ProductionIndex Item::getDotPosition() const
         { return dotPosition; }
    inline ProductionIndex Item::getLength() const
         { return production->getLength(); }
    inline Set const& Item::getLookAheadSet() const
         { return lookAheadSet; }
    inline bool Item::operator==(Item const& i) const
         { return compare(i) == 0; }
    inline bool Item::operator<=(Item const& i) const
         { return compare(i) <= 0; }
    inline bool Item::isMoreToRightOfDot() const
         { return dotPosition < getLength(); }
    inline ostream& operator<<(ostream& stream, Item const& item)
         { return item.put(stream); }
}

  #endif
