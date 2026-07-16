#include <list>
#include <catch2/catch_test_macros.hpp>
#include "Gramatika/Automaton.h"
#include "Gramatika/Production.h"
#include "Gramatika/Symbol.h"
#include "Gramatika/SymbolTable.h"

TEST_CASE("symbol table starts with built in terminals")
{
    Gramatika::SymbolTable symbols;
    REQUIRE(symbols.getNumberOfSymbols() == 2);
    REQUIRE(symbols.getSymbol("_epsilon")->isTerminal());
    REQUIRE(symbols.getSymbol("end_of_file")->getNumber() == Gramatika::end_of_file);
}

TEST_CASE("symbol table declares grammar symbols")
{
    Gramatika::SymbolTable symbols;
    symbols.declareTerminal("number");
    symbols.declareNonterminal("expr", ".value");
    REQUIRE(symbols.getSymbol("number")->isTerminal());
    REQUIRE(symbols.getSymbol("expr")->isNonterminal());
    REQUIRE(symbols.getSymbol("expr")->getField() == "..value");
}

TEST_CASE("symbol table builds an automaton")
{
    Gramatika::SymbolTable symbols;
    symbols.declareTerminal("number");
    symbols.declareNonterminal("expr");
    symbols.declareStartSymbol("expr");
    symbols.computeFirstSets();
    Gramatika::Automaton automaton(symbols);
    REQUIRE(automaton.getNumberOfStates() >= 1);
    REQUIRE(automaton.getSymbolTable().getStartSymbol() != nullptr);
}
