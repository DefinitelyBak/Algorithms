#include <vector>
#include <iostream>
#include <algorithm>
/*
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
*/

class Solution {
public:
    int longestOnes(std::vector<int>& nums, int k) {
        int res = 0;
        int left = 0;
        int right = 0;
        while (right < nums.size())
        {
            if (nums[right] != 0)
                right++;
            else if (k > 0)
            {
                right++;
                k--;
            }
            else
            {
                res = std::max(res, right - left);
                while (nums[left] != 0)
                    left++;
                left++;
                k++;
            }
        }
        res = std::max(res, right-left);
        return res;
    }         
};

void main()
{
    Solution sol;
    std::vector<int> nums1 = {1,1,1,0,0,0,1,1,1,1,0};
    int k1 = 2;
    std::cout << sol.longestOnes(nums1, k1) << std::endl; // Output: 6

    std::vector<int> nums2 = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    int k2 = 3;
    std::cout << sol.longestOnes(nums2, k2) << std::endl; // Output: 10
}