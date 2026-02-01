class Solution {
public:
    int totalTimeTaken(vector<int>&piles, int speed){
        int time = 0;
        for(int pile : piles){
            time += (pile + speed - 1) / speed; // Ceiling division
        }
        return time;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = *max_element(piles.begin(), piles.end());
        while(l < r){
            int mid = l + (r - l) / 2;
            if(totalTimeTaken(piles, mid) <= h){
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};