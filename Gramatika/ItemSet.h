#if !defined(_Gramatika_ItemSet_h)
#define _Gramatika_ItemSet_h

#include <iostream>
#include <vector>
#include "Gramatika/Gramatika.h"
#include "Gramatika/Symbol.h"
#include "Gramatika/Item.h"

namespace Gramatika
{
    class ItemSet
    {
        public: class const_iterator
        {
             private: ItemSet const* itemSet;
             private: uint8_t referent;
             private: const_iterator(ItemSet const*, uint8_t referent);
             public: const_iterator();
             public: const_iterator(const_iterator const&);
             public: Item const& operator*() const;
             public: const_iterator& operator++();
             public: bool operator!=(const_iterator const&) const;
             friend ItemSet;
        };
        protected: vector<Item> item;
        protected: bool close(Item);
        public: ItemSet();
        public: ~ItemSet();
        public: ItemSet(ItemSet const&);
        public: ItemSet& operator=(ItemSet const&);
        public: int compare(ItemSet const&) const;
        public: bool operator==(ItemSet const&) const;
        public: void add(Item const&);
        public: void add(ItemSet const&);
        public: void addKernelItems(ItemSet const&);
        public: void advanceDots();
        public: bool mergeLookAhead(ItemSet const&);
        public: Item* getItem(Production const*);
        public: ItemSet getClosure() const;
        public: uint16_t getHashValue() const;
        public: ostream& put(ostream&) const;
        public: const_iterator begin() const;
        friend class const_iterator;
        friend class Partition;
    };
    inline bool ItemSet::operator==(ItemSet const& itemSet) const
        { return compare(itemSet) == 0; }
    inline ostream& operator<<(ostream& stream, ItemSet const& itemSet)
        { return itemSet.put(stream); }
    inline uint16_t hash(ItemSet const& itemSet)
        { return itemSet.getHashValue(); }
}

  #endif
