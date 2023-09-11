// write a recursive template function that checks if a value x is in an array a[0:n-1]

#include <iostream>
#include <string>

template <typename T>
bool in_array_helper(T x, T a[], int n, bool found = false)
{
    return (n == 0 || found) ? found : in_array_helper(x, a, n - 1, x == a[n - 1] || found);
}

template <typename T>
bool in_array(T x, T a[], int n)
{
    return in_array_helper(x, a, n, false);
}

int main(void)
{
    // @test for in_array()
    int a[] = { 1, 2, 3, 4, 5 };
    std::string str = in_array(3, a, 3) ? "true" : "false";
    if (str == "true") {
        std::cout << "in_array() test1 passed" << std::endl;
    } else {
        std::cout << "in_array() test1 failed" << std::endl;
        std::cout << "expect: true" << std::endl;
        std::cout << "actual: " << str << std::endl;
    }

    str = in_array(6, a, 3) ? "true" : "false";
    if (str == "false") {
        std::cout << "in_array() test2 passed" << std::endl;
    } else {
        std::cout << "in_array() test2 failed" << std::endl;
        std::cout << "expect: false" << std::endl;
        std::cout << "actual: " << str << std::endl;
    }

    str = in_array(3, a, 0) ? "true" : "false";
    if (str == "false") {
        std::cout << "in_array() test3 passed" << std::endl;
    } else {
        std::cout << "in_array() test3 failed" << std::endl;
        std::cout << "expect: false" << std::endl;
        std::cout << "actual: " << str << std::endl;
    }
}