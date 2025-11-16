#include <vector>
#include <string>
#include <iostream>
/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]
*/

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) 
    {
        std::vector<std::string> result;
        std::string temp;
        backtrack(result, temp, 0, 0, n);
        return result;
    }

    void backtrack(std::vector<std::string>& out, std::string& tmp, int open, int close, int max)
    {
        if (tmp.size() == max*2)
        {
            out.push_back(tmp);
            return;
        }

        if (open < max)
        {
            tmp.push_back('(');
            backtrack(out, tmp, open + 1, close, max);
            tmp.pop_back();
        }
        if( close < open)
        {
            tmp.push_back(')');
            backtrack(out, tmp, open, close + 1, max);
            tmp.pop_back();
        }
    }
};

int main()
{
    std::vector<std::string> result = Solution().generateParenthesis(2);
    for (const std::string& s : result)
        std::cout << s << std::endl;
    return 0;
}