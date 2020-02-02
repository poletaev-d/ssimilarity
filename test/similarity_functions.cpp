#include <string>
#include "gtest/gtest.h"
#include "StringsSimilarityCalculator.hpp"

using namespace ssimilarity;
using namespace std;
testing::AssertionResult IsNear(double a, double b, double delta = 1.e-5) {
    if (abs(a-b) <= delta)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Floats are not near: " << a << " and " << b << ". Max. delta is " << delta;
}

TEST(SimilarityCalculation, Charwise) {
  EXPECT_TRUE(IsNear(1.0, charwiseSimilarity(string(""), string(""), -1)));
  EXPECT_TRUE(IsNear(0.0, charwiseSimilarity(string(""), string("a"), -1)));
  EXPECT_TRUE(IsNear(0.0, charwiseSimilarity(string(""), string("example"), -1)));
  EXPECT_TRUE(IsNear(0.0, charwiseSimilarity(string("example"), string(""), -1)));
  EXPECT_TRUE(IsNear(1.0, charwiseSimilarity(string("example"), string("example"), -1)));
  EXPECT_TRUE(IsNear(1.0, charwiseSimilarity(string("example"), string("example"), 0)));
  EXPECT_TRUE(IsNear(7.0 / 8.0, charwiseSimilarity(string("1example"), string("example2"), -1)));
  EXPECT_TRUE(IsNear(7.0 / 8.0, charwiseSimilarity(string("1example"), string("example2"), 9999999)));
  EXPECT_TRUE(IsNear(0.0, charwiseSimilarity(string("1example"), string("example2"), 0)));
  EXPECT_TRUE(IsNear(14.0 / 15.0, charwiseSimilarity(string("1example"), string("example"), -1)));
  EXPECT_TRUE(IsNear(4.0 / 26.0, charwiseSimilarity(string("4516y243exafdlkstmplefdoke"), string("9375niexample123ew6n.as1cz"), -1)));

  EXPECT_TRUE(IsNear(7.0 / 8.0, charwiseSimilarity(u32string(U"1example"), u32string(U"example2"), -1)));
  EXPECT_TRUE(IsNear(7.0 / 8.0, charwiseSimilarity(u16string(u"1example"), u16string(u"example2"), -1)));
  EXPECT_TRUE(IsNear(7.0 / 8.0, charwiseSimilarity(wstring(L"1example"), wstring(L"example2"), -1)));
}

TEST(SimilarityCalculation, LevenshteinDistance) {
    EXPECT_EQ(0, levenshteinDistance(string(""), string("")));
    EXPECT_EQ(1, levenshteinDistance(string(""), string("a")));
    EXPECT_EQ(7, levenshteinDistance(string(""), string("example")));
    EXPECT_EQ(7, levenshteinDistance(string("example"), string("")));
    EXPECT_EQ(0, levenshteinDistance(string("example"), string("example")));
    EXPECT_EQ(2, levenshteinDistance(string("1example"), string("example2")));
    EXPECT_EQ(1, levenshteinDistance(string("1example"), string("example")));
    EXPECT_EQ(24, levenshteinDistance(string("4516y243exafdlkstmplefdoke"), string("9375niexample123ew6n.as1cz")));

    EXPECT_EQ(2, levenshteinDistance(u32string(U"1example"), u32string(U"example2")));
    EXPECT_EQ(2, levenshteinDistance(u16string(u"1example"), u16string(u"example2")));
    EXPECT_EQ(2, levenshteinDistance(wstring(L"1example"), wstring(L"example2")));
}

TEST(SimilarityCalculation, Levenshtein) {
    EXPECT_TRUE(IsNear(1.0, levenshteinSimilarity(string(""), string(""))));
    EXPECT_TRUE(IsNear(0.0, levenshteinSimilarity(string("example"), string(""))));
    EXPECT_TRUE(IsNear(1.0, levenshteinSimilarity(string("example"), string("example"))));
    EXPECT_TRUE(IsNear(6.0 / 8.0, levenshteinSimilarity(string("1example"), string("example2"))));
    EXPECT_TRUE(IsNear(6.0 / 8.0, levenshteinSimilarity(u32string(U"1example"), u32string(U"example2"))));
    EXPECT_TRUE(IsNear(6.0 / 8.0, levenshteinSimilarity(u16string(u"1example"), u16string(u"example2"))));
    EXPECT_TRUE(IsNear(6.0 / 8.0, levenshteinSimilarity(wstring(L"1example"), wstring(L"example2"))));
}