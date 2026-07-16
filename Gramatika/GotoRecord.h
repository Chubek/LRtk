#if !defined(_Gramatika_GotoRecord_h)
#define _Gramatika_GotoRecord_h

#include <iostream>
#include <list>
#include "Gramatika/Gramatika.h"

namespace Gramatika
{
    class GotoRecord : public TableEntry
    {
        private: int compare(GotoRecord const&) const;
        public: GotoRecord(SymbolNumber, StateNumber);
        public: SymbolNumber getSymbolNumber() const;
        public: StateNumber getStateNumber() const;
        public: bool operator==(GotoRecord const&) const;
        public: bool operator<=(GotoRecord const&) const;
        public: ostream& put(ostream&) const;
    };
    inline SymbolNumber GotoRecord::getSymbolNumber() const
        { return symbol; }
    inline StateNumber GotoRecord::getStateNumber() const
        { return number; }
    inline bool GotoRecord::operator==(GotoRecord const& arg) const
        { return compare(arg) == 0; }
    inline bool GotoRecord::operator<=(GotoRecord const& arg) const
        { return compare(arg) <= 0; }
    inline ostream& operator<<(ostream& stream, GotoRecord const& g)
        { return g.put(stream); }
}

  #endif
