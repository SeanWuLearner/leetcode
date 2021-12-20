class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for(int i=1; i<m ; i++){
            for(int j=1; j<n ; j++){
                dp[j] = dp[j-1] + dp[j];
            }
        }
        return dp[n-1];
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.uniquePaths(3,7), 28);
    EXPECT_EQ(s.uniquePaths(3,2), 3);
    EXPECT_EQ(s.uniquePaths(7,3), 28);
    EXPECT_EQ(s.uniquePaths(3,3), 6);
}