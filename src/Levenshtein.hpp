#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace ssimilarity {

template<class T>
int levenshteinDistance(const T& a, const T& b) {
  if (a == b) {
    return 0;
  }
  std::vector<unsigned> prevIterarion(b.length() + 1);
  std::vector<unsigned> currentIteration(b.length() + 1);

  for (unsigned j = 0; j < prevIterarion.size(); ++j) {
    prevIterarion[j] = j;
  }

  for (unsigned i = 1; i < a.length() + 1; ++i) {
    currentIteration[0] = i;
    for (unsigned j = 1; j < b.length() + 1; ++j) {
      int costDelete = currentIteration[j - 1] + 1;
      int costAdd = prevIterarion[j] + 1;
      int costReplace = prevIterarion[j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1);
      currentIteration[j] = std::min({ costDelete, costAdd, costReplace });
    }
    std::swap(currentIteration, prevIterarion);
  }
  return prevIterarion.back();
}

template<class T>
double levenshteinSimilarity(const T& a, const T& b) {
  return 1.0 - static_cast<double>(levenshteinDistance(a, b)) / std::max(1.0, static_cast<double>(std::max(a.length(), b.length())));
}

}



