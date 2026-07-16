#if !defined(_Loma_File_h)
#define _Loma_File_h

#include <string>
#include "Loma/Group.h"
#include "Toolbox/HashTable.h"
#include "Toolbox/String.h"

  using namespace Toolbox;
  using namespace Toolbox::String;

namespace Loma
{
    class File
    {
         private: ModuleList* const moduleList;
         private: ModuleList fileList;
         private: HashTable<string,Group*> groupTable;
    public:
         public: File(ModuleList*);
         public: ~File();
         public: Group* find(string const&) const;
         public: void registerIt(FileModule*);
         public: void registerIt(CodeModule*);
         public: void crossReference();
         public: void putCode(string const&, string const&) const;
         public: ostream& put(ostream& s) const;
    };
    inline ostream& operator<<(ostream& s, File const& f)
         { return f.put(s); }
}

  #endif
