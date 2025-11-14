#include <iostream>
#include <vector>
/*
Example 1:

Input: num = 16
Output: true
Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

Example 2:

Input: num = 14
Output: false
Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an integer.
*/

class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        long mid;
        while (left <= right)
        {
            mid = left + (right - left)/2;
            long square = mid * mid;
            if (square == num)
                return true;
            else if (square > num)
               right = mid - 1; 
            else
                left = mid + 1;
        }

        return false;
    }
};

int main()
{
    bool result = Solution().isPerfectSquare(16);
    std::cout << result;

    return 0;
}