/* top-down DP */
class Solution_topdown {
public:
    bool canGetSum(vector<int>& nums, int idx, int sum, unordered_map<long, bool>& dp){
        if(idx == nums.size() || sum < 0) return false;
        if(sum == 0) return true;
        long dp_idx = ((long)idx<<32) | sum;
        if(dp.find(dp_idx)!=dp.end())
            return dp[dp_idx];
        dp[dp_idx] = canGetSum(nums, idx+1, sum, dp) || canGetSum(nums, idx+1, sum-nums[idx], dp);
        return dp[dp_idx];
    }
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int i : nums)
            sum+=i;
        if(sum%2 != 0)
            return false;
        unordered_map<long, bool> dp;
        int half = sum / 2;
        return canGetSum(nums, 0, half, dp);
    }
};

/* bottom-up DP */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int i : nums)
            sum+=i;
        if(sum%2 != 0)
            return false;
        int n = sum / 2;
        vector<bool> dp(n+1);
        dp[0] = true;
        for(int i : nums){
            for(int j=n ; j >=i ; j--){
                if(dp[j]==true) continue;
                dp[j] = dp[j-i];
            }
        }
        return dp[n];
    }
};

TEST(Solution, test1) {
    Solution s;
    vector<int> q;

    q = {1,5,11,5};
    EXPECT_EQ(s.canPartition(q),true);

    q = {1,2,3,5};
    EXPECT_EQ(s.canPartition(q),false);

    q = {1,2,5};
    EXPECT_EQ(s.canPartition(q),false);
}