class Solution {
public:
    typedef long long ll;
    typedef pair<ll,ll> pll;
    long long minimumCost(vector<int>& nums, int k, int dist) {
        //We must divide the array into k subarrays
        //Ans == sum of first elements of each subarray
        //First subarray always starts at nums[0]
        //Distance between second and last subarray's first number must be at least dist
        //Use sliding window to find best subarray with minimal cost between the second and last subarray's first numbers
        //We will use two sorted multisets - one to maintain the current window elements and other to maintain the smallest elements outside window
        ll n = nums.size();
        ll ans = LLONG_MAX;
        set<pll> window;
        set<pll> outside;
        ll windowSum = 0;

        // Initialize the first window
        int i = 1;
        while(i - dist < 1){
            window.insert({nums[i],i});
            windowSum += nums[i];
            if(window.size() > k - 1){
                auto it = prev(window.end());
                outside.insert(*it);
                windowSum -= it->first;
                window.erase(it);
            }
            i++;
        }

        //Iterate through the rest of the array
        while(i < n){
            window.insert({nums[i],i});
            windowSum += nums[i];

            if(window.size() > k - 1){
                auto it = prev(window.end());
                outside.insert(*it);
                windowSum -= it->first;
                window.erase(it);
            }

            ans = min(ans, windowSum);
            
            pll remove = {nums[i - dist ], i - dist };

            //Remove the element going out of the window
            if(window.find(remove) != window.end()){
                window.erase(remove);
                windowSum -= remove.first;
                if (!outside.empty())
                {
                    pll toAdd = *outside.begin();
                    outside.erase(toAdd);
                    windowSum += toAdd.first;
                    window.insert(toAdd);
                }
            }else{
                outside.erase(remove);
            }

            i++;
        
        }

        return nums[0] +ans;
    }
};

// Example - Input: nums = [1,3,5,2,8,4,6], k = 3, dist = 2
//We must form 3 subarrays from nums with difference of second and last
//subarray's first number at least 2

//Possible subarrays:
//[1] [3,5] [2,8,4,6] -> Cost = 1 + 3 + 2 = 6
//[1] [3,5,2] [8,4,6] -> Cost = 1 + 3 + 8 = 12
//[1] [3,5,2,8] [4,6] -> Cost = 1 + 3 + 4 = 8
//[1] [3,5,2,8,4] [6] -> Cost = 1 + 3 + 6 = 10
//Minimum cost is 6
//Output: 6

//Dry run -
//Initialize window with first possible elements for second subarray
//window = {3,5}, outside = {}, windowSum = 8
//Iterate through the rest of the array
//i = 4 -> window = {2,3}, outside = {5}, windowSum = 5, ans = 5
//i = 5 -> window = {2,3,4}, outside = {5}, windowSum = 9, ans = 5
//i = 6 -> window = {2,3,4}, outside = {5,6}, windowSum = 9, ans = 5
//Final answer = nums[0] + ans = 1 + 5 = 6 