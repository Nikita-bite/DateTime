#include <iostream>
#include "DateTime.h"

int main()
{
    time_t now = time(0);
    std::cout << now << "\n";
    DateTime time(now);
    std::cout << time.ToString() << "\n\n";
    DateTime Now;
    Now = Now.get_Now();
    std::cout << Now.get_Now().ToString() << "\n\n";

}
