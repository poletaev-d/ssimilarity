# ssimilarity
Header-only С++ library implementing string similarity calculation functions.
* [Usage](#usage)
* [Supported algorithms](#supported-algorithms)
* [Examples](#examples)
## Usage
Add `ssimilarity/src` to compiler include directories. Then you can use it:
```cpp
#include <iostream>
#include "StringsSimilarityCalculator.hpp"

namespace ss = ssimilarity;

int main() {
    std::string a("specially");
    std::string b("especially");
    std::cout << ss::calculate(a, b, ss::CalculationMethod::LEVENSHTEIN) << std::endl; //0.9
    return 0;
}
```
## Supported algorithms
* Charwise - very straightforward method, that compares same-indexed characters
* Levenshtein distance - https://en.wikipedia.org/wiki/Levenshtein_distance
## Examples
```cpp
#include <iostream>
#include "StringsSimilarityCalculator.hpp"

int main() {
    namespace ss = ssimilarity;
    std::string a("Example");
    std::string b("exampl e");
    std::cout << ss::calculate(a, b, ss::CalculationMethod::CHARWISE) << std::endl; //0.667
    std::cout << ss::calculate(a, b, ss::CalculationMethod::LEVENSHTEIN) << std::endl; //0.75
    return 0;
}
```
Other specializations of std::basic_string (wstring, u16string, u32string) are also supported:
```cpp
ss::calculate(std::u32string(U"example"), std::u32string(U"example")); //1.0
ss::calculate(std::u16string(u"winning"), std::u16string(u"swimming")); //0.625
```
Please note, that C++ knows nothing about encodings, so if you use variable-width encoding (e.g. unicode with non-ASCII characters), results will be inaccurate. 
Using std::u32string is better approach in such cases, because it stores exactly one character under one index.