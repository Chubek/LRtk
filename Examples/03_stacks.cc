#include <iostream>
#include "Toolbox/Stack.h"

int main()
{
    Toolbox::Stack<int> stack;
    stack.push(10);
    stack.push(20);
    std::cout << stack.getTop() << ' ' << stack.pop() << '\n';
    return 0;
}
