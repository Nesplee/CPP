#include "iter.hpp"
#include <iostream>

void    print(int x) {
    std::cout<<x<<std::endl;
}

int main() {
    int arr[] = {1, 2, 3};
    iter(arr, 3, print);
    return (0);
}