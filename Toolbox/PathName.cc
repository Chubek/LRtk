#include <iostream>
#include <assert.h>
#include "Toolbox/PathName.h"

namespace Toolbox
{
    string PathName::getHead() const
    {
        int16_t pos = rfind(separator);
        if (pos >= 0)
             return substr(0, pos + 1);
        else
             return "";
    }
    string PathName::getTail() const
    {
        int16_t pos = rfind(separator);
        if (pos >= 0)
             return substr(pos + 1);
        else
             return *this;
    }
    string PathName::getBase() const
        { return getHead() + getRoot(); }
    string PathName::getExtension() const
    {
        string const tail = getTail();
        int16_t pos = tail.rfind(dot);
        if (pos >= 0)
             return tail.substr(pos);
        else
             return "";
    }
    string PathName::getRoot() const
    {
        string const tail = getTail();
        int16_t pos = tail.rfind(dot);
        if (pos >= 0)
             return tail.substr(0, pos);
        else
             return tail;
    }
}
