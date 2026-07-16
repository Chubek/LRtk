#include <iostream>
#include "Lexis/DFA.h"
#include "Lexis/NFA.h"

int main()
{
    Lexis::NFA nfa("cat");
    Lexis::DFA dfa(nfa);
    std::cout << dfa.getNumberOfStates() << '\n';
    return 0;
}
