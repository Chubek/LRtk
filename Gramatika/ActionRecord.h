#if !defined(_Gramatika_ActionRecord_h)
#define _Gramatika_ActionRecord_h

#include <iostream>
#include <list>
#include "Gramatika/Gramatika.h"

namespace Gramatika
{
    class ActionRecord : public TableEntry
    {
        private: int compare(ActionRecord const&) const;
        public: ActionRecord(SymbolNumber, Action, uint16_t);
        public: SymbolNumber getSymbolNumber() const;
        public: Action getAction() const;
        public: uint16_t getNumber() const;
        public: bool operator==(ActionRecord const&) const;
        public: bool operator<=(ActionRecord const&) const;
        public: ostream& put(ostream&) const;
    };
    inline SymbolNumber ActionRecord::getSymbolNumber() const
        { return symbol; }
    inline Action ActionRecord::getAction() const
        { return static_cast<Action>(action); }
    inline uint16_t ActionRecord::getNumber() const
        { return number; }
    inline bool ActionRecord::operator==(ActionRecord const& arg) const
        { return compare(arg) == 0; }
    inline bool ActionRecord::operator<=(ActionRecord const& arg) const
        { return compare(arg) <= 0; }
    inline ostream& operator<<(ostream& stream, ActionRecord const& action)
        { return action.put(stream); }
}
#endif
