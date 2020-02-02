#pragma once
#include <utility>
#include <string>

namespace ssimilarity {
  namespace detail_ {
    template<class T>
    struct is_basic_string : std::false_type {};

    template<class Ch, class Tr, class Al>
    struct is_basic_string<std::basic_string<Ch, Tr, Al>> : std::true_type {};
  }
}



