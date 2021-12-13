/*Solution1: Bottom up DP */
class Solution_BtnUp {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, INT_MAX);
        dp[0] = 0;
        sort(coins.begin(), coins.end());

        for(int i=1 ; i<=amount ; i++){
            for(int coin : coins){
                int start = i - coin;
                if(start < 0) break;
                if(dp[start] == INT_MAX) continue;
                dp[i] = min(dp[i], dp[start]+1);
            }
        }
        return (dp[amount] == INT_MAX)? -1 : dp[amount];

    }
};

/* Solution2: Top-down DP
    dp[i] = INT_MAX-1, while not reachable
          = INT_MAX, unvisited
          = others, num of coins sum up to i.
*/
class Solution_TopDown {
private:
    vector<int> dp;
    int helper(vector<int>& coins, int rem){
        if(rem < 0) return INT_MAX-1;
        if(dp[rem] <= INT_MAX-1) return dp[rem];
        for(int coin : coins){
            int prev = rem - coin;
            if(prev < 0) break;
            dp[rem] = min(dp[rem], helper(coins, prev) + 1);
        }
        if(dp[rem] == INT_MAX)
            dp[rem] = INT_MAX - 1;
        return dp[rem];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        dp = vector<int>(amount+1, INT_MAX);  // unvisited = INT_MAX, invalid = INT_MAX-1
        dp[0] = 0;
        sort(coins.begin(), coins.end());
        helper(coins, amount);
        return (dp[amount] >= INT_MAX-1)? -1 : dp[amount];

    }
};

/*Solution3: neater Top-Down DP
    dp[i] = -1, while not reachable
          = INT_MAX, unvisited
          = others, num of coins sum up to i.
*/
class Solution {
private:
    int helper(vector<int>& coins, int rem, vector<int>& dp){
        if(rem < 0) return -1;
        if(dp[rem] != INT_MAX ) return dp[rem];

        for(int coin : coins){
            int res = helper(coins, rem-coin, dp);
            if(res >= 0 && res < dp[rem])
                dp[rem] = res+1;
        }
        if(dp[rem]==INT_MAX)
            dp[rem] = -1;
        return dp[rem];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, INT_MAX);
        dp[0] = 0;
        helper(coins, amount, dp);
        return dp[amount];

    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {1,2,5};
    EXPECT_EQ(s.coinChange(q, 11), 3);
    q = {2};
    EXPECT_EQ(s.coinChange(q, 3), -1);
    q = {1};
    EXPECT_EQ(s.coinChange(q, 0), 0);
    q = {1};
    EXPECT_EQ(s.coinChange(q, 1), 1);
    q = {186,419,83,408};
    EXPECT_EQ(s.coinChange(q, 6249), 20);
}