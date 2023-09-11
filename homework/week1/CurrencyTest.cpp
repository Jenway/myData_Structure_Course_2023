// test for currency class
#include "currency.h"
#include <iostream>
#include <sstream>
#include <string>

void assertEquals(int expected, int actual, std::string message)
{
    if (expected != actual) {
        std::cout << "ERROR: " << message << " (expected " << expected << ", actual " << actual << ")" << std::endl;
    }
}

// @test for input()

void CurrencyInputTest()
{

    // redirect input
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("+ 3.50");
    std::cin.rdbuf(input.rdbuf());

    currency c1(signType::plus, 9, 20);
    c1.input();
    if (c1.getSign() == signType::plus && c1.getDollars() == 3 && c1.getCents() == 50) {
        std::cout << "input() test passed" << std::endl;
    } else {
        std::cout << "input() test failed" << std::endl;
    }
    std::istringstream input2("- 3.50");
    std::cin.rdbuf(input2.rdbuf());

    currency c2(signType::minus, 2, 25);
    c2.input();
    if (c2.getSign() == signType::minus && c2.getDollars() == 3 && c2.getCents() == 50) {
        std::cout << "input() test passed" << std::endl;
    } else {
        std::cout << "input() test failed" << std::endl;
    }
}

int main(void)
{
    CurrencyInputTest();
    // @test for subtract()
    currency c3(signType::plus, 9, 20);
    currency c4(signType::plus, 3, 80);
    currency c5 = c3.subtract(c4);
    if (c5.getSign() == signType::plus && c5.getDollars() == 5 && c5.getCents() == 40) {
        std::cout << "subtract() test passed" << std::endl;
    } else {
        std::cout << "subtract() test failed" << std::endl;
        std::cout << "expect + 5.40" << std::endl;
        std::string str_sign = c5.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c5.getDollars()) + "." + std::to_string(c5.getCents());
        std::cout << "actual " << str << std::endl;
    }

    currency c3_1(signType::plus, 9, 20);
    currency c4_1(signType::minus, 30, 59);
    currency c5_1 = c3_1.subtract(c4_1);
    if (c5_1.getSign() == signType::plus && c5_1.getDollars() == 39 && c5_1.getCents() == 79) {
        std::cout << "subtract() test passed" << std::endl;
    } else {
        std::cout << "subtract() test failed" << std::endl;
        std::cout << "expect + 39.79" << std::endl;
        std::string str_sign = c5_1.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c5_1.getDollars()) + "." + std::to_string(c5_1.getCents());
        std::cout << "actual " << str << std::endl;
    }

    // @test for percent()
    currency c6(signType::plus, 9, 20);
    currency c7 = c6.percent(10.0);
    if (c7.getSign() == signType::plus && c7.getDollars() == 0 && c7.getCents() == 92) {
        std::cout << "percent() test passed" << std::endl;
    } else {
        std::cout << "percent() test failed" << std::endl;
        std::cout << "expect + 0.92" << std::endl;
        std::string str_sign = c7.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c7.getDollars()) + "." + std::to_string(c7.getCents());
        std::cout << "actual " << str << std::endl;
    }

    currency c6_1(signType::plus, 123456, 0);
    currency c7_1 = c6_1.percent(10);
    if (c7_1.getSign() == signType::plus && c7_1.getDollars() == 12345 && c7_1.getCents() == 60) {
        std::cout << "percent() test passed" << std::endl;
    } else {
        std::cout << "percent() test failed" << std::endl;
        std::cout << "expect + 12345.60" << std::endl;
        std::string str_sign = c7_1.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c7_1.getDollars()) + "." + std::to_string(c7_1.getCents());
        std::cout << "actual " << str << std::endl;
    }

    // @test for multiply()
    currency c8(signType::plus, 9, 20);
    currency c9 = c8.multiply(10.0);
    if (c9.getSign() == signType::plus && c9.getDollars() == 92 && c9.getCents() == 0) {
        std::cout << "multiply() test passed" << std::endl;
    } else {
        std::cout << "multiply() test failed" << std::endl;
        std::cout << "expect + 92.00" << std::endl;
        std::string str_sign = c9.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c9.getDollars()) + "." + std::to_string(c9.getCents());
        std::cout << "actual " << str << std::endl;
    }

    currency c8_1(signType::plus, 123456, 0);
    currency c9_1 = c8_1.multiply(10);
    if (c9_1.getSign() == signType::plus && c9_1.getDollars() == 1234560 && c9_1.getCents() == 0) {
        std::cout << "multiply() test passed" << std::endl;
    } else {
        std::cout << "multiply() test failed" << std::endl;
        std::cout << "expect + 1234560.00" << std::endl;
        std::string str_sign = c9_1.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c9_1.getDollars()) + "." + std::to_string(c9_1.getCents());
        std::cout << "actual " << str << std::endl;
    }

    // @test for divide()
    currency c10(signType::plus, 9, 20);
    currency c11 = c10.divide(10.0);
    if (c11.getSign() == signType::plus && c11.getDollars() == 0 && c11.getCents() == 92) {
        std::cout << "divide() test passed" << std::endl;
    } else {
        std::cout << "divide() test failed" << std::endl;
        std::cout << "expect + 0.92" << std::endl;
        std::string str_sign = c11.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c11.getDollars()) + "." + std::to_string(c11.getCents());
        std::cout << "actual " << str << std::endl;
    }

    currency c10_1(signType::plus, 123456, 0);
    currency c11_1 = c10_1.divide(10);
    if (c11_1.getSign() == signType::plus && c11_1.getDollars() == 12345 && c11_1.getCents() == 60) {
        std::cout << "divide() test passed" << std::endl;
    } else {
        std::cout << "divide() test failed" << std::endl;
        std::cout << "expect + 12345.60" << std::endl;
        std::string str_sign = c11_1.getSign() == signType::plus ? "+" : "-";
        std::string str = str_sign + std::to_string(c11_1.getDollars()) + "." + std::to_string(c11_1.getCents());
        std::cout << "actual " << str << std::endl;
    }
}