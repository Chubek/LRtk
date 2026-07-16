#include <string>
#include <list>
#include "Loma/Module.h"
#include "Loma/File.h"
#include "Loma/Output.h"

namespace Loma
{
    uint16_t Module::numberOfModules = 0;
    Module::Module(string const& _name,
        FragmentList* _fragmentList, uint16_t _number) :
        number(_number),
        name(_name),
        fragmentList(_fragmentList)
    {
        assert(fragmentList != 0);
        for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                 lim(fragmentList->end()); p != lim; ++p)
        {
             (*p)->setModule(this);
        }
    }
    Module::~Module()
    {
         for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                  lim(fragmentList->end()); p != lim; ++p)
         {
              delete *p;
         }
         delete fragmentList;
    }
    void Module::registerIt(File&)
         {}
    void Module::checkused()
         {}
    void Module::setUsed(Module*)
         {}
    void Module::crossReference(File& f)
    {
         for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                  lim(fragmentList->end()); p != lim; ++p)
         {
              (*p)->crossReference(f);
         }
    }
    ostream& Module::put(ostream& s) const
    {
        uint16_t lineNumber = 0;
        for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                 lim(fragmentList->end()); p != lim; ++p)
        {
             s << "\\lomaline{" << ++lineNumber << "}" << **p;
        }
        return s;
    }
    ostream& Module::putCode(
        ostream& s, string const& srcFile, uint16_t indent) const
    {
        for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                 lim(fragmentList->end()); p != lim; ++p)
        {
             (*p)->putCode(s, srcFile, indent);
        }
        return s;
    }
    string Module::getScope() const
         { return ""; }
    TextModule::~TextModule()
        {}
    ostream& TextModule::put(ostream& s) const
    {
        for (list<Fragment*>::const_iterator p(fragmentList->begin()),
                  lim(fragmentList->end()); p != lim; ++p)
        {
             s << **p;
        }
        return s;
    }
    ostream& TextModule::putCode(ostream& s, string const&, uint16_t) const
        { return s; }
    FileModule::~FileModule()
        {}
    void FileModule::registerIt(File& _file)
        { _file.registerIt(this); }
    string FileModule::getScope() const
        { return scope; }
    ostream& FileModule::put(ostream& s) const
    {
        s << "\\begin{lomafile}{" << clearText(name) << "}";
        s << "{" << name << "}";
        s << "{" << number << "}\n";
        Module::put(s);
        return s << "\\end{lomafile}\n";
    }
    CodeModule::~CodeModule()
        {}
    void CodeModule::registerIt(File& _file)
        { _file.registerIt(this); }
    void CodeModule::checkused()
    {
        if (used == 0)
             cerr << "Loma: \"" << name << "\" is not used." << endl;
    }
    string CodeModule::getScope() const
    {
        if (used != 0)
             return used->getScope() + scope;
        else
             return scope;
    }

    ostream& CodeModule::put(ostream& s) const
    {
        s << "\\begin{lomacode}{" << clearText(name) << "}";
        s << "{" << name << "}";
        s << "{" << number << "}";
        if (used != 0)
             s << "{" << used->getNumber() << "}\n";
        else
             s << "{unused}\n";
        Module::put(s);
        return s << "\\end{lomacode}\n";
    }
    ExampleModule::~ExampleModule()
        {}
    ostream& ExampleModule::put(ostream& s) const
    {
        s << "\\begin{lomaexample}\n";
        Module::put(s);
        return s << "\\end{lomaexample}\n";
    }
}
