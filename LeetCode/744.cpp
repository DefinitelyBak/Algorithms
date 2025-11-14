#include <iostream>
#include <vector>
/*
Example 1:

Input: letters = ["c","f","j"], target = "a"
Output: "c"
Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.

Example 2:

Input: letters = ["c","f","j"], target = "c"
Output: "f"
Explanation: The smallest character that is lexicographically greater than 'c' in letters is 'f'.

Example 3:

Input: letters = ["x","x","y","y"], target = "z"
Output: "x"
Explanation: There are no characters in letters that is lexicographically greater than 'z' so we return letters[0].
*/

class Solution {
public:
    char nextGreatestLetter(std::vector<char>& letters, char target) {
        int left = 0;
        int right = letters.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left)/2;
            if (letters[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return letters[left];
    }
};

int main()
{
    std::vector<char> input {'x','x','y','y'};
    char result = Solution().nextGreatestLetter(input, 'z');
    std::cout << result;

    return 0;
}