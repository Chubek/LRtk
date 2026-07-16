#include <iostream>
#include <string>
#include <ctype.h>
#include <cassert>
#include "Gramatika/Production.h"
#include "Gramatika/Symbol.h"
#include "Toolbox/fixwarn.h"

namespace Gramatika
{
    Production::Production() :
        number(0),
        leftHandSide(0),
        rightHandSide(0),
        action()
        {}
    Production::~Production()
        {}
    ProductionIndex Production::getPosition(
            string const& name, ProductionIndex instance) const
    {
        ProductionIndex count = 0;
        for (ProductionIndex i = 0; i < rightHandSide.size(); ++i)
        {
            if (rightHandSide[i]->getName() == name)
            {
                 count += 1;
                 if (count == instance)
                     return i;
            }
        }
        cerr << "Gramatika: $" << name << "#" << static_cast<uint16_t>(instance)
            << " not found.\n";
        return rightHandSide.size();
    }
    Symbol* Production::getRightHandSide(ProductionIndex i) const
    {
        assert(i < rightHandSide.size());
        return rightHandSide[i];
    }
    void Production::add(Symbol* symbol)
    {
        assert(symbol != 0);
        rightHandSide.push_back(symbol);
        symbol->setUsed();
    }
    Set Production::getFirstClosure() const
    {
        Set result;
        if (rightHandSide.size() == 0)
             result += epsilon;
        else
        {
             for (ProductionIndex i = 0; i < rightHandSide.size(); ++i)
             {
                 result |= rightHandSide[i]->getFirstSet();
                 if (!rightHandSide[i]->isNullable())
                     break;
            }
        }
        return result;
    }
    ostream& Production::put(ostream& s) const
    {
        assert(leftHandSide != 0);
        s << leftHandSide->getName() << " ->";
        for (ProductionIndex i = 0; i < rightHandSide.size(); ++i)
             s << " " << rightHandSide[i]->getName();
        s << ". (" << number << ")";
        return s;
    }
    ostream& Production::putAction(ostream& s) const
    {
        s << " case " << number << ":\n";
        s << "\t{\n";
        string::const_iterator ptr(action.begin()), lim(action.end());
        while (ptr != lim)
        {
            if (*ptr != '$')
            {
                 s << *ptr;
                 ++ptr;
            }
            else
            {
                 ++ptr;
                 if (ptr == lim)
                      s << '$';
                 else if (*ptr == '$')
                 {
                      s << "resultValue" << leftHandSide->getField();
                      ++ptr;
                 }
                 else
                 {
                      string name;
                      for ( ; ptr != lim; ++ptr)
                      {
                           if (!isalpha(*ptr)) break;
                           name += *ptr;
                      }
                      ProductionIndex instance = 0;
                      if (ptr != lim && *ptr == '#')
                      {
                           ++ptr;
                           for ( ; ptr != lim; ++ptr)
                           {
                               if (!isdigit(*ptr)) break;
                               instance = 10 * instance + *ptr - '0';
                           }
                      }
                      else
                           instance = 1;
                      ProductionIndex const i =
                           getPosition(name, instance);
                      s << "stack["
                           << static_cast<uint16_t>(rightHandSide.size()
                                   - (i + 1))
                           << "]";
                      s << rightHandSide[i]->getField();
                 }
            }
        }
        s << "\n";
        s << "\t}\n";
        s << "\tbreak;\n";
        return s;
    }
}
