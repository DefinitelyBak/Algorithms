#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:
Input: nums = [1]
Output: [[1]]
*/
class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> temp;
        backtrack(result, temp, nums);
        return result;
    }

    void backtrack(std::vector<std::vector<int>>& out, std::vector<int>& tmp, const std::vector<int>& nums)
    {
        if (tmp.size() == nums.size())
        {
            out.push_back(tmp);
            return;
        }

        for (auto n : nums)
        {
            auto it = std::find(tmp.begin(), tmp.end(), n);
            if (it != tmp.end())
                continue;
            tmp.push_back(n);
            backtrack(out, tmp, nums);
            tmp.pop_back();
        }
    }
};

int main()
{
    std::vector<int> nums = {1, 2, 3};
    std::vector<std::vector<int>> result = Solution().permute(nums);
    for (const auto& perm : result)
    {
        for (int num : perm)
            std::cout << num << " ";
        std::cout << std::endl;
    }
    return 0;
}