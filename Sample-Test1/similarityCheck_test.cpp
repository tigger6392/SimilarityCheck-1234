#include "pch.h"
#include "../Project1/similarityCheck.cpp"

class SimCheckFixture : public testing::Test
{
public:

    int GetLengthScore(const string& input1, const string& input2)
    {
        return sc.LengthCheck(input1, input2);
    }
    int GetAlphaScore(const string& input1, const string& input2)
    {
        return sc.AlphaCheck(input1, input2);
    }
    int GetTotalScore(const string& input1, const string& input2)
    {
        return GetLengthScore(input1, input2) + GetAlphaScore(input1, input2);
    }
    SimilarityCheck sc;
};

/* Length */
TEST_F(SimCheckFixture, Length_Except_No_String) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("A", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("", "A"));
}

TEST_F(SimCheckFixture, Length_Except_Lowercase) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("a", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("A", "b"));
}

TEST_F(SimCheckFixture, Length_Except_Number) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("1", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("A", "8"));
}

TEST_F(SimCheckFixture, Length_Special_Char) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("-", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetLengthScore("A", "@"));
}

TEST_F(SimCheckFixture, Length_Double_String) {
    EXPECT_EQ(0, GetLengthScore("ABC", "A"));
    EXPECT_EQ(0, GetLengthScore("ABC", "ABCDEFG"));
    EXPECT_EQ(0, GetLengthScore("A", "ABCDEF"));
}

TEST_F(SimCheckFixture, Length_Perfect_Cases) {
    EXPECT_EQ(MAX_LENGTH_SCORE, GetLengthScore("ABC", "CDE"));
    EXPECT_EQ(MAX_LENGTH_SCORE, GetLengthScore("ABC", "ABC"));
    EXPECT_EQ(MAX_LENGTH_SCORE, GetLengthScore("A", "X"));
}

TEST_F(SimCheckFixture, Length_Diff_Length) {
    EXPECT_EQ(40, GetLengthScore("ABCD", "CDE"));
    EXPECT_EQ(20, GetLengthScore("ABCDE", "ABC"));
    EXPECT_EQ(0, GetLengthScore("AB", "X"));
}

/* Alpha */
TEST_F(SimCheckFixture, Alpha_Except_No_String) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("A", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("", "A"));
}

TEST_F(SimCheckFixture, Alpha_Except_Lowercase) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("a", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("A", "b"));
}

TEST_F(SimCheckFixture, Alpha_Except_Number) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("1", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("A", "8"));
}

TEST_F(SimCheckFixture, Alpha_Special_Char) {
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("-", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES, GetAlphaScore("A", "@"));
}

TEST_F(SimCheckFixture, Alpha_All_Different) {
    EXPECT_EQ(0, GetAlphaScore("AB", "CDE"));
    EXPECT_EQ(0, GetAlphaScore("ACB", "QWER"));
    EXPECT_EQ(0, GetAlphaScore("B", "AC"));
}

TEST_F(SimCheckFixture, Alpha_Normal_Cases) {
    EXPECT_EQ(40, GetAlphaScore("ABCD", "CDAB"));
    EXPECT_EQ(5, GetAlphaScore("ACB", "QWERA"));
    EXPECT_EQ(20, GetAlphaScore("ACB", "DAB"));
}

/* Integrated (Length + Alpha) */
TEST_F(SimCheckFixture, Integrated_Normal_Cases) {
    EXPECT_EQ(100, GetTotalScore("ASD", "DSA"));
    EXPECT_EQ(0, GetTotalScore("A", "BB"));
    EXPECT_EQ(60, GetTotalScore("AAABB", "BAA")); //20 + 40
    EXPECT_EQ(70, GetTotalScore("AA", "AAA")); //30 + 40
    EXPECT_EQ(50, GetTotalScore("AA", "AAE")); //30 + 20
}

TEST_F(SimCheckFixture, Integrated_Exceptional_Cases) {
    EXPECT_EQ(EXCEPTIONAL_CASES + EXCEPTIONAL_CASES, GetTotalScore("a", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES + EXCEPTIONAL_CASES, GetTotalScore("", ""));
    EXPECT_EQ(EXCEPTIONAL_CASES + EXCEPTIONAL_CASES, GetTotalScore("1", "A"));
    EXPECT_EQ(EXCEPTIONAL_CASES + EXCEPTIONAL_CASES, GetTotalScore("A", "@"));
}