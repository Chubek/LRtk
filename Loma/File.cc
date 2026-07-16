#include <iostream>
#include <fstream>
#include "Loma/File.h"
#include <cassert>

namespace Loma
{
    File::File(ModuleList* _moduleList) :
         moduleList(_moduleList)
         { assert (moduleList != 0); }
    File::~File()
    {
         for (list<Module*>::const_iterator p(moduleList->begin()),
                  lim(moduleList->end()); p != lim; ++p)
              delete *p;
         delete moduleList;
    }
    Group* File::find(string const& s) const
    {
         HashTable<string,Group*>::const_iterator p(groupTable.find(s)), null;
         if (p != null)
              return *p;
         else
              return 0;
    }
    void File::crossReference()
    {
        for (list<Module*>::const_iterator p(moduleList->begin()),
                 lim(moduleList->end()); p != lim; ++p)
        {
             (*p)->registerIt(*this);
        }
        for (list<Module*>::const_iterator p(moduleList->begin()),
                 lim(moduleList->end()); p != lim; ++p)
        {
             (*p)->crossReference(*this);
        }
        for (list<Module*>::const_iterator p(moduleList->begin()),
                 lim(moduleList->end()); p != lim; ++p)
        {
             (*p)->checkused();
        }
    }
    void File::registerIt(FileModule* m)
         { fileList.push_back(m); }
    void File::registerIt(CodeModule* m)
    {
        HashTable<string,Group*>::const_iterator
             p(groupTable.find(m->getName())), null;
        if (p != null)
             (*p)->append(m);
        else
        {
             Group* const group = new Group(m->getName());
             assert(group != 0);
             group->append(m);
             groupTable.add(m->getName(), group);
        }
    }
    void File::putCode(string const& directory, string const& srcFile) const
    {
        for (list<Module*>::const_iterator p(fileList.begin()),
                  lim(fileList.end()); p != lim; ++p)
        {
             string const fileName =
                 directory + (*p)->getName();
             cerr << " " << fileName;
             ofstream file(fileName.c_str());
             if (!file)
                 cerr << " Can’t open " << fileName << endl;
             else
                 (*p)->putCode(file, srcFile);
        }
    }
    ostream& File::put(ostream& s) const
    {
         for (list<Module*>::const_iterator p(moduleList->begin()),
                  lim(moduleList->end()); p != lim; ++p)
              s << **p;
         return s;
    }
}
