#include <iostream>
#include <list>
#include "Gramatika/ItemSet.h"

namespace Gramatika
{
    ItemSet::ItemSet() :
        item(0)
        {}
    ItemSet::~ItemSet()
        {}
    ItemSet::ItemSet(ItemSet const& itemSet) :
        item(itemSet.item)
        {}
    ItemSet& ItemSet::operator=(ItemSet const& itemSet)
    {
        if (this != &itemSet)
        {
              item = itemSet.item;
        }
        return *this;
    }
    int ItemSet::compare(ItemSet const& itemSet) const
    {
        int result = static_cast<int>(item.size())
             - static_cast<int>(itemSet.item.size());
        if (result != 0)
             return result;
        for (uint8_t i = 0; i < item.size(); ++i)
        {
             result = item[i].compare(itemSet.item[i]);
             if (result != 0)
                 return result;
        }
        return 0;
    }
    void ItemSet::add(Item const& newItem)
    {
        uint8_t i;
        for (i = 0; i < item.size(); ++i)
        {
             if (item[i] == newItem)
             {
                 item[i].addLookAhead(newItem.getLookAheadSet());
                 return;
             }
        }
        item.resize(item.size() + 1U);
        for (i = item.size() - 1U; i > 0; i--)
        {
             if (item[i - 1] <= newItem)
                 break;
             item[i] = item[i - 1];
        }
        item[i] = newItem;
    }
    void ItemSet::add(ItemSet const& itemSet)
    {
        if (this != &itemSet)
        {
              for (uint8_t i = 0;
                      i < itemSet.item.size(); ++i)
                  add(itemSet.item[i]);
        }
    }
    void ItemSet::addKernelItems(ItemSet const& kernelSet)
    {
        if (this != &kernelSet)
        {
             for (uint8_t i = 0;
                     i < kernelSet.item.size(); ++i)
                 if (kernelSet.item[i].isMoreToRightOfDot())
                     add(kernelSet.item[i]);
        }
    }
    void ItemSet::advanceDots()
    {
        for (uint8_t i = 0; i < item.size(); ++i)
              item[i].advanceDot();
    }
    bool ItemSet::mergeLookAhead(ItemSet const& itemSet)
    {
        assert(item.size() == itemSet.item.size());
        bool modified = false;
        for (uint8_t i = 0; i < item.size(); ++i)
              modified |= item[i].mergeLookAhead(
                  itemSet.item[i]);
        return modified;
    }
    bool ItemSet::close(Item inputItem)
    {
        Symbol* const symbol = inputItem.getDotSymbol();

          if (symbol == 0 || symbol->isTerminal())
              return false;

          bool modified = false;
          list<Production*> const& prodList = symbol->getProductionList();
          for (list<Production*>::const_iterator p(prodList.begin()),
              lim(prodList.end()); p != lim; ++p)
          {
              Production const* const prod = *p;
              Item* closureItem = getItem(prod);
              if (closureItem == 0)
              {
                  add(Item(*prod));
                  modified = true;
                  closureItem = getItem(prod);
                  assert(closureItem != 0);
              }
              Set closureSet = inputItem.getFirstSet(1);
              closureSet -= epsilon;
              if (inputItem.isNullable(1))
                  closureSet |= inputItem.getLookAheadSet();
              if (!(closureSet <= closureItem->getLookAheadSet()))
              {
                  closureItem->addLookAhead(closureSet);
                  modified = true;
              }
          }
          return modified;
      }
    ItemSet ItemSet::getClosure() const
    {
        ItemSet result;

          bool modified = false;
          for (uint8_t i = 0; i < item.size(); ++i)
              modified |= result.close(item[i]);

          while (modified)
          {
              modified = false;
              for (uint8_t i = 0;
                      i < result.item.size(); ++i)
                  modified |= result.close(result.item[i]);
          }

          return result;
      }
    Item* ItemSet::getItem(Production const* p)
    {
        for (uint8_t i = 0; i < item.size(); ++i)
              if (item[i].getProduction() == p)
                  return &item[i];
        return 0;
    }
    uint16_t ItemSet::getHashValue() const
    {
        uint16_t result = 0;
        for (uint8_t i = 0; i < item.size(); ++i)
              result += item[i].getProductionNumber() +
                  item[i].getDotPosition();
        return result;
    }
    ostream& ItemSet::put(ostream& s) const
    {
        for (uint8_t i = 0; i < item.size(); ++i)
              s << item[i] << "\n";
        return s;
    }
    ItemSet::const_iterator ItemSet::begin() const
    {
        if (item.size() > 0)
              return const_iterator(this, 0);
        else
              return const_iterator();
    }
    ItemSet::const_iterator::const_iterator() :
         itemSet(0),
         referent(0)
         {}
    ItemSet::const_iterator::const_iterator(ItemSet const* i, uint8_t r) :
         itemSet(i),
         referent(r)
         {}
    ItemSet::const_iterator::const_iterator(ItemSet::const_iterator const& i) :
         itemSet(i.itemSet),
         referent(i.referent)
         {}
    Item const& ItemSet::const_iterator::operator*() const
    {
         assert(itemSet != 0 && referent < itemSet->item.size());
         return itemSet->item[referent];
    }
    ItemSet::const_iterator& ItemSet::const_iterator::operator++()
    {
        assert(itemSet != 0);
        if (++referent == itemSet->item.size())
        {
             itemSet = 0;
             referent = 0;
        }
        return *this;
    }
    bool ItemSet::const_iterator::operator!=(
              ItemSet::const_iterator const& i) const
         { return itemSet != i.itemSet || referent != i.referent; }
}
