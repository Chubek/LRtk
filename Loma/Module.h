#if !defined(Loma_Module_h)
#define Loma_Module_h

#include <string>
#include <list>
#include "Loma/Fragment.h"

namespace Loma
{
    class Module;
    class File;

      typedef list<Module*> ModuleList;

      class Module
      {
           protected: uint16_t number;
           protected: string name;
           protected: FragmentList* const fragmentList;
           protected: static uint16_t numberOfModules;
           protected: Module(string const&, FragmentList*, uint16_t = 0);
           public: virtual ~Module();
           public: uint16_t getNumber() const;
           public: string const& getName() const;
           public: virtual void registerIt(File&);
           public: virtual void crossReference(File&);
           public: virtual void checkused();
           public: virtual void setUsed(Module*);
           public: virtual string getScope() const;
           public: virtual ostream& put(ostream&) const;
           public: virtual ostream& putCode(
               ostream&, string const&, uint16_t = 0) const;
      };
      inline uint16_t Module::getNumber() const
           { return number; }
      inline string const& Module::getName() const
           { return name; }
      inline ostream& operator<<(ostream& s, Module const& m)
           { return m.put(s); }

      class TextModule : public Module
      {
          public: TextModule(FragmentList*);
          public: ~TextModule();
          public: ostream& put(ostream&) const;
          public: ostream& putCode(ostream&, string const&, uint16_t = 0) const;
      };
      inline TextModule::TextModule(FragmentList* _fragmentList) :
          Module("", _fragmentList)
          {}

      class FileModule : public Module
      {
          private: string scope;
          public: FileModule(string const&, FragmentList*);
          public: FileModule(string const&, string const&, FragmentList*);
          public: ~FileModule();
          public: void registerIt(File&);
          public: string getScope() const;
          public: ostream& put(ostream&) const;
      };
      inline FileModule::FileModule(string const& _name,
          FragmentList* _fragmentList) :
          Module(_name, _fragmentList, ++numberOfModules),
          scope()
          {}
      inline FileModule::FileModule(string const& _name,
          string const& _scope,
          FragmentList* _fragmentList) :
          Module(_name, _fragmentList, ++numberOfModules),
          scope(_scope)
          {}

      class CodeModule : public Module
      {
          private: Module* used;
          private: string scope;
          public: CodeModule(string const&, FragmentList*);
          public: CodeModule(string const&, string const&, FragmentList*);
          public: ~CodeModule();
          public: void registerIt(File&);
          public: void checkused();
          public: void setUsed(Module*);
          public: string getScope() const;
          public: ostream& put(ostream&) const;
      };
      inline CodeModule::CodeModule(string const& _name,
          FragmentList* _fragmentList) :
          Module(_name, _fragmentList, ++numberOfModules),
          used(0),
          scope()
          {}
      inline CodeModule::CodeModule(string const& _name,
          string const& _scope,
          FragmentList* _fragmentList) :
          Module(_name, _fragmentList, ++numberOfModules),
          used(0),
          scope(_scope)
          {}
      inline void CodeModule::setUsed(Module* _used)
          { used = _used; }

      class ExampleModule : public Module
      {
          public: ExampleModule(FragmentList*);
          public: ~ExampleModule();
          public: ostream& put(ostream&) const;
      };
      inline ExampleModule::ExampleModule
          (FragmentList* _fragmentList) :
          Module("", _fragmentList)
          {}
  }

  #endif
