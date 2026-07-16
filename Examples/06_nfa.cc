#include <iostream>
#include "Lexis/NFA.h"

int main()
{
    Lexis::NFA nfa("cat");
    nfa.setToken("word");
    std::cout << nfa.getNumberOfStates() << '\n';
    return 0;
}
