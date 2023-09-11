// Greatest Common Divisor

#include <iostream>

int gcd(int x, int y)
{
    return (y == 0) ? x : gcd(y, x % y);
}

int main(void)
{
    // @test for gcd()
    // expect: gcd(0,0) = 0
    if (gcd(0, 0) == 0) {
        std::cout << "gcd() test1 passed" << std::endl;
    } else {
        std::cout << "gcd() test1 failed" << std::endl;
        std::cout << "expect: gcd(0,0) = 0" << std::endl;
        std::cout << "actual: gcd(0,0) = " << gcd(0, 0) << std::endl;
    }
    // expect: gcd(0,1) = 1
    if (gcd(0, 1) == 1) {
        std::cout << "gcd() test2 passed" << std::endl;
    } else {
        std::cout << "gcd() test2 failed" << std::endl;
        std::cout << "expect: gcd(0,1) = 1" << std::endl;
        std::cout << "actual: gcd(0,1) = " << gcd(0, 1) << std::endl;
    }
    // expect: gcd(1,0) = 1
    if (gcd(1, 0) == 1) {
        std::cout << "gcd() test3 passed" << std::endl;
    } else {
        std::cout << "gcd() test3 failed" << std::endl;
        std::cout << "expect: gcd(1,0) = 1" << std::endl;
        std::cout << "actual: gcd(1,0) = " << gcd(1, 0) << std::endl;
    }
    // expect: gcd(81,36) = 9
    if (gcd(81, 36) == 9) {
        std::cout << "gcd() test4 passed" << std::endl;
    } else {
        std::cout << "gcd() test4 failed" << std::endl;
        std::cout << "expect: gcd(81,36) = 9" << std::endl;
        std::cout << "actual: gcd(81,36) = " << gcd(81, 36) << std::endl;
    }
    // expect: gcd(42,28) = 14
    if (gcd(42, 28) == 14) {
        std::cout << "gcd() test5 passed" << std::endl;
    } else {
        std::cout << "gcd() test5 failed" << std::endl;
        std::cout << "expect: gcd(42,28) = 14" << std::endl;
        std::cout << "actual: gcd(42,28) = " << gcd(42, 28) << std::endl;
    }
    return 0;
}