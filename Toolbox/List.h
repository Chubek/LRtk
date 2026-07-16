#if !defined(_Toolbox_List_h)
#define _Toolbox_List_h

  #include <iostream>
  #include <list>

namespace Toolbox
{
    namespace List
    {
          template <typename T>
          bool equals(list<T> const& left, list<T> const& right);
          template <typename T>
          void appendTo(list<T>& first, list<T> const& second);
          template <typename T>
          void sortedInsert(list<T>& lst, T i);
          template <typename T>
          ostream& put(ostream& s, list<T> const& l);
    }
}

  #include "Toolbox/List.cc"

  #endif
