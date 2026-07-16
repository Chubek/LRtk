#include <list>
#include "Loma/Group.h"
#include "Loma/Output.h"

namespace Loma
{
    void Group::setUsed(Module* _module)
    {
         for (list<Module*>::const_iterator p(moduleList.begin()),
                  lim(moduleList.end()); p != lim; ++p)
         {
             (*p)->setUsed(_module);
         }
    }
    ostream& Group::put(ostream& s, uint16_t indent) const
    {
        s << texIndent(indent);
        s << "\\lomainclude{" << clearText(name) << "}";
        s << "{" << name << "}";
        s << "{" << getNumber() << "}";
        s << "{";
        putNumbers(s);
        s << "}\\\\\n";
        return s;
    }
    ostream& Group::putCode(
        ostream& s, string const& srcFile, uint16_t indent) const
    {
        for (list<Module*>::const_iterator p(moduleList.begin()),
                 lim(moduleList.end()); p != lim; ++p)
        {
            (*p)->putCode(s, srcFile, indent);
        }
        return s;
    }
    ostream& Group::putNumbers(ostream& s) const
    {
        bool comma = false;
        list<Module*>::const_iterator p(moduleList.begin());
        list<Module*>::const_iterator lim(moduleList.end());
        assert(p != lim);
        uint16_t first = (*p)->getNumber();
        uint16_t previous = first;
        for (++p; p != lim; ++p)
        {
             uint16_t const current = (*p)->getNumber();
             if (current != previous + 1)
             {
                 if (comma)
                      s << ",";
                 comma = true;
                 if (first == previous)
                      s << first;
                 else if (first + 1 == previous)
                      s << first << "," << previous;
                 else
                      s << first << "--" << previous;
                 first = current;
             }
             previous = current;
        }
        if (comma)
             s << ",";
        if (first == previous)
             s << first;
        else if (first + 1 == previous)
             s << first << "," << previous;
        else
             s << first << "--" << previous;
        return s;
    }
}
