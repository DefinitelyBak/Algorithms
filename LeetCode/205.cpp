#include <iostream>
#include <string>
#include <unordered_map>
/*
Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.


Example 1:

Input: s = "egg", t = "add"
Output: true
Explanation:
The strings s and t can be made identical by:
Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

Example 2:

Input: s = "foo", t = "bar"
Output: false
Explanation:
The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:
Input: s = "paper", t = "title"
Output: true
*/

class Solution {
public:
    bool isIsomorphic(std::string s, std::string t)
    {
        std::unordered_map<char, int> s_to_t;
        std::unordered_map<char, int> t_to_s;

        for (size_t i = 0; i < s.size(); ++i)
        {
            char cs = s[i];
            char ct = t[i];

            if (s_to_t.find(cs) == s_to_t.end())
                s_to_t[cs] = ct;
            else
                if (s_to_t[cs] != ct)
                    return false;

            if (t_to_s.find(ct) == t_to_s.end())
                t_to_s[ct] = cs;
            else
                if (t_to_s[ct] != cs)
                    return false;
        }
        return true;
    }
};

int main()
{
    std::string s = "bbbaaaba";
    std::string t = "aaabbbba";
    bool result = Solution().isIsomorphic(s, t);
    std::cout << result;

    return 0;
}