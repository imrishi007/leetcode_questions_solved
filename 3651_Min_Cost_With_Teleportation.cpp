class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j] = minimum cost to go from (i,j) to bottom-right
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));

        // Store all grid positions
        vector<pair<int,int>> cells;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({i, j});
            }
        }

        sort(cells.begin(), cells.end(), [&](auto &a, auto &b) {
            return grid[a.first][a.second] < grid[b.first][b.second];
        });

        // Repeat relaxation k+1 times
        for (int step = 0; step <= k; step++) {

            int bestSoFar = INT_MAX;
            int start = 0;

            for (int i = 0; i < cells.size(); i++) {
                int r = cells[i].first;
                int c = cells[i].second;

                bestSoFar = min(bestSoFar, dp[r][c]);

                // If next cell has same value, wait
                if (i + 1 < cells.size() &&
                    grid[r][c] == grid[cells[i + 1].first][cells[i + 1].second])
                    continue;

                // Assign best dp to all same-value cells
                for (int j = start; j <= i; j++) {
                    dp[cells[j].first][cells[j].second] = bestSoFar;
                }
                start = i + 1;
            }

            for (int i = m - 1; i >= 0; i--) {
                for (int j = n - 1; j >= 0; j--) {

                    if (i == m - 1 && j == n - 1) {
                        dp[i][j] = 0;
                        continue;
                    }

                    if (i + 1 < m)
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + grid[i + 1][j]);

                    if (j + 1 < n)
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + grid[i][j + 1]);
                }
            }
        }
        return dp[0][0];
    }
};