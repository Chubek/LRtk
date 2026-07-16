#if !defined(_Toolbox_Stack_cc)
#define _Toolbox_Stack_cc

  #include <stdint.h>
  #include <cassert>
  #include "Toolbox/Stack.h"

namespace Toolbox
{
    template <typename T>
    Stack<T>::Stack() :
        data()
        {}
    template <typename T>
    void Stack<T>::push(T item)
        { data.push_back(item); }
    template <typename T>
    T Stack<T>::pop(uint16_t count)
    {
        assert(data.size() >= count);
        T result;
        for (uint16_t i = 0; i < count; ++i)
        {
            result = data.back();
            data.pop_back();
        }
        return result;
    }
    template <typename T>
    void Stack<T>::reset()
        { data.resize(0); }
    template <typename T>
    bool Stack<T>::isEmpty() const
        { return data.empty(); }
    template <typename T>
    T const& Stack<T>::operator[](uint16_t i) const
    {
        assert(i < data.size());
        return data[data.size() - (i + 1)];
    }
    template <typename T>
    ostream& Stack<T>::put(ostream& s) const
    {
        for (uint16_t i = data.size(); i > 0; --i)
            s << data[i - 1] << endl;
        return s;
    }
    template <typename T>
    T const& Stack<T>::getTop() const
    {
        assert(data.size() > 0);
        return data.back();
    }
    template <typename T>
    uint16_t Stack<T>::getSize() const
        { return data.size(); }
}

  #endif
