#if !defined(_Loma_Group_h)
#define _Loma_Group_h

  #include <string>
  #include "Loma/Module.h"

namespace Loma
{
    class Group
    {
         private: string name;
         private: ModuleList moduleList;
         private: ostream& putNumbers(ostream&) const;
         private: uint16_t getNumber() const;
         public: Group(string const&);
         public: string const& getName() const;
         public: void append(Module*);
         public: void setUsed(Module*);
         public: ostream& put(ostream&, uint16_t = 0) const;
         public: ostream& putCode(
              ostream&, string const& srcFile, uint16_t = 0) const;
    };
    inline Group::Group(string const& _name) :
         name(_name),
         moduleList()
         {}
    inline string const& Group::getName() const
         { return name; }
    inline uint16_t Group::getNumber() const
    {
         list<Module*>::const_iterator p(moduleList.begin());
         list<Module*>::const_iterator null(moduleList.end());
         assert(p != null);
         return (*p)->getNumber();
    }
    inline void Group::append(Module* _module)
         { moduleList.push_back(_module); }
    inline ostream& operator<<(ostream& s, Group const& g)
         { return g.put(s); }
}

  #endif
