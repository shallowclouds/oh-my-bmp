#include <thread>

#include <iostream>

#include <vector>

 

 

void hello()
{

}

 

int main()

{

    std ::thread t1(hello);
    t1.join();
    return 0;
}