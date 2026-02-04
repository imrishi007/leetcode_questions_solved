#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

class Solution {
public:
    typedef long long ll;
    int n;
    std::vector<vector<ll>> memo;

    ll solve(int i, int trend, std::vector<int>& nums) {
        if(i == n) {
            if(trend == 3) {
                return 0; // valid end
            } else {
                return LLONG_MIN / 2; // invalid state
            }
        }

        if(memo[i][trend] != LLONG_MIN) {
            return memo[i][trend];
        }

        ll take = LLONG_MIN / 2;
        ll skip = LLONG_MIN / 2;

        // Skip
        if(trend == 0){
            skip = solve(i + 1, 0, nums);
        }

        // Take current element and stop if it is in trend 3 - increasing;
        if(trend == 3){
            take = nums[i];
        }

        if(i + 1 < n){
            int curr = nums[i];
            int next = nums[i + 1];

            //There is no trend yet but we can start a trend from now since it is increasing from next number;
            if(trend == 0 && next > curr){
                take = std::max(take, curr + solve(i + 1, 1, nums));
            }

            //For trend == 1 - increasing trend
            if(trend == 1 && next > curr){
                //If next > curr we can continue the increasing trend or stop here
                take = max(take, curr + solve(i + 1, 1, nums));
            }
            else if(trend == 1 && next < curr){
                //If next < curr and the current trend is increasing then we can change the trend to decreasing
                take = max(take, curr + solve(i + 1, 2, nums));
            }

            //For trend == 2 - decreasing trend
            else if(trend == 2 && next < curr){
                //If the current trend is decreasing and the next element is smaller than the current one then we can just continue the current trend
                take = max(take, curr + solve(i + 1, 2, nums));
            }
            else if(trend == 2 && next > curr){
                //If the current trend is decreasing and we obtain a new trend we go to trend 3;
                take = max(take, curr + solve(i + 1, 3, nums));
            }

            //For trend == 3
            else if(trend == 3 && next > curr){
                //If we are in trend 3 and the next element is smaller than the current one we can just take it and stop
                take = max(take, curr + solve(i + 1, 3, nums));
            }
        }

        return memo[i][trend] = max(take, skip);
    }

    ll maxSumTrionic(vector<int>& nums) {
        n = nums.size();
        memo.assign(n + 1, vector<ll>(4, LLONG_MIN));
        return solve(0, 0, nums);
    }
};

int main() {
  Solution sol;
  std::vector<int> nums = {0, -2, -1, -3, 0, 2, -1};
  long long result = sol.maxSumTrionic(nums);
  std::cout << "Maximum Sum Trionic: " << result << std::endl;
}