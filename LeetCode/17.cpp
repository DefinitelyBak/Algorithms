#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
/*
Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = "2"
Output: ["a","b","c"]
*/

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        std::unordered_map<char, std::string> numberToChars
        {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
        };

        std::vector<std::string> result;
        for (auto dig : digits)
        {
            std::vector<std::string> newResult;
            for (auto insert : numberToChars[dig])
            {
                if (result.empty())
                    newResult.push_back(std::string(1, insert));
                else
                    for (auto last : result)
                    {
                        last.insert(last.end(), insert);
                        newResult.push_back(last);
                    }
            }
            result = newResult;
        }

        return result;
    }
};

/*
Оптимально решение:
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        static const unordered_map<char, string> numberToChars {
            {'2',"abc"}, {'3',"def"}, {'4',"ghi"}, {'5',"jkl"},
            {'6',"mno"}, {'7',"pqrs"}, {'8',"tuv"}, {'9',"wxyz"}
        };

        vector<string> result = {""};

        for (char d : digits) {
            const string& chars = numberToChars.at(d);

            vector<string> next;
            next.reserve(result.size() * chars.size());

            for (const string& prefix : result)
                for (char c : chars)
                    next.push_back(prefix + c);

            result.swap(next);
        }

        return result;
    }
};
*/

int main()
{
    auto result = Solution().letterCombinations("23");
    for (const auto& str : result)
        std::cout << str << " ";
    return 0;
}