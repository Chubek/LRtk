#include <iostream>
#include "Gramatika/Automaton.h"
#include "Gramatika/SymbolTable.h"

int main()
{
    Gramatika::SymbolTable symbols;
    symbols.declareTerminal("number");
    symbols.declareNonterminal("start");
    symbols.declareStartSymbol("start");
    symbols.computeFirstSets();
    Gramatika::Automaton automaton(symbols);
    std::cout << automaton.getNumberOfStates() << '\n';
    return 0;
}
