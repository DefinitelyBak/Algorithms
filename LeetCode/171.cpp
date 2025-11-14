#include <iostream>
#include <string>
/*
Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.

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

Input: columnTitle = "A"
Output: 1

Example 2:

Input: columnTitle = "AB"
Output: 28

Example 3:

Input: columnTitle = "ZY"
Output: 701
*/

class Solution {
public:
    int titleToNumber(std::string columnTitle) {
        int result = 0;
        auto begin = columnTitle.rbegin();
        auto end = columnTitle.rend();
        int pow = 1;
        while (begin != end)
        {
            result += int(*begin - 'A' + 1) * pow;
            pow *= 26;
            ++begin;
        }
        return result;
    }
};

int main()
{
    int result = Solution().titleToNumber("AB");
    std::cout << result;

    return 0;
}