#if !defined(_Gramatika_ParseTable_h)
#define _Gramatika_ParseTable_h

#include <iostream>
#include <vector>
#include <stdint.h>
#include "Gramatika/Gramatika.h"
#include "Gramatika/Automaton.h"

namespace Gramatika
{
    class ParseTable
    {
        public: enum Constants
        {
            invalid = UINT16_MAX >> 1
        };
        private: Automaton const* const automaton;
        private: SymbolTable const* const symbolTable;
        private: SymbolNumber const numberOfStates;
        private: ProductionNumber const numberOfProductions;
        private: vector<MapEntry> actionMap;
        private: vector<TableEntry> actionTable;
        private: uint16_t actionTableSize;
        private: Set actionStates;
        private: vector<MapEntry> gotoMap;
        private: vector<TableEntry> gotoTable;
        private: uint16_t gotoTableSize;
        private: Set gotoStates;
        private: vector<SymbolNumber> leftHandSideTable;
        private: vector<ProductionIndex> rightHandSideTable;
        private: void makeProductionTables();
        private: void makeActionMap();
        private: void makeActionTable();
        private: void makeGotoMap();
        private: void makeGotoTable();
        private: ostream& putMap(
            ostream&, char const*, vector<MapEntry> const&) const;
        private: ostream& putTable(ostream&, char const*, uint16_t,
            vector<TableEntry> const&) const;
        private: ostream& putLeftHandSideTable(ostream&) const;
        private: ostream& putRightHandSideTable(ostream&) const;
        public: explicit ParseTable(Automaton const&);
        public: ~ParseTable();
        public: ostream& put(ostream&) const;
    };
    inline ostream& operator<<(ostream& stream, ParseTable const& table)
        { return table.put(stream); }
}

  #endif
