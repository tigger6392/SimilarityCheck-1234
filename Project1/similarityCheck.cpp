#include <codecvt>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

const int EXCEPTIONAL_CASES = -1;
const int NORMAL_CASES = 0;
const int MAX_LENGTH_SCORE = 60;
const int MAX_ALPHA_SCORE = 40;
const int MAX_ALPHA_NUMS = 27;

class SimilarityCheck
{
public:
    int LengthCheck(const string& input1, const string& input2)
    {
        if (CheckInputStrings(input1, input2) == EXCEPTIONAL_CASES)
            return EXCEPTIONAL_CASES;
        if (CheckDoubleStrings(input1, input2))	return 0;

        return GetLengthScoreForNormalCases(input1, input2);
    }
    int AlphaCheck(const string& input1, const string& input2)
    {
        if (CheckInputStrings(input1, input2) == EXCEPTIONAL_CASES)
            return EXCEPTIONAL_CASES;
        if (CheckAllDifferentChars(input1, input2))	return 0;

        return GetAlphaScoreForNormalCases(input1, input2);
    }

private:
    int CheckInputStrings(const string& input1, const string& input2)
    {
        try
        {
            CheckInvalidInput(input1, input2);
        }
        catch (invalid_argument& e)
        {
            cout << "ERR: " << e.what() << endl;
            return EXCEPTIONAL_CASES;
        }
        return NORMAL_CASES;
    }
    void CheckInvalidInput(const string& input1, const string& input2)
    {
        if (input1.length() == 0 || input2.length() == 0)
        {
            throw invalid_argument("Empty string!");
        }
        if (HasWrongChar(input1) || HasWrongChar(input2))
        {
            throw invalid_argument("Has wrong char!");
        }
    }
    bool HasWrongChar(const string& input)
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (!(input[i] >= 'A' && input[i] <= 'Z')) return true;
        }
        return false;
    }
    bool CheckDoubleStrings(const string& input1, const string& input2)
    {
        if (input1.length() >= (input2.length() * 2) ||
            input2.length() >= (input1.length() * 2))
        {
            return true;
        }
        return false;
    }
    int GetLengthScoreForNormalCases(const string& input1, const string& input2)
    {
        if (input1.length() == input2.length())	return MAX_LENGTH_SCORE;
        int gap = max(input1.length(), input2.length()) -
            min(input1.length(), input2.length());
        return MAX_LENGTH_SCORE -
            (MAX_LENGTH_SCORE * gap / min(input1.length(), input2.length()));
    }
    bool CheckAllDifferentChars(const string& input1, const string& input2)
    {
        for (int i = 0; i < input1.length(); i++)
        {
            for (int j = 0; j < input2.length(); j++)
            {
                if (input1[i] == input2[j]) return false;
            }
        }
        return true;
    }
    int GetAlphaScoreForNormalCases(const string& input1, const string& input2)
    {
        int map1[MAX_ALPHA_NUMS] = { 0, };
        int map2[MAX_ALPHA_NUMS] = { 0, };
        FillAlphabetMap(input1, map1);
        FillAlphabetMap(input2, map2);
        return (MAX_ALPHA_SCORE * GetSameCnt(map1, map2) / GetTotalCnt(map1, map2));
    }
    void FillAlphabetMap(const string& input, int* map)
    {
        for (int i = 0; i < input.length(); i++) map[input[i] - 'A']++;
    }
    int GetTotalCnt(int* map1, int* map2)
    {
        int totalCnt = 0;
        for (int i = 0; i < MAX_ALPHA_NUMS; i++)
        {
            if (map1[i] || map2[i]) totalCnt++;
        }
        return totalCnt;
    }
    int GetSameCnt(int* map1, int* map2)
    {
        int sameCnt = 0;
        for (int i = 0; i < MAX_ALPHA_NUMS; i++)
        {
            if (map1[i] && map2[i]) sameCnt++;
        }
        return sameCnt;
    }
};
