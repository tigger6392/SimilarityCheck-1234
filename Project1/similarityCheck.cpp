#include <codecvt>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

const int EXCEPTIONAL_CASES = -1;
const int NORMAL_CASES = 0;
const int MAX_LENGTH_SCORE = 60;


class SimilarityCheck
{
public:
    int LengthCheck(const string& input1, const string& input2)
    {
        if (CheckInputStrings(input1, input2) == EXCEPTIONAL_CASES)
            return EXCEPTIONAL_CASES;
        if (CheckDoubleStrings(input1, input2))	return 0;

        return GetScoreForNormalCases(input1, input2);
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
    int GetScoreForNormalCases(const string& input1, const string& input2)
    {
        if (input1.length() == input2.length())	return MAX_LENGTH_SCORE;
        int gap = max(input1.length(), input2.length()) -
            min(input1.length(), input2.length());
        return MAX_LENGTH_SCORE -
            (MAX_LENGTH_SCORE * gap / min(input1.length(), input2.length()));
    }
};
