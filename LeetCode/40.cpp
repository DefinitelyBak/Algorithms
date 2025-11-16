#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output:
[
[1,2,2],
[5]
]
*/
class Solution
{
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> temp;
        std::sort(candidates.begin(), candidates.end());
        backtrack(result, temp, candidates, target, 0);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>> &out, std::vector<int> &tmp, const std::vector<int> &candidates, int target, int start)
    {
        auto sum = std::accumulate(tmp.begin(), tmp.end(), 0);
        if (sum == target)
        {
            out.push_back(tmp);
            return;
        }
        else if (sum > target)
            return;

        for (int i = start; i < candidates.size(); i++)
        {
            if (i > start && candidates[i] == candidates[i - 1])
                continue;
            tmp.push_back(candidates[i]);
            backtrack(out, tmp, candidates, target, i + 1);
            tmp.pop_back();
        }
    }
};

int main()
{
    std::vector<int> candidates{2, 5, 2, 1, 2};
    int target = 5;
    std::vector<std::vector<int>> result = Solution().combinationSum2(candidates, target);
    for (const auto &combination : result)
    {
        std::cout << "[";
        for (const auto &num : combination)
        {
            std::cout << num << ",";
        }
        std::cout << "]" << std::endl;
    }
    return 0;
}