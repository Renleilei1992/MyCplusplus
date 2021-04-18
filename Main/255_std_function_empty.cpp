
// 本意是想测试 std::function 函数指针为空的以及判空的问题.
#include <iostream>     // std::coout
#include <functional>   // std::function, std::plus

using namespace std;

int main() {

    std::function<int(int, int)> foo;   // empty
    if (foo) {
        std::cout << "[1] foo is not empty!" << std::endl;
    } else {
        std::cout << "[1] foo is empty!" << std::endl;
    }

    // Now we can test a example
    foo = std::plus<int>();
    if (foo) {
        std::cout << "[2] foo is not empty!" << std::endl;
    } else {
        std::cout << "[2] foo is empty!" << std::endl;
    }

    std::cout << "[3] 9 + 12 = " << foo(9,12) << std::endl;

    // Example use with ternary operator (https://www.cprogramming.com/reference/operators/ternary-operator.html)
    std::cout << "[4] foo is " << (foo ? "callable" : "NOT callable") << std::endl;
    
    // make it empty
    foo = {};
    std::cout << "[5] foo is " << (foo ? "callable" : "NOT callable") << std::endl;
    
    foo = [](int a, int b) -> int { return a+b; };
    std::cout << "[6] foo is " << (foo ? "callable" : "NOT callable") << std::endl;
    return 0;
}