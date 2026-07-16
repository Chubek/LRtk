#include <iostream>
#include <string>
#include "Gramatika/Symbol.h"
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/List.h"

  using namespace Toolbox;

namespace Gramatika
{
    Symbol::Symbol(string const& nam, SymbolNumber num,
             SymbolType typ, string const& fld) :
        name(nam),
        number(num),
        type(typ),
        field(fld),
        used(false),
        defined(false),
        productionList(),
        firstSet()
    {
        if (type == terminal)
             defined = true;
    }
    Symbol& Symbol::setFirstSet(Set const& set)
    {
         firstSet = set;
         return *this;
    }
    Symbol& Symbol::append(list<Production*> const& list)
    {
         List::appendTo(productionList, list);
         return *this;
    }
    bool Symbol::isNullable() const
    {
         return type == nonterminal &&
              firstSet.contains(epsilon);
    }
    Set Symbol::getFirstClosure() const
    {
        Set result(firstSet);
        if (type == terminal)
             result += number;
        else
        {
             for (list<Production*>::const_iterator p(productionList.begin()),
                     lim(productionList.end()); p != lim; ++p)
             {
                 Production const* const prod = *p;
                 result |= prod->getFirstClosure();
             }
        }
        return result;
    }
    ostream& Symbol::put(ostream& s) const
    {
        s << "Symbol {" << name;
        s << ", " << number;
        s << ", " << type;
        s << ", " << field;
        s << ", used=" << used;
        s << ",\n defined=" << defined;
        s << ", firstSet=" << firstSet;
        s << "\n";
        for (list<Production*>::const_iterator p(productionList.begin()),
                 lim(productionList.end()); p != lim; ++p)
             s << " " << **p << "\n";
        s << "}\n";
        return s;
    }
    ostream& Symbol::putActions(ostream& s) const
    {
         for (list<Production*>::const_iterator p(productionList.begin()),
                  lim(productionList.end()); p != lim; ++p)
              (*p)->putAction(s);
         return s;
    }
}
