#include "Loma/Fragment.h"
#include "Loma/Module.h"
#include "Loma/Group.h"
#include "Loma/File.h"
#include "Loma/Output.h"
#include <cassert>

namespace Loma
{
    Fragment::~Fragment() {}
    void Fragment::setModule(Module* _module)
    {
        assert(module == 0);
        module = _module;
    }
    void Fragment::crossReference(File&)
        {}
    TextFragment::~TextFragment()
        {}
    ostream& TextFragment::putCode(ostream& s, string const&, uint16_t) const
        { return s; }
    ostream& TextFragment::put(ostream& s) const
        { return s << text << endl; }
    CodeFragment::~CodeFragment()
        {}
    ostream& CodeFragment::putCode(
        ostream& s, string const& srcFile, uint16_t _indent) const
    {
        static int next = -1;
        if (line != next)
        {
            s << "#line " << line << " \"" << srcFile << "\"" << endl;
        }
        next = line + 1;
        s << textIndent(indent + _indent) << code << endl;
        return s;
    }
    ostream& CodeFragment::put(ostream& s) const
    {
        s << texIndent(indent) << texCode(code);
        if (label.size() > 0)
            s << "\\lomalabel{" << label << "}";
        if (symbol.size() > 0)
        {
            string const fullName = module->getScope() + symbol;
            string head;
            string tail;
            int16_t pos = fullName.rfind(':');
            if (pos < 0)
            {
                s << "\\lomasymbola{" << noBlanks(clearText(fullName)) << "}";
                s << "{" << texCode(fullName) << "}";
            }
            else
            {
                string head(fullName.substr(0, pos+1));
                string tail(fullName.substr(pos+1));
                s << "\\lomasymbolb{" << noBlanks(clearText(tail)) << "}";
                s << "{" << texCode(tail) << "}";
                s << "{" << noBlanks(clearText(head)) << "}";
                s << "{" << texCode(head) << "}";
            }
        }
        return s << "\\\\\n";
    }
    IncludeFragment::~IncludeFragment()
        {}
    void IncludeFragment::crossReference(File& f)
    {
        includeGroup = f.find(name);
        if (includeGroup == 0)
        {
             cerr << "Loma: \"" << name;
             cerr << "\" is not defined." << endl;
        }
        else
            includeGroup->setUsed(module);
    }
    ostream& IncludeFragment::putCode(
        ostream& s, string const& srcFile, uint16_t _indent) const
    {
        if (includeGroup != 0)
            includeGroup->putCode(s, srcFile, indent + _indent);
        return s;
    }
    ostream& IncludeFragment::put(ostream& s) const
    {
        if (includeGroup != 0)
            includeGroup->put(s, indent);
        return s;
    }
}
