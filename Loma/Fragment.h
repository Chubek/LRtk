#if !defined(_Loma_Fragment_h)
#define _Loma_Fragment_h

#include <iostream>
#include <string>
#include <list>
#include <stdint.h>

namespace Loma
{
    class Fragment;
    class Module;
    class Group;
    class File;

      typedef list<Fragment*> FragmentList;

      class Fragment
      {
          protected: Module* module;
          protected: Fragment();
          public: virtual ~Fragment();
          public: void setModule(Module*);
          public: virtual void crossReference(File&);
          public: virtual ostream& putCode(
              ostream&, string const&, uint16_t = 0) const = 0;
          public: virtual ostream& put(ostream&) const = 0;
      };
      inline Fragment::Fragment() :
          module(0)
          {}
      inline ostream& operator<<(ostream& s, Fragment const& f)
          { return f.put(s); }

      class TextFragment : public Fragment
      {
          private: string const text;
          public: TextFragment(string const&);
          public: ~TextFragment();
          public: ostream& putCode(ostream&, string const&, uint16_t = 0) const;
          public: ostream& put(ostream&) const;
      };
      inline TextFragment::TextFragment(string const& _text) :
          text(_text)
          {}

      class CodeFragment : public Fragment
      {
          private: uint16_t const line;
          private: uint16_t const indent;
          private: string const code;
          private: string const label;
          private: string const symbol;
          public: CodeFragment(uint16_t, uint16_t, string const&,
              string const&, string const&);
          public: ~CodeFragment();
          public: ostream& putCode(ostream&, string const&, uint16_t = 0) const;
          public: ostream& put(ostream&) const;
      };
      inline CodeFragment::CodeFragment(
              uint16_t _line, uint16_t _indent, string const& _code,
              string const& _label, string const& _symbol) :
          line(_line),
          indent(_indent),
          code(_code),
          label(_label),
          symbol(_symbol)
          {}

      class IncludeFragment : public Fragment
      {
          private: uint16_t const indent;
          private: string const name;
          private: Group* includeGroup;
          public: IncludeFragment(uint16_t, string const&);
          public: ~IncludeFragment();
          public: void crossReference(File&);
          public: ostream& putCode(ostream&, string const&, uint16_t = 0) const;
          public: ostream& put(ostream&) const;
      };
      inline IncludeFragment::IncludeFragment
          (uint16_t _indent, string const& _name) :
          indent(_indent),
          name(_name),
          includeGroup(0)
          {}
  }

  #endif
