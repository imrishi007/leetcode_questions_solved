class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        //Vector is already sorted so we check two conditions - 
        // 1. sum[l] + sum[r] < target -> l++;
        // 2. sum[l] + sum[r] > target -> r--;
        int l = 0, r = numbers.size() - 1;
        while(l < r){
            int sum = numbers[l] + numbers[r];
            if(sum == target){
                return {l+1, r+1};
            }
            else if(sum < target){
                l++;
            }
            else{
                r--;
            }
        }
        return {};      
    }
};