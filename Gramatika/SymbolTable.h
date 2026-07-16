#if !defined(_Gramatika_SymbolTable_h)
#define _Gramatika_SymbolTable_h

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "Gramatika/Symbol.h"
#include "Toolbox/HashTable.h"
#include "Toolbox/String.h"

  using namespace Toolbox;
  using namespace Toolbox::String;

namespace Gramatika
{
    class SymbolTable
    {
        private: SymbolNumber numberOfTerminals;
        private: SymbolNumber numberOfNonterminals;
        private: HashTable<string,Symbol*> hashTable;
        private: vector<Symbol*> symbolTable;
        private: vector<Production*> productionTable;
        private: string preamble;
        private: string postamble;
        private: Symbol* startSymbol;
        private: string language;
        private: void declareSymbol(
            SymbolType, string const&, string const&, SymbolNumber = 0);
        public: SymbolTable();
        public: ~SymbolTable();
        public: void setPreamble(string const&);
        public: void setPostamble(string const&);
        public: void setLanguage(string const&);
        public: void declareStartSymbol(string const&);
        public: void declareTerminal(string const&, SymbolNumber = 0);
        public: void declareNonterminal(string const&);
        public: void declareNonterminal(string const&, string const&);
        public: void declareProductions(string const&, list<Production*> const&);
        public: void getTerminalSymbols(istream&);
        public: void computeFirstSets();
        public: Symbol* getSymbol(string const&) const;
        public: Symbol* getStartSymbol() const;
        public: Symbol const& operator[](SymbolNumber) const;
        public: SymbolNumber getNumberOfSymbols() const;
        public: ProductionNumber getNumberOfProductions() const;
        public: string const& getPreamble() const;
        public: string const& getPostamble() const;
        public: string const& getLanguage() const;
        public: ostream& put(ostream&) const;
        public: ostream& putActions(ostream&) const;
        public: ostream& putPreamble(ostream&) const;
    };
    inline void SymbolTable::setPreamble(string const& s)
        { preamble = s; }
    inline void SymbolTable::setPostamble(string const& s)
        { postamble = s; }
    inline void SymbolTable::setLanguage(string const& s)
        { language = s; }
    inline Symbol* SymbolTable::getStartSymbol() const
        { return startSymbol; }
    inline SymbolNumber SymbolTable::getNumberOfSymbols() const
        { return symbolTable.size(); }
    inline ProductionNumber SymbolTable::getNumberOfProductions() const
        { return productionTable.size(); }
    inline string const& SymbolTable::getPreamble() const
        { return preamble; }
    inline string const& SymbolTable::getPostamble() const
        { return postamble; }
    inline string const& SymbolTable::getLanguage() const
        { return language; }
    inline ostream& operator<<(ostream& stream, SymbolTable const& symtbl)
        { return symtbl.put(stream); }
}

  #endif
