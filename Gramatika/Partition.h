#if !defined(_Gramatika_Partition_h)
#define _Gramatika_Partition_h

#include <iostream>
#include <vector>
#include "Gramatika/Gramatika.h"
#include "Gramatika/Symbol.h"
#include "Gramatika/Item.h"
#include "Gramatika/ItemSet.h"

namespace Gramatika
{
    class Partition : public ItemSet
    {
        public: class const_iterator
        {
            private: Partition const* partition;
            private: uint8_t referent;
            private: const_iterator(Partition const*, uint8_t);
            public: const_iterator();
            public: const_iterator(const_iterator const&);
            public: ItemSet operator*() const;
            public: Symbol const* getSymbol() const;
            public: const_iterator& operator++();
            public: bool operator!=(const_iterator const&) const;
            friend class Partition;
        };
        protected: uint8_t numberOfElements;
        protected: vector<uint8_t> startOfElement;
        protected: vector<uint8_t> sizeOfElement;
        protected: vector<Symbol const*> elementSymbol;
        public: explicit Partition(ItemSet const&);
        public: ~Partition();
        public: ostream& put(ostream&) const;
        public: const_iterator begin() const;
        friend class const_iterator;
    };
    inline ostream& operator<<(ostream& stream, Partition const& partition)
        { return partition.put(stream); }
}

  #endif
