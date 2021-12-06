#include "vector_util.h"
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n =matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        int max_len = 0;
        for(int i=0; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(matrix[i][j] != '1') continue;
                int left = (j==0)? 0 : dp[i][j-1];
                int up = (i==0)? 0 : dp[i-1][j];
                int up_left = (i==0 || j==0)? 0: dp[i-1][j-1];
                dp[i][j] = min(min(left, up), up_left) + 1;
                max_len = max(max_len, dp[i][j]);
            }
        }
        // printVec(dp);
        return max_len * max_len ;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<char>> q;

    q= {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    EXPECT_EQ(s.maximalSquare(q), 4);

    q = {{'0','1'},{'1','0'}};
    EXPECT_EQ(s.maximalSquare(q), 1);
    q = {{1}};
    EXPECT_EQ(s.maximalSquare(q), 0);

}