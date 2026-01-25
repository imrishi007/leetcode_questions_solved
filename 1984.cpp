#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if(k <= 1) return 0;
        
        std::sort(nums.begin(),nums.end());

        int n = nums.size();
        int minDiff = INT_MAX;

        for(int i = 0 ; i < n - k + 1 ;i++){
            minDiff = std::min(minDiff , nums[i+k-1] - nums[i]);
        }
        return minDiff;
    }
};