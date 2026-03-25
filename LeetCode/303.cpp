#include <iostream>
#include <vector>
/*
Given an integer array nums, handle multiple queries of the following type:
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:
NumArray(int[] nums) Initializes the object with the integer array nums.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 
Example 1:
Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]

Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
*/

class NumArray {
    std::vector<int> _pref;
public:
    NumArray(std::vector<int>& nums)
    {
        _pref.resize(nums.size());
        _pref[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
            _pref[i] = _pref[i - 1] + nums[i];
    }
    
    int sumRange(int left, int right)
    {
        if (left == 0)
            return _pref[right];
        return _pref[right] - _pref[left - 1];
    }
};

int main()
{
    std::vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray numArray(nums);
    std::cout << numArray.sumRange(0, 2) << std::endl; // return 1
    std::cout << numArray.sumRange(2, 5) << std::endl; // return -1
    std::cout << numArray.sumRange(0, 5) << std::endl; // return -3
    return 0;
}
