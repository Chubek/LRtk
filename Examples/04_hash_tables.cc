#include <iostream>
#include "Toolbox/HashTable.h"

int main()
{
    Toolbox::HashTable<std::string, int> table;
    table.add("answer", 42);
    std::cout << *table.find("answer") << '\n';
    return 0;
}
