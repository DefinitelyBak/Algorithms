#include <vector>
#include <numeric>
#include <iostream>
/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []
*/

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> temp;
        backtrack(result, temp, candidates, target, 0);
        return result;
    }

    void backtrack(std::vector<std::vector<int>>& out, std::vector<int>& tmp,
                   const std::vector<int>& candidates, int target, int start)
    {
        int sum = std::accumulate(tmp.begin(), tmp.end(), 0);

        if (sum == target)
        {
            out.push_back(tmp);
            return;
        }
        if (sum > target)
            return;

        for (int i = start; i < candidates.size(); i++)
        {
            tmp.push_back(candidates[i]);
            backtrack(out, tmp, candidates, target, i);
            tmp.pop_back();
        }
    }
};

int main()
{
    std::vector<int> candidates{2,3,6,7};
    int target = 7;
    std::vector<std::vector<int>> result = Solution().combinationSum(candidates, target);
    for (const auto& combination : result) {
        std::cout << "[";
        for (const auto& num : combination) {
            std::cout << num << ",";
        }
        std::cout << "]" << std::endl;
    }
    return 0;
}