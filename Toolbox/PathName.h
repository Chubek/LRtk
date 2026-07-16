#if !defined(_Toolbox_PathName_h)
#define _Toolbox_PathName_h

  #include <string>
  #include <stdint.h>

namespace Toolbox
{
    class PathName : public string
    {
        private: enum Constants
        {
            dot = '.',

               #if defined(unix)
                   separator = '/'
               #endif

               #if defined(__MSDOS__)
                   separator = '\\'
               #endif
          };
        public: PathName();
        public: PathName(string const&);
        public: PathName(char const*);
        public: PathName(char const*, uint16_t);
        public: string getHead() const;
        public: string getTail() const;
        public: string getBase() const;
        public: string getExtension() const;
        public: string getRoot() const;
    };
    inline PathName::PathName() :
        string()
        {}
    inline PathName::PathName(string const& _string) :
        string(_string)
        {}
    inline PathName::PathName(char const* _string) :
        string(_string)
        {}
    inline PathName::PathName(char const* _string, uint16_t _length) :
        string(_string, _length)
        {}
}

  #endif
