class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1);
        dp[0] = dp[1] = 1;
        for(int i=2 ; i<=n ; i++){
            for(int j=0 ; j<i; j++)
                dp[i] += dp[j] * dp[i-j-1];
                /* idea: all possible trees while picking one node is,
                    variations_of_left_nodes times variations_of_right_nodes.
                    We just need to sum up the num of trees while taking each
                    node as root.

                  dp[2] = dp[0]dp[1] + dp[1]*dp[0]
                  dp[3] = dp[0]dp[2] + dp[1]*dp[1] + dp[2]dp[0]
                  dp[5] = dp[0]*dp[4] + dp[1]*dp[3] + ...
                */
        }
        return dp[n];
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.numTrees(3), 5);
    EXPECT_EQ(s.numTrees(1), 1);
}