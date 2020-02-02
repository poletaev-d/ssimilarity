#pragma once
#include <string>
#include <algorithm>

namespace ssimilarity {

  template<class T>
  double charwiseSimilarity(const T& a, const T& b, int offsetsLimit = 0) {
    if (a == b) {
      return 1.0;
    }
    //offset limit should not exceed string length
    if (offsetsLimit < 0 || offsetsLimit > static_cast<int>(std::max(a.length(), b.length()) - 1)) {
      offsetsLimit = static_cast<int>(std::max(a.length(), b.length())) - 1;
    }

    unsigned maxMatch = 0;
    for (int ofst = 0; ofst <= offsetsLimit; ofst = ofst < 0 ? -ofst : (-ofst - 1)) { //ofst = {0, -1, +1, -2, +2 ,-3 ... -offsetsLimit, +offsetsLimit}
      const T& staticString = ofst >= 0 ? b : a;
      const T& shiftedString = ofst >= 0 ? a : b;
      unsigned offset = static_cast<unsigned>(std::abs(ofst));
      unsigned intersectionLength = static_cast<unsigned>(std::min(staticString.length(), shiftedString.length() - offset));
      
      if (maxMatch == std::min(a.length(), b.length()) || intersectionLength < maxMatch) {
        break;
      }
      
      unsigned matchCounter = 0;

      for (unsigned i = 0; i < intersectionLength; ++i) {
        if (staticString[i] == shiftedString[i + offset]) {
          matchCounter++;
        }
      }
      maxMatch = std::max(maxMatch, matchCounter);
    }
    return static_cast<double>(maxMatch) / std::max(0.5 * static_cast<double>(a.length() + b.length()), 1.0);
  }

}



