#include <iostream>
#include <vector>
/*
Example 1:

Input: x = 4
Output: 2
Explanation: The square root of 4 is 2, so we return 2.

Example 2:

Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.
*/

class Solution {
public:
    int mySqrt(int x) {
        int left = 0;
        int right = x;
        while (left <= right)
        {
            long m = left + (right - left)/2;
            if ( m * m > x)
                right = m - 1;
            else
                left = m + 1;
        }
        return right;
    }
};

int main()
{
    int result = Solution().mySqrt(8);
    std::cout << result;

    return 0;
}