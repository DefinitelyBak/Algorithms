#include <iostream>
#include <vector>
/*
Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3

Output: [1,2,3,4]

Example 2:

Input: arr = [1,1,2,3,4,5], k = 4, x = -1

Output: [1,1,2,3]
*/

class Solution {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        int left = 0, right = arr.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left)/2;
            if (arr[mid] == x)
            {
                left = mid;
                right = mid;
                break;
            }
            else if (arr[mid] < x)
                left = mid + 1;
            else
                right = mid;
        }
        
        std::vector<int> result;
        while (k)
        {
            if (left > 0 && right < arr.size())
            {
                if (std::abs(arr[left - 1] - x) <= std::abs(arr[right] - x))
                    result.insert(result.begin(), arr[--left]);
                else
                    result.push_back(arr[right++]);
            }
            else if (left > 0)
                result.insert(result.begin(), arr[--left]);
            else
                result.push_back(arr[right++]);
            --k;
        }
        return result;
    }
};

int main()
{
    std::vector<int> input {1,1,2,3,4,5};
    int k = 4;
    int x = -1;
    Solution().findClosestElements(input, k, x);

    return 0;
}