#include<iostream>
#include<vector>

class Solution {
public:

    //TLE
    double t[101][101];

    double solve(int poured, int i , int j){
        if(i < 0 || j < 0 || j > i) return 0.0;
        if(i == 0 && j == 0) return poured;
        if(t[i][j] != -1) return t[i][j];

        double left = (solve(poured, i - 1, j - 1)-1.0)/2.0;
        double right = (solve(poured, i - 1, j)-1.0)/2.0;
        
        if(right < 0) right = 0.0;
        if(left < 0) left = 0.0;
        
        return t[i][j] = left + right;

    }

    double champagneTower(int poured, int query_row, int query_glass) {
        
        for(int i = 0; i < 101; i++){
            for(int j = 0; j < 101; j++){
                t[i][j] = -1;
            }
        }

        return std::min(1.0, solve(poured, query_row, query_glass));
    }

    //Top Down Approach 
    double champagneTower(int poured, int query_row, int query_glass) {
        double dp[101][101] = {0};
        dp[0][0] = poured;

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j <= i; j++) {
                if (dp[i][j] > 1.0) {
                    double extra = (dp[i][j] - 1.0) / 2.0;
                    dp[i + 1][j] += extra;
                    dp[i + 1][j + 1] += extra;
                    dp[i][j] = 1.0;
                }
            }
        }
        return min(1.0, dp[query_row][query_glass]);
    }
};

int main(){
    Solution s;
    std::cout << s.champagneTower(100000009, 33, 17) << std::endl;
    return 0;
}