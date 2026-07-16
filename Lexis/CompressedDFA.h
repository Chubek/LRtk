#if !defined(_Lexis_Compressed_h)
#define _Lexis_Compressed_h

#include <iostream>
#include <vector>
#include <string>
#include "Lexis/DFA.h"

namespace Lexis
{
    class CompressedDFA
    {
        private: TableEntry numberOfStates;
        private: TableEntry numberOfRows;
        private: TableEntry numberOfColumns;
        private: TableEntry numberOfTokens;
        private: vector<TableEntry> rowMap;
        private: vector<TableEntry> columnMap;
        private: vector<Anchor> anchorTable;
        private: vector<Action> actionTable;
        private: vector<TableEntry> transitionTable;
        private: vector<string> tokenTable;
        private: vector<string> tokenList;
        private: string language;
        private: ostream& putMap(ostream&, char const*, TableEntry,
            vector<TableEntry> const&) const;
        private: ostream& putTransitionTable(ostream&) const;
        private: ostream& putAnchorTable(ostream&) const;
        private: ostream& putActionTable(ostream&) const;
        private: ostream& putTokenList(ostream&) const;
        private: ostream& putTokenTable(ostream&) const;
        public: explicit CompressedDFA(DFA const&);
        public: ~CompressedDFA();
        public: ostream& putTokens(ostream&) const;
        public: ostream& putTables(ostream&) const;
    };
}

  #endif
