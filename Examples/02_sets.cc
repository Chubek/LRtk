#include <iostream>
#include "Toolbox/Set.h"

int main()
{
    Toolbox::Set set;
    set += 1;
    set += 3;
    std::cout << set << '\n';
    return 0;
}
