#include <iostream>
#include "Toolbox/PathName.h"

int main()
{
    Toolbox::PathName path("src/main.cc");
    std::cout << path.getRoot() << path.getExtension() << '\n';
    return 0;
}
