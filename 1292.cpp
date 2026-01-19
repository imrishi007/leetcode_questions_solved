#include<bits.stdc++.h>
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int rows = mat.size();
        int cols = mat[0].size();

        // 2D prefix sum: pref[i][j] = sum of mat[0..i-1][0..j-1]
        vector<vector<int>> pref(rows + 1, vector<int>(cols + 1, 0));

        for(int i = 1; i <= rows; i++){
            for(int j = 1; j <= cols; j++){
                pref[i][j] = mat[i-1][j-1] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
            }
        }

        auto possible = [&](int len) {
            for(int i = 0; i + len <= rows; i++){
                for(int j = 0; j + len <= cols; j++){
                    int r1 = i, c1 = j;
                    int r2 = i + len, c2 = j + len;
                    // Sum of submatrix from (r1, c1) to (r2-1, c2-1)
                    int sum = pref[r2][c2] - pref[r1][c2] - pref[r2][c1] + pref[r1][c1];
                    if(sum <= threshold) return true;
                }
            }
            return false;
        };

        int l = 0, r = min(rows, cols);
        int ans = 0;

        while(l <= r){
            int mid = l + (r - l) / 2;

            if(possible(mid)){
                ans = mid;
                l = mid + 1;   // try bigger square
            } else {
                r = mid - 1;   // try smaller square
            }
        }

        return ans;
    }
};

// pref[i][j] stores sum of submatrix from (0,0) to (i-1, j-1) in mat.
// i and j are 1-based for pref so that pref[0][*] and pref[*][0] = 0 (easy boundaries).
//
// Diagram (building pref[i][j]):
//
// We want the sum of this rectangle:
//
//      (0,0) ---------------------> j-1
//        |   [ covered area up to current cell ]
//        |
//        v i-1
//
// To compute pref[i][j], we combine:
//
// 1) pref[i-1][j]  -> sum of area ABOVE current row
// 2) pref[i][j-1]  -> sum of area LEFT of current column
//
// But the overlap area (top-left block) is counted twice:
//
//      +-------------------+
//      | overlap (counted) |
//      +-------------------+----
//      |                   |
//      |                   |
//      +-------------------+
//
// overlap = pref[i-1][j-1]
//
// So we subtract overlap once, then add current cell mat[i-1][j-1].
//
// Final formula:
// pref[i][j] = mat[i-1][j-1] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];

// Compute sum of submatrix using 2D prefix sum in O(1).
//
// Suppose we want sum of rectangle with corners:
// (r1,c1) = top-left (inclusive)
// (r2,c2) = bottom-right (exclusive in pref coordinates)
//
// pref[x][y] contains sum of area from (0,0) to (x-1,y-1).
//
// Diagram:
//
//          c1        c2
//       ----|--------|----
//        A  |   B    |
// r1    ----|--------|----
//        C  |   D    |
// r2    ----|--------|----
//
// We want sum of region D.
//
// pref[r2][c2] = A + B + C + D
// pref[r1][c2] = A + B            (remove top part)
// pref[r2][c1] = A + C            (remove left part)
//
// After subtracting both, region A is removed twice, so add it back once:
//
// sum = pref[r2][c2] - pref[r1][c2] - pref[r2][c1] + pref[r1][c1];