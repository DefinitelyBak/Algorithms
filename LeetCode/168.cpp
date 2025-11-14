#include <iostream>
#include <string>
/*
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
For example:
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...

Example 1:

Input: columnNumber = 1
Output: "A"

Example 2:

Input: columnNumber = 28
Output: "AB"

Example 3:

Input: columnNumber = 701
Output: "ZY"
*/

class Solution {
public:
    std::string convertToTitle(int columnNumber)
    {
        std::string result;
        while (columnNumber)
        {
            --columnNumber;
            char ch = 'A' + (columnNumber % 26);
            result.insert(result.begin(), ch);
            columnNumber /= 26;
        }
        return result;
    }
};

int main()
{
    std::string result = Solution().convertToTitle(701);
    std::cout << result;

    return 0;
}