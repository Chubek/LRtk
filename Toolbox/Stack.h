#if !defined(_Toolbox_Stack_h)
#define _Toolbox_Stack_h

#include <iostream>
#include <vector>
#include <stdint.h>

namespace Toolbox
{
    template <typename T>
    class Stack
    {
         public: typedef T ElementType;
         private: vector<T> data;
         public: Stack();
         public: T pop(uint16_t = 1);
         public: void push(T);
         public: void reset();
         public: bool isEmpty() const;
         public: T const& operator[](uint16_t) const;
         public: T const& getTop() const;
         public: uint16_t getSize() const;
         public: ostream& put(ostream&) const;
    };
    template <typename T>
    inline ostream& operator<<(
              ostream& stream, Stack<T> const& stack)
          { return stack.put(stream); }
}

  #include "Toolbox/Stack.cc"

  #endif
