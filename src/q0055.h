#include "vector_util.h"

/* Solution1: time limit exceeded */
class Solution_NG {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> dp(nums.size());
        dp[0] = true;
        for(int i = 0 ; i < nums.size()-1 ; i++){
            if(dp[i]==false)
                continue;
            for(int j = 1 ; j <= nums[i] && i+j < nums.size() ; j++)
                dp[i+j] = true;
        }
        return dp[nums.size()-1];
    }
};
/* Solution2: top down dp,
    dp mem is canReachEnd[i]
*/
class Solution_TopDown1 {
private:
    int canReach(vector<int>& nums, vector<int>& dp, int idx){
        if(idx >= nums.size() - 1)
            return 1;
        if(dp[idx] != 0)
            return dp[idx];
        for(int i = idx+1 ; i <= idx + nums[idx] ; i++){
            if(canReach(nums, dp, i)==1){
                dp[idx] = 1;
                return dp[idx];
            }
        }
        dp[idx] = -1;
        return dp[idx];
    }
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[n-1] = 1;
        return (canReach(nums, dp, 0) == 1)? true:false;
    }
};

/* Solution3: top down dp, further tidy up the code */
class Solution_TopDown2 {
private:
    bool canReach(vector<int>& nums, vector<int>& dp, int idx){
        if(dp[idx] != 0)
            return dp[idx]==1;
        int n = nums.size();
        int end_idx = min(n-1, idx + nums[idx]);
        for(int i = idx+1 ; i <= end_idx ; i++){
            if(canReach(nums, dp, i)){
                dp[idx] = 1;
                return true;
            }
        }
        dp[idx] = -1;
        return false;
    }
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[n-1] = 1;
        return canReach(nums, dp, 0);
    }
};

/* Solution4 : Bottom-Up DP */
class Solution_BotttomUp {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n);
        dp[n-1] = true;
        for(int i = n-2 ; i >= 0 ; i--){
            int last = min(n-1 , i + nums[i]);
            for(int j = last ; j>=i+1 ; j--){
                if(dp[j]){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};

/* Solution 5: Greedy
    only keep leftMostGoodIdx instead of a whole dp
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int lastOkIdx = n-1;
        for(int i = n-2 ; i >= 0 ; i--){
            if(i+nums[i] >= lastOkIdx)
                lastOkIdx = i;
        }
        return lastOkIdx == 0;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    bool exp;

    q = {2,3,1,1,4};
    exp = true;
    EXPECT_EQ(s.canJump(q), exp);

    // q = {3,2,1,0,4};
    // exp = false;
    // EXPECT_EQ(s.canJump(q), exp);
}