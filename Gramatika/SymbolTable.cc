#include <iostream>
#include <string>
#include "Gramatika/Gramatika.h"
#include "Gramatika/SymbolTable.h"
#include "Toolbox/EscapeSequence.h"
#include <cassert>

namespace Gramatika
{
    SymbolTable::SymbolTable() :
        numberOfTerminals(0),
        numberOfNonterminals(0),
        hashTable(127),
        symbolTable(),
        productionTable(),
        preamble(),
        postamble(),
        startSymbol(0)
    {
        declareTerminal("_epsilon", epsilon);
        declareTerminal("end_of_file", end_of_file);
    }
    SymbolTable::~SymbolTable()
    {
        for (SymbolNumber s = 0; s < symbolTable.size(); ++s)
            delete symbolTable[s];
        for (ProductionNumber p = 0;
            p < productionTable.size(); ++p)
            delete productionTable[p];
    }
    Symbol const& SymbolTable::operator[](SymbolNumber i) const
    {
        assert(i < symbolTable.size());
        return *symbolTable[i];
    }
    void SymbolTable::declareStartSymbol(string const& name)
    {
        HashTable<string,Symbol*>::const_iterator ptr(hashTable.find(name)), null;
        if (ptr != null)
        {
             Production* const production = new Production();
             production->add(*ptr);
             list<Production*>* const productionList =
                 new list<Production*>();
             productionList->push_back(production);
             declareNonterminal("_start", "default");
             ptr = hashTable.find("_start");
             assert(ptr != null);
             startSymbol = *ptr;
             declareProductions("_start", *productionList);
             delete productionList;
        }
        else
             cerr << "Error: " << name << " not declared.\n";
    }
    void SymbolTable::declareSymbol(
             SymbolType type, string const& name,
             string const& field, SymbolNumber number)
    {
        HashTable<string,Symbol*>::const_iterator
             ptr(hashTable.find(name)), null;
        if (ptr != null)
             cerr << "Error: " << name << " multiply defined.\n";
        else
        {
            if (number != 0)
                 assert(number == symbolTable.size());
            Symbol* symbol =
                 new Symbol(name, symbolTable.size(), type, field);
            symbolTable.push_back(symbol);
            hashTable.add(name, symbol);
        }
    }
    void SymbolTable::declareTerminal(string const& name, SymbolNumber number)
    {
        declareSymbol(terminal, name, ".terminal", number);
        numberOfTerminals += 1;
    }
    void SymbolTable::declareNonterminal(string const& name)
        { declareNonterminal(name, "_default"); }
    void SymbolTable::declareNonterminal(string const& name, string const& fld)
    {
        string attributesField(".");
        attributesField += fld;
        declareSymbol(
            nonterminal, name, attributesField);
        numberOfNonterminals += 1;
    }
    void SymbolTable::declareProductions(
             string const& name, list<Production*> const& productionList)
    {
        HashTable<string,Symbol*>::const_iterator
             ptr(hashTable.find(name)), null;
        if (ptr == null)
             cerr << "Error: " << name << " not declared.\n";
        else
        {
            Symbol* const symbol = *ptr;
            assert(symbol != 0);
            assert(productionTable.size() != 0 ||
                 symbol == startSymbol);
            for (list<Production*>::const_iterator p(productionList.begin()),
                     lim(productionList.end()); p != lim; ++p)
            {
                 Production* const production = *p;
                 production->setNumber(productionTable.size());
                 production->setLeftHandSide(symbol);
                 productionTable.push_back(production);
            }
            symbol->append(productionList);
            symbol->setDefined();
        }
    }
    void SymbolTable::getTerminalSymbols(istream& s)
    {
        uint8_t count = 0;
        for (;;)
        {
            string word;

               s >> word;
               if (word == string("{"))
               {
                   if (++count == 3)
                       break;
               }
          }
          for (;;)
          {
              string name;
              string word;
              SymbolNumber number;

               s >> name >> word >> number;
               if (name != string("_epsilon") && name != string("end_of_file"))
                   declareTerminal(name, number);
               s >> word;
               if (word == string("};"))
                   break;
          }
      }
    Symbol* SymbolTable::getSymbol(string const& name) const
    {
        HashTable<string,Symbol*>::const_iterator
            ptr(hashTable.find(name)), null;
        assert(ptr != null);
        return *ptr;
    }
    void SymbolTable::computeFirstSets()
    {
        bool modified = false;
        do
        {
            modified = false;
            for (SymbolNumber i = 0;
                 i < symbolTable.size(); ++i)
            {
                 Set newValue;
                 newValue = symbolTable[i]->getFirstClosure();
                 if (symbolTable[i]->getFirstSet() != newValue)
                 {
                     symbolTable[i]->setFirstSet(newValue);
                     modified = true;
                 }
            }
        }
        while (modified);
    }
    ostream& SymbolTable::put(ostream& s) const
    {
        s << "preamble = \"" << EscapeSequence::encode(preamble, '"')
            << "\"\n";
        s << "postamble = \"" << EscapeSequence::encode(postamble, '"')
            << "\"\n";
        s << "startSymbol = " << startSymbol->getName() << "\n";
        for (SymbolNumber i = 0; i < symbolTable.size(); ++i)
            s << *symbolTable[i];
        return s;
    }
    ostream& SymbolTable::putActions(ostream& s) const
    {
        s <<
             "#if !defined(gramactn_c)\n"
             "#define gramactn_c\n"
             "\n"
             "#include \"gramadef.h\"\n"
             "\n"
             "namespace " << language << "\n"
             "{\n"
             "template <typename B, typename T, typename A, typename GT>\n"
             "bool Parser<B,T,A,GT>::performAction"
                 "(ProductionNumber production)\n"
             "{\n"
             " switch (production)\n"
             " {\n";
        for (ProductionNumber i = 0; i < productionTable.size(); ++i)
             productionTable[i]->putAction(s);
        s <<
             " default: break;\n"
             " }\n"
             " return true;\n"
             "}\n"
             "\n"
             "}\n";
        s << postamble << "\n";
        s << "#endif\n";
        return s;
    }
    ostream& SymbolTable::putPreamble(ostream& s) const
    {
        s <<
             "#if !defined(gramadef_h)\n"
             "#define gramadef_h\n"
             "\n"
             "#include \"Gramatika/Gramatika.h\"\n"
             "\n";
        s << preamble << "\n";
        s <<
             "namespace " << language << "\n"
             "{\n"
             " using namespace Gramatika;\n"
             " class GramatikaTables\n"
             " {\n"
             " public:\n"
             "\tstatic StateNumber const numberOfStates;\n"
             "\tstatic MapEntry const actionMap[];\n"
             "\tstatic TableEntry const actionTable[];\n"
             "\tstatic MapEntry const gotoMap[];\n"
             "\tstatic TableEntry const gotoTable[];\n"
             "\tstatic ProductionNumber const numberOfProductions;\n"
             "\tstatic SymbolNumber const leftHandSideTable[];\n"
             "\tstatic ProductionIndex const rightHandSideTable[];\n"
             " };\n\n"
             " template <typename B, typename T, typename A, typename GT>\n"
             " class Parser : public B, public Gramatika::Parser<T,A,GT>\n"
             " {\n"
             " protected:\n"
             "\tbool performAction(ProductionNumber);\n"
             " };\n"
             "\n"
             "}\n"
             "\n"
             "#include \"gramactn.cc\"\n"
             "\n"
             "#endif\n";
        return s;
    }
}
