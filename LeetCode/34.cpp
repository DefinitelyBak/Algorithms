#include <iostream>
#include <vector>
/*
Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
*/

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) 
    {
        int left = 0, right = nums.size() - 1;
        int first = -1, last = -1;
        
        while (left <= right)
        {
            int mid = left + (right - left)/2;
            if (nums[mid] == target)
            {
                first = mid;
                last = mid;
                while (first > 0 && nums[first-1] == target)
                    --first;
                while (last < nums.size() - 1 && nums[last + 1] == target)
                    ++last;
                break;
            }
            else if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return {first, last};
    }
};

int main()
{
    std::vector<int> input {};
    std::vector<int> result = Solution().searchRange(input, 0);
    for (int i : result) {
        std::cout << i << " ";
    }
    return 0;
}