#include "pch.h"
#include "../Project1/similarityCheck.cpp"

class SimCheckFixture : public testing::Test
{
public:
    SimilarityCheck sc;
};

TEST_F(SimCheckFixture, Length_Except_No_String) {
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("A", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("", "A"));
}

TEST_F(SimCheckFixture, Length_Except_Lowercase) {
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("a", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("A", "b"));
}

TEST_F(SimCheckFixture, Length_Except_Number) {
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("1", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("A", "8"));
}

TEST_F(SimCheckFixture, Length_Special_Char) {
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("-", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, sc.LengthCheck("A", "@"));
}

TEST_F(SimCheckFixture, Length_Double_String) {
    EXPECT_EQ(0, sc.LengthCheck("ABC", "A"));
    EXPECT_EQ(0, sc.LengthCheck("ABC", "ABCDEFG"));
    EXPECT_EQ(0, sc.LengthCheck("A", "ABCDEF"));
}

TEST_F(SimCheckFixture, Length_Perfect_Cases) {
    EXPECT_EQ(MAX_LENGTH_SCORE, sc.LengthCheck("ABC", "CDE"));
    EXPECT_EQ(MAX_LENGTH_SCORE, sc.LengthCheck("ABC", "ABC"));
    EXPECT_EQ(MAX_LENGTH_SCORE, sc.LengthCheck("A", "X"));
}

TEST_F(SimCheckFixture, Length_Diff_Length) {
    EXPECT_EQ(40, sc.LengthCheck("ABCD", "CDE"));
    EXPECT_EQ(20, sc.LengthCheck("ABCDE", "ABC"));
    EXPECT_EQ(0, sc.LengthCheck("AB", "X"));
}