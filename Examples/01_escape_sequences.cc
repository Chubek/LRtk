#include <iostream>
#include "Toolbox/EscapeSequence.h"

int main()
{
    std::cout << Toolbox::EscapeSequence::encode("line\n") << '\n';
    return 0;
}
