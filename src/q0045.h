/* DP: O(n^2) runtime.... */
class Solution_dp {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        for(int i=n-2 ; i>=0 ;i--){
            int min_step = INT_MAX-1;
            for(int j = i+1 ; j <= i+nums[i] && j < n ; j++){
                min_step = min(min_step, dp[j]);
            }
            dp[i] = min_step + 1;
        }
        return dp[0];
    }
};

/* solution: greedy */
class Solution {
public:
    int jump(vector<int>& nums) {
        int jumps = 0;
        int farest = 0, jumpEnd = 0;
        for(int i=0 ; i<nums.size()-1 ; i++){
            farest = max(farest, i + nums[i]);
            if(i==jumpEnd){
                jumps++;
                jumpEnd = farest;
            }
        }
        return jumps;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {2,3,1,1,4};
    EXPECT_EQ(s.jump(q), 2);

    q = {2,3,0,1,4};
    EXPECT_EQ(s.jump(q), 2);
}