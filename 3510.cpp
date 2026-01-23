
class Solution {
   public:
    typedef long long ll;
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();

        vector<ll> temp(n);

        for (int i = 0; i < n; i++) {
            temp[i] = nums[i];
        }

        set<pair<ll, int>> minPairSet;
        vector<int> nextInd(n);
        vector<int> prevInd(n);
        int badPairs = 0;

        for (int i = 0; i < n; i++) {
            nextInd[i] = i + 1;
            prevInd[i] = i - 1;
        }

        for (int i = 0; i < n - 1; i++) {
            if (temp[i] > temp[i + 1]) {
                badPairs++;
            }
            minPairSet.insert({temp[i] + temp[i + 1], i});
        }

        int operations = 0;

        while (badPairs > 0) {
            int first = minPairSet.begin()->second;
            int second = nextInd[first];
            int first_left = prevInd[first];
            int second_right = nextInd[second];

            minPairSet.erase(begin(minPairSet));

            if (temp[first] > temp[second]) {
                badPairs--;
            }

            if (first_left >= 0) {
                if (temp[first_left] > temp[first] &&
                    temp[first_left] <= temp[first] + temp[second]) {
                    badPairs--;
                }
            } else if (temp[first_left] <= temp[first] &&
                       temp[first_left] > temp[first] + temp[second]) {
                badPairs++;
            }

            if (second_right < n) {
                if (temp[second] > temp[second_right] && temp[first] <= temp[second_right]) {
                    badPairs--;
                } else if (temp[second] <= temp[second_right] && temp[first] > temp[second_right]) {
                    badPairs++;
                }
            }
            if (first_left >= 0) {
                minPairSet.erase({temp[first_left] + temp[first], first_left});
                minPairSet.insert({temp[first_left] + temp[second] + temp[second], first_left});
            }
            if (second_right < n) {
                minPairSet.erase({temp[second] + temp[second_right], second});
                minPairSet.insert({temp[first] + temp[second_right] + temp[second], first});
                prevInd[second_right] = first;
            }
            nextInd[first] = second_right;
            temp[first] += temp[second];

            operations++;
        }
        return operations;
    }
};