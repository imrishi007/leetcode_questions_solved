#include<iostream>
#include<vector>
#include<algorithm>
class Solution {
public:
    int minRemoval(std::vector<int>& nums, int k) {
        std::sort(nums.begin(),nums.end());
        int n = nums.size();
        int l =0 , r = 0, maxWindow = 0;
        while(r < n){
            int max = nums[r];
            int min = nums[l];
            while(l < r && max > k*min){
                l++;
            }
            maxWindow = std::max(maxWindow, r-l+1);
            r++;
        }
        return n - maxWindow;
    }
};

int main(){
    Solution s;
    std::vector<int> nums = {8,99,65,16,39};
    int k = 3;
    std::cout << s.minRemoval(nums, k) << std::endl;
    return 0;
}