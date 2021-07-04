#include <iostream>

#include "dir/util.h"
#include "dir/stuff.h"

int main()
{
    std::cout << "Hello World " << std::endl;
    std::cout << "Hello World " << util::GetAnswer() << std::endl;
    std::cout << "Hello World 2 " << util::GetOtherAnswer() << std::endl;
}
