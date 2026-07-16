#if !defined(symbol_h)
#define symbol_h

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "Toolbox/Set.h"
#include "Gramatika/Production.h"

  using namespace Toolbox;

namespace Gramatika
{
    class Symbol
    {
         private: string name;
         private: SymbolNumber number;
         private: SymbolType type;
         private: string field;
         private: bool used;
         private: bool defined;
         private: list<Production*> productionList;
         private: Set firstSet;
         public: Symbol(string const&, SymbolNumber,
             SymbolType, string const&);
         public: Symbol& setDefined();
         public: Symbol& setUsed();
         public: Symbol& setFirstSet(Set const&);
         public: Symbol& append(list<Production*> const&);
         public: SymbolNumber getNumber() const;
         public: SymbolType getType() const;
         public: string const& getName() const;
         public: string const& getField() const;
         public: list<Production*> const& getProductionList() const;
         public: Set const& getFirstSet();
         public: bool isUsed() const;
         public: bool isDefined() const;
         public: bool isTerminal() const;
         public: bool isNonterminal() const;
         public: bool isNullable() const;
         public: Set getFirstClosure() const;
         public: ostream& put(ostream&) const;
         public: ostream& putActions(ostream&) const;
    };
    inline Symbol& Symbol::setDefined()
         { defined = true; return *this; }
    inline Symbol& Symbol::setUsed()
         { used = true; return *this; }
    inline SymbolNumber Symbol::getNumber() const
         { return number; }
    inline SymbolType Symbol::getType() const
         { return type; }
    inline string const& Symbol::getName() const
         { return name; }
    inline string const& Symbol::getField() const
         { return field; }
    inline list<Production*> const& Symbol::getProductionList() const
         { return productionList; }
    inline Set const& Symbol::getFirstSet()
         { return firstSet; }
    inline bool Symbol::isUsed() const
         { return used; }
    inline bool Symbol::isDefined() const
         { return defined; }
    inline bool Symbol::isTerminal() const
         { return type == terminal; }
    inline bool Symbol::isNonterminal() const
         { return type == nonterminal; }
    inline ostream& operator<<(ostream& stream, Symbol const& symbol)
         { return symbol.put(stream); }
}

  #endif
