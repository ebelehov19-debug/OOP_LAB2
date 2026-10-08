#include "string.h"
#include <iostream>
#include <utility>

int main()
{
    String s1;
    String s2("Hello");
    String s3(s2);
    String s4(std::move(s3));

    s1 = s2;
    s1.append(", World!");
    s1.print(std::cout);
    std::cout << '\n' << s1.find("World") << '\n';

    String text("aa bb ccc");
    text.wrap(4).print(std::cout);
    std::cout << '\n';
}
