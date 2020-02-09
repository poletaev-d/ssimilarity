#pragma once
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <type_traits>
#include <cassert>
#include <functional>
#include "common.hpp"
#include "StringsSimilarityCalculator.hpp"


namespace ssimilarity {

  namespace detail_ {
    template<typename T1, typename T2>
    struct TemporaryMatch {
      TemporaryMatch(const T1* first, const T1* second, double similarity)
        : first(first), second(second), similarity(similarity) {};
    
      bool operator < (const TemporaryMatch<T1, T2>& other) const {
        return this->similarity < other.similarity;
      }

      const T1* first;
      const T2* second;
      double similarity;
    };

  }
/**
 * Calculate similarity of two vectors of strings,
 * depending on similarity of theirs same-indexed items
 * Resulting similarity is weighted average of items similarities, where weights depend on strings lengths
 * @param a Vector containing string values
 * @param b Vector containing string values
 * @param method Method of similarity calculation
 * @param useWeights Set to false if you want to return average of similarities instead of weighted average
 * @return Coefficient of similarity from 0.0 до 1.0
*/
template<class T>
double compareVectors(const std::vector<T>& a, const std::vector<T>& b, CalculationMethod method = CalculationMethod::CHARWISE, bool useWeights = true) {
  static_assert(detail_::is_basic_string<T>::value, "Vectors must be instantiated with std::basic_string specialization");
  if (a.size() != b.size()) {
    assert("Vectors should have the same size. Redundant elements will not take part in calculation");
  }
  if (a.size() == 0 || b.size() == 0) {
    return 0.0;
  }

  double weight = 0.0, sum = 0.0, weightsSum = 0.0;
  for (unsigned i = 0; i < std::min(a.size(), b.size()); ++i) {
    weight = useWeights ? 0.5 * (a[i].length() + b[i].length()) : 1.0;
    weightsSum += weight;
    sum += weight * ssimilarity::calculate(a[i], b[i], method);
  }

  return sum / weightsSum;
}


/**
 * Stores pair of objects and its similarity
 */
template<typename T1, typename T2> 
struct Match {
public:
  Match(detail_::TemporaryMatch<T1, T2>& t) 
    : first(*t.first), second(*t.second), similarity(t.similarity) {};
public:
  T1 first;
  T2 second;
  const double similarity;
};

/**
 * Find matches of objects in two vectors depending on objects similarity
 * @param first Vector containing T1 objects
 * @param second Vector containing T2 objects
 * @param sCalculate Function that returns similarity of T1 and T2 objects
 * @param threshold Minimum required similarity for pair. 
 *  High values can significantly improve performance. Choose this value depending on source data quality
 */ 
template<typename T1, typename T2>
std::vector<Match<T1, T2> > FindMatches(const std::vector<T1>& first, const std::vector<T2>& second
  , std::function<double(const T1&, const T2&)> sCalculate
  , double threshold = 0.7)
{
  typedef detail_::TemporaryMatch TemporaryMatch;

  std::vector<TemporaryMatch<T1, T2> > tmpPairs;
  int i = 0;
  for (const T1& d : first) {
    for (const T2& s : second) {
      TemporaryMatch<T1, T2> tmpPair(&d, &s, sCalculate(d, s));
      if (tmpPair.similarity >= threshold) {
        tmpPairs.push_back(tmpPair);
      }
    }
  }
  std::sort(tmpPairs.begin(), tmpPairs.end());


  std::set<const T1*> uDest;
  std::set<const T2*> uSrc;
  std::vector<Match<T1, T2>> similarPairs;
  auto it = tmpPairs.rbegin();
  while (it < tmpPairs.rend()) {
    TemporaryMatch<T1, T2>& tmpPair = *it;
    if (uDest.find(tmpPair.first) == uDest.end() && uSrc.find(tmpPair.second) == uSrc.end()) {
      similarPairs.emplace_back(tmpPair);
      uDest.insert(tmpPair.first);
      uSrc.insert(tmpPair.second);
    }
    it++;
  }
  return similarPairs;
}
}
