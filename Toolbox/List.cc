#if !defined(_Toolbox_List_cc)
#define _Toolbox_List_cc

#include <iostream>
#include <list>
#include <cassert>
#include "Toolbox/List.h"

namespace Toolbox
{
    namespace List
    {
          template <typename T>
          bool equals(list<T> const& left, list<T> const& right)
          {
              typename list<T>::const_iterator lptr(left.begin());
              typename list<T>::const_iterator rptr(right.begin());
              while (lptr != left.end() && rptr != right.end())
              {
                   if (!(*lptr == *rptr))
                       return false;
                   ++lptr;
                   ++rptr;
              }
              return true;
          }
          template <typename T>
          void appendTo(list<T>& first, list<T> const& second)
          {
               assert(&first != &second);
               for (typename list<T>::const_iterator ptr(second.begin()),
                        lim(second.end()); ptr != lim; ++ptr)
                    first.push_back(*ptr);
          }
          template <typename T>
          void sortedInsert(list<T>& lst, T i)
          {
              typename list<T>::iterator ptr(lst.begin());
              typename list<T>::iterator lim(lst.end());
              while (ptr != lim)
              {
                   if (i <= *ptr)
                   {
                       break;
                   }
                   ++ptr;
              }
              if (ptr == lim)
                   lst.push_back(i);
              else
                   lst.insert(ptr, i);
          }
          template <typename T>
          ostream& put(ostream& s, list<T> const& l)
          {
              for (typename list<T>::const_iterator ptr(l.begin()),
                       lim(l.end()); ptr != lim; ++ptr)
              {
                   s << *ptr << endl;
              }
              return s;
          }
    }
}

  #endif
