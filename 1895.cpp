class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> rowPrefix(rows, vector<int>(cols + 1, 0));
        vector<vector<int>> colPrefix(rows + 1, vector<int>(cols, 0));
        vector<vector<int>> diag1Prefix(rows + 1, vector<int>(cols + 1, 0));
        vector<vector<int>> diag2Prefix(rows + 1, vector<int>(cols + 2, 0));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                //Calculate rowprefix sum
                rowPrefix[r][c + 1] = rowPrefix[r][c] + grid[r][c];
                //Calculate colprefix
                colPrefix[r + 1][c] = colPrefix[r][c] + grid[r][c];
                //Calculate diagonal sum
                diag1Prefix[r + 1][c + 1] = diag1Prefix[r][c] + grid[r][c];
                //Calculate Anti diagonal
                diag2Prefix[r + 1][c] = diag2Prefix[r][c + 1] + grid[r][c];
            }
        }
        int maxSize = std::min(rows, cols);
        //First loop iterates from maximum possible size to minimum size of 1. 
        for (int size = maxSize; size >= 1; --size) {
            for (int r = 0; r <= rows - size; ++r) {
                for (int c = 0; c <= cols - size; ++c) {
                    //Calculate target sum using the first row of the current square
                    int targetSum = rowPrefix[r][c + size] - rowPrefix[r][c];
                    bool isMagic = true;
                    for (int k = 0; k < size; ++k) {
                        //If any row or column doesnt match target sum, just break hahahahaha
                        if (rowPrefix[r + k][c + size] - rowPrefix[r + k][c] != targetSum ||
                            colPrefix[r + size][c + k] - colPrefix[r][c + k] != targetSum) {
                            isMagic = false;
                            break;
                        }
                    }
                    //After checking all rows and columns check for diagonals haha
                    int diag1 = diag1Prefix[r + size][c + size] - diag1Prefix[r][c];
                    int diag2 = diag2Prefix[r + size][c] - diag2Prefix[r][c + size];
                    if (diag1 != targetSum || diag2 != targetSum) isMagic = false;

                    if (isMagic) {
                        return size;
                    }
                }
            }
        }
        return 1;
    }
};

//Approach - Calculate prefix sums for rows, columns, and diagonals to efficiently check sums of sub-squares. 
//Iterate from the largest possible square size down to 1, checking each sub-square for the magic square property. 
//Return the size of the largest magic square found.

//Complexity - Time - O(N^2 * min(N, M)), Space - O(N * M) for prefix sum storage.