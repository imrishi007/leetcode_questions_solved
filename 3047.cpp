class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        long long maxArea = 0;
        int n = bottomLeft.size();
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                int left = max(bottomLeft[i][0], bottomLeft[j][0]);
                int right = min(topRight[i][0], topRight[j][0]);
                int bottom = max(bottomLeft[i][1], bottomLeft[j][1]);
                int top = min(topRight[i][1], topRight[j][1]);
                if(left < right && bottom < top){
                    int side = min(right - left, top - bottom);
                    maxArea = max(maxArea, (long long)side * side);
                }
            }
        }
        return maxArea;
    }
};

//Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]

// We must find the largest square that can be formed between two or more overlapping rectangles
// We can iterate through each pair of rectangles and calculate the overlapping area
// For each overlapping area, we can determine the largest square that can fit within that area
// We will keep track of the maximum square area found during these calculations