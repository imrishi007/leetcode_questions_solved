#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int longestBalanced(std::vector<int> &nums) {
        int n = nums.size();
        std::unordered_map<int, int> eveFreq, oddFreq;
        int maxL = 0, l = 0;

        for (int r = 0; r < n; r++) {
            if (nums[r] % 2 == 0) {
                eveFreq[nums[r]]++;
            } else {
                oddFreq[nums[r]]++;
            }

            while (l <= r && eveFreq.size() != oddFreq.size()) {
                if (nums[l] % 2 == 0) {
                    if (--eveFreq[nums[l]] == 0) {
                        eveFreq.erase(nums[l]); 
                    }
                } else {
                    if (--oddFreq[nums[l]] == 0) {
                        oddFreq.erase(nums[l]); 
                    }
                }
                l++;
            }

            if (eveFreq.size() == oddFreq.size()) {
                maxL = std::max(maxL, r - l + 1);
            }
        }
        return maxL;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {30, 27, 25}; 
    // {30} -> 1 distinct even, 0 odd (Unbalanced) -> Shrink
    // {27} -> 0 even, 1 distinct odd (Unbalanced) -> Shrink
    // {30, 27} -> 1 even, 1 odd (Balanced!) -> Length 2
    std::cout << "Longest Balanced Subarray: " << sol.longestBalanced(nums) << std::endl;
    return 0;
}