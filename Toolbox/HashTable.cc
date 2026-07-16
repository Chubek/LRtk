#if !defined(_Toolbox_HashTable_cc)
#define _Toolbox_HashTable_cc

#include <iostream>
#include <stdint.h>
#include <cassert>
#include "Toolbox/HashTable.h"
#include "Toolbox/String.h"

  namespace Toolbox
  {
      using namespace String;

      template <typename K, typename V>
      HashTable<K,V>::HashTable(uint16_t size) :
          table(size)
          { assert(size > 0); }
      template <typename K, typename V>
      HashTable<K,V>::~HashTable()
          {}
      template <typename K, typename V>
      void HashTable<K,V>::add(K const& k, V i)
      {
          uint16_t const h = hash(k) % table.size();
          table[h].push_back(pair<K,V>(k, i));
      }
      template <typename K, typename V>
      void HashTable<K,V>::remove(K const& k)
      {
          uint16_t const h = hash(k) % table.size();

            for (typename List::iterator ptr(table[h].begin()),
                    lim(table[h].end()); ptr != lim; ++ptr)
            {
                if (ptr->first == k)
                {
                    table[h].erase(ptr);
                    break;
                }
            }
        }
      template <typename K, typename V>
      void HashTable<K,V>::remove(K const& k, V i)
      {
          uint16_t const h = hash(k) % table.size();

            for (typename List::iterator ptr(table[h].begin()),
                    lim(table[h].end()); ptr != lim; ++ptr)
            {
                if (ptr->first == k && ptr->second == i)
                {
                    table[h].erase(ptr);
                    break;
                }
            }
        }
      template <typename K, typename V>
      ostream& HashTable<K,V>::put(ostream& s) const
      {
          s << "HashTable {\n";
          for (uint16_t i = 0; i < table.size(); ++i)
          {
              for (typename List::const_iterator ptr(table[i].begin()),
                      lim(table[i].end()); ptr != lim; ++ptr)
              {
                  s << *ptr << endl;
              }
          }
          return s << "}\n";
      }
      template <typename K, typename V>
      typename HashTable<K,V>::const_iterator HashTable<K,V>::begin() const
      {
          for (uint16_t i = 0; i < table.size(); ++i)
          {
              for (typename List::const_iterator ptr(table[i].begin()),
                      lim(table[i].end()); ptr != lim; ++ptr)
              {
                  return const_iterator(this, i, ptr);
              }
          }
          return const_iterator();
      }
      template <typename K, typename V>
      typename HashTable<K,V>::const_iterator HashTable<K,V>::find(
              K const& k) const
      {
          uint16_t const h = hash(k) % table.size();

            for (typename List::const_iterator ptr(table[h].begin()),
                    lim(table[h].end()); ptr != lim; ++ptr)
            {
                if (ptr->first == k)
                {
                    return const_iterator(this, h, ptr);
                }
            }
            return const_iterator();
        }
      template <typename K, typename V>
      bool HashTable<K,V>::const_iterator::operator==(
               HashTable<K,V>::const_iterator const& i) const
      {
          bool result = false;
          if (hashTable == 0 || i.hashTable == 0)
          {
               return hashTable == i.hashTable;
          }
          else
          {
               if (position >= hashTable->table.size() ||
                   i.position >= hashTable->table.size())
               {
                   result = (position == i.position);
               }
               else
               {
                   result = (position == i.position && ptr == i.ptr);
               }
          }
          return result;
      }
      template <typename K, typename V>
      typename HashTable<K,V>::const_iterator&
      HashTable<K,V>::const_iterator::operator++()
      {
          if (position < hashTable->table.size())
          {
              if (ptr != hashTable->table[position].end())
              {
                   ++ptr;
                   if (ptr != hashTable->table[position].end())
                       return *this;
              }
              for (++position; position < hashTable->table.size(); ++position)
              {
                   ptr = hashTable->table[position].begin();
                   if (ptr != hashTable->table[position].end())
                       return *this;
              }
              hashTable = 0;
              position = UINT16_MAX;
              ptr = List::const_iterator();
          }
          return *this;
      }
  }

  #endif
