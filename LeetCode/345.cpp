#include <iostream>
#include <string>
#include <unordered_set>
/*
Given a string s, reverse only all the vowels in the string and return it.
The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:

Input: s = "IceCreAm"
Output: "AceCreIm"
Explanation:
The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Example 2:

Input: s = "leetcode"
Output: "leotcede"
*/

class Solution {
    bool isVowel(char c)
    {
        char ch = tolower(c);
        return ch == 'a' || ch == 'e' || ch =='i' || ch == 'o' || ch == 'u';
    }
public:
    std::string reverseVowels(std::string s) {
        if (s.empty() || s.size() == 1)
            return s;
        int l = 0;
        int r = s.size() - 1;
        while (l < r)
        {
            char cl = s[l];
            char cr = s[r];
            if (isVowel(cl) && isVowel(cr))
            {
                std::swap(s[l], s[r]);
                l++;
                r--;
            }
            else
            {
                if (isVowel(cl) == 0)
                    l++;
                if (isVowel(cr) == 0)
                    r--;
            }
        }
        return s;
    }
};

int main()
{
    std::string s = "IceCreAm";
    auto result = Solution().reverseVowels(s);
    std::cout << result;

    return 0;
}