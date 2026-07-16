#include <iostream>
#include "Gramatika/Partition.h"

namespace Gramatika
{
    Partition::Partition(ItemSet const& itemSet) :
        ItemSet(itemSet),
        numberOfElements(0),
        startOfElement(itemSet.item.size() + 1),
        sizeOfElement(itemSet.item.size() + 1),
        elementSymbol(itemSet.item.size() + 1)
    {
        uint8_t i = 0;
        elementSymbol[numberOfElements] = 0;
        startOfElement[numberOfElements] = i;
        for ( ; i < item.size(); ++i)
            if (item[i].getLength() > 0)
                break;
        sizeOfElement[numberOfElements] =
            i - startOfElement[numberOfElements];
        numberOfElements += 1;
        while (i < item.size())
        {
            startOfElement[numberOfElements] = i;
            Symbol* const symbol = item[i].getDotSymbol();
            elementSymbol[numberOfElements] = symbol;
            for ( ; i < item.size(); ++i)
                if (item[i].getDotSymbol() != symbol)
                     break;
            sizeOfElement[numberOfElements] =
                i - startOfElement[numberOfElements];
            numberOfElements += 1;
        }
    }
    Partition::~Partition()
        {}
    ostream& Partition::put(ostream& s) const
    {
        s << "Partition {\n";
        assert(numberOfElements > 0);
        uint8_t i = 0;
        for (;;)
        {
            uint8_t const start = startOfElement[i];
            uint8_t const size = sizeOfElement[i];
            for (uint8_t j = 0; j < size; ++j)
                s << item[start + j] << "\n";
            i += 1;
            if (i == numberOfElements)
                break;
            s << "--------\n";
        }
        return s << "}\n";
    }
    Partition::const_iterator Partition::begin() const
    {
        if (numberOfElements > 0)
             return const_iterator(this, 0);
        else
             return const_iterator();
    }
    Partition::const_iterator::const_iterator() :
        partition(0),
        referent(0)
        {}
    Partition::const_iterator::const_iterator(Partition const* p, uint8_t r) :
        partition(p),
        referent(r)
        {}
    Partition::const_iterator::const_iterator(
             Partition::const_iterator const& i) :
        partition(i.partition),
        referent(i.referent)
        {}
    ItemSet Partition::const_iterator::operator*() const
    {
        assert(partition != 0 && referent < partition->numberOfElements);
        ItemSet result;
        uint8_t const start =
            partition->startOfElement[referent];
        uint8_t const size =
            partition->sizeOfElement[referent];
        for (uint8_t i = 0; i < size; ++i)
            result.add(partition->item[start + i]);
        return result;
    }
    Symbol const* Partition::const_iterator::getSymbol() const
    {
        assert(partition != 0 && referent < partition->numberOfElements);
        return partition->elementSymbol[referent];
    }
    Partition::const_iterator& Partition::const_iterator::operator++()
    {
        assert(partition != 0);
        if (++referent == partition->numberOfElements)
        {
            partition = 0;
            referent = 0;
        }
        return *this;
    }
    bool Partition::const_iterator::operator!=(
             Partition::const_iterator const& i) const
    {
        return partition != i.partition || referent != i.referent;
    }
}
