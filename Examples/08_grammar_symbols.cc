#include <iostream>
#include "Gramatika/Symbol.h"

int main()
{
    Gramatika::Symbol symbol("identifier", 2, Gramatika::terminal, ".value");
    std::cout << symbol.getName() << '\n';
    return 0;
}
