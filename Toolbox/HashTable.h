#if !defined(_Toolbox_HashTable_h)
#define _Toolbox_HashTable_h

#include <iostream>
#include <vector>
#include <list>
#include <stdint.h>

namespace Toolbox
{
    template <typename K, typename V>
    class HashTable
    {
        public: typedef K Key;
        public: typedef V Value;
        public: typedef pair<Key,Value> Pair;
        public: typedef list<Pair> List;
        public: typedef vector<List> Table;
        public: class const_iterator
        {
            private: HashTable<K,V> const* hashTable;
            private: uint16_t position;
            private: typename List::const_iterator ptr;
            public: const_iterator();
            public: const_iterator(
                HashTable<K,V> const*, uint16_t,
                typename List::const_iterator const&);
            public: const_iterator(const_iterator const&);
            public: V operator*() const;
            public: const_iterator& operator++();
            public: bool operator==(const_iterator const&) const;
            public: bool operator!=(const_iterator const&) const;
        };
        private: enum Constants
        {
            defaultSize = 127
        };
        private: Table table;
        public: explicit HashTable(uint16_t = defaultSize);
        public: ~HashTable();
        public: void add(K const&, V);
        public: void remove(K const&);
        public: void remove(K const&, V);
        public: ostream& put(ostream&) const;
        public: const_iterator find(K const&) const;
        public: const_iterator begin() const;
        friend class const_iterator;
    };
    template <typename K, typename V>
    inline ostream& operator<<(ostream& s, pair<K,V> const& pair)
        { return s << pair.first << ":" << pair.second; }
    template <typename K, typename V>
    inline ostream& operator<<(ostream& s, HashTable<K,V> const& table)
        { return table.put(s); }
    template <typename K, typename V>
    inline HashTable<K,V>::const_iterator::const_iterator() :
        hashTable(0),
        position(UINT16_MAX),
        ptr()
        {}
    template <typename K, typename V>
    inline HashTable<K,V>::const_iterator::const_iterator(
             HashTable<K,V> const* _hashTable,
             uint16_t _position,
             typename List::const_iterator const& _ptr) :
        hashTable(_hashTable),
        position(_position),
        ptr(_ptr)
        {}
    template <typename K, typename V>
    inline HashTable<K,V>::const_iterator::const_iterator(
             HashTable<K,V>::const_iterator const& i) :
        hashTable(i.hashTable),
        position(i.position),
        ptr(i.ptr)
        {}
    template <typename K, typename V>
    inline V HashTable<K,V>::const_iterator::operator*() const
        { return ptr->second; }
    template <typename K, typename V>
    inline bool HashTable<K,V>::const_iterator::operator!=(
             HashTable<K,V>::const_iterator const& i) const
        { return !(*this == i); }
}

  #include "Toolbox/HashTable.cc"

  #endif
