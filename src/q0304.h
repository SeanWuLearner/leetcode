/* my dp solution */
class NumMatrix_my {
    vector<vector<int>> dp;
    int m, n;
public:
    NumMatrix_my(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        dp = vector<vector<int>>(m, vector<int>(n));
        for(int i=m-1 ; i>=0 ; i--)
            for(int j=n-1 ; j>=0 ; j--){
                int add1 = (i+1 == m)? 0 : dp[i+1][j];
                int add2 = (j+1 == n)? 0 : dp[i][j+1];
                int overlap = (i+1==m || j+1==n)? 0 : dp[i+1][j+1];
                dp[i][j] = matrix[i][j] + add1 + add2 - overlap;
            }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int sub1 = (row2+1 == m)? 0 : dp[row2+1][col1];
        int sub2 = (col2+1 == n)? 0 : dp[row1][col2+1];
        int overlap = (row2+1 == m || col2+1 == n)? 0 : dp[row2+1][col2+1];
        return dp[row1][col1] - sub1 - sub2 + overlap;
    }
};

/* neater solution, just extend the dp array with 0 filled */
class NumMatrix {
    vector<vector<int>> dp;
    int m, n;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        dp = vector<vector<int>>(m+1, vector<int>(n+1, 0));
        for(int i=m-1 ; i>=0 ; i--)
            for(int j=n-1 ; j>=0 ; j--)
                dp[i][j] = matrix[i][j] + dp[i+1][j] + dp[i][j+1] - dp[i+1][j+1];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row1][col1] - dp[row2+1][col1] - dp[row1][col2+1] + dp[row2+1][col2+1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

 TEST(TestSolution, test1) {
    vector<vector<int>> m;

    m = {{3, 0, 1, 4, 2},
         {5, 6, 3, 2, 1},
         {1, 2, 0, 1, 5},
         {4, 1, 0, 1, 7},
         {1, 0, 3, 0, 5}};
    auto obj = NumMatrix(m);
    EXPECT_EQ(obj.sumRegion(2,1,4,3), 8);
    EXPECT_EQ(obj.sumRegion(1,1,2,2), 11);
    EXPECT_EQ(obj.sumRegion(1,2,2,4), 12);

}