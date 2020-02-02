#pragma once
#include "Charwise.hpp"
#include "Levenshtein.hpp"

namespace ssimilarity {


enum class CalculationMethod { CHARWISE, LEVENSHTEIN };

/**
* Calculate similarity of two strings using specified algorithm
* @param a First string
* @param b Second string
* @param method Algorithm of similarity calculation
* @return Coefficient of similarity from 0.0 до 1.0
*/
template<class T>
double calculate(const T& a, const T& b, CalculationMethod method = CalculationMethod::CHARWISE){
  if (method == CalculationMethod::CHARWISE) {
    return charwiseSimilarity(a, b);
  }
  else if (method == CalculationMethod::LEVENSHTEIN) {
    return levenshteinSimilarity(a, b);
  }
  return 0.0;
}

}



