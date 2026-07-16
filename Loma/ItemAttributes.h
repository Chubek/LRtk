#if !defined(_Loma_ItemAttributes_h)
#define _Loma_ItemAttributes_h

#include <string>
#include "Loma/File.h"
#include "Loma/Fragment.h"
#include "Loma/Module.h"

namespace Loma
{
    struct WordList
    {
        public: string text;
        public: string tag;
    };
    class ItemAttributes
    {
        public: string text;
        public: WordList wordList;
        public: union
        {
            Fragment* fragment;
            FragmentList* fragmentList;
            Module* module;
            ModuleList* moduleList;
            File* file;
        };
        public: ItemAttributes();
    };
    inline ItemAttributes::ItemAttributes() :
        text(),
        wordList(),
        fragment(0)
        {}
}

  #endif
