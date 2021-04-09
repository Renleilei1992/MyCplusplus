
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
	// bool值按照 true 和 false 输出.
    //std::cout << std::boolalpha;

    std::vector<string> phrase1{ "the", "tigers", "of", "wrath" };
    std::vector<string> phrase2{ "the", "horses", "of", "instruction" };
    auto less = std::lexicographical_compare(std::begin(phrase1), std::end(phrase1), std::begin(phrase2), std::end(phrase2));
    std::copy(std::begin(phrase1), std::end(phrase1), std::ostream_iterator<string>{std::cout, " "});
    std::cout << (less ? "are" : "are not") << " less than ";
    std::copy(std::begin(phrase2), std::end(phrase2), std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;

    std::array<int, 4> array1{ 1, 3, 19, 2 };
    std::array<int, 4> array2{ 1, 3, 20, 1 };
    auto bLess1 = std::lexicographical_compare(std::begin(array1), std::end(array1), std::begin(array2), std::end(array2));
    std::copy(std::begin(array1), std::end(array1), std::ostream_iterator<int>{std::cout, " "});
    std::cout << ((bLess1) ? " < " : " > ");
    std::copy(std::begin(array2), std::end(array2), std::ostream_iterator<int>{std::cout, " "});
    std::cout << std::endl;
}
