/* Solution 1: brute force */
class Solution_BruteForce {
private:
    int helper(vector<int>& nums, int idx, int target){
        if(idx == nums.size()){
            return (target==0)? 1 : 0;
        }
        return helper(nums, idx+1, target-nums[idx]) +
               helper(nums, idx+1, target+nums[idx]);
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return helper(nums, 0, target);
    }
};

/* Solution 2: brute force + memo */
#include <unordered_map>
struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    // return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
    return hash<size_t>()(((size_t)x.first)^(((size_t)x.second)<<32));
  }
};
class Solution_BruteForceDP {
private:
    unordered_map<pair<int,int>,int,HASH> memo;
    int helper(vector<int>& nums, int idx, int target){
        if(idx == nums.size()){
            return (target==0)? 1 : 0;
        }
        auto mem_idx = make_pair(idx, target);
        auto it = memo.find(mem_idx);
        if(it != memo.end())
            return it->second;

        memo[mem_idx] = helper(nums, idx+1, target-nums[idx]) +
               helper(nums, idx+1, target+nums[idx]);
        return memo[mem_idx];
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return helper(nums, 0, target);
    }
};

/* Solution 3: iterative DP (size sum of nums...) */
class Solution_dp{
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<int, int> sum_cnt;
        sum_cnt[nums[0]] = 1;
        sum_cnt[-nums[0]] += 1;
        for(int i=1 ; i<nums.size() ; i++){
            unordered_map<int, int> next;
            for(auto&& it : sum_cnt){
                next[it.first + nums[i]] += it.second;
                next[it.first - nums[i]] += it.second;
            }
            sum_cnt = next;
        }
        return sum_cnt[target];
    }
};

/* Solution 4: subset sum method
    positive subset sum noted as sum(P)
    negtive subset sum noted as sum(N)

                  sum(P) - sum(N) = target
sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
                       2 * sum(P) = target + sum(nums)
    i.e. to find the possible subset sums to (target + sum(nums)) / 2

<DP of subset sum>
    For each num, we have to either include it or not include it.
    dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]] //2D representation, i as idx to nums, j as targetSum.

    In 1D dp representation.
    dp[j] = dp[j] + dp[j-nums[i]]
*/
class Solution{
private:
    int getNumSubsetSum(vector<int>& nums, int target){
        vector<int> dp(target+1);
        dp[0] = 1;
        for(auto &n : nums){
            for(int i=target; i>=n ; i-- ){
                dp[i] += dp[i-n];
            }
        }
        return dp[target];
    }
public:
    int findTargetSumWays(vector<int>& nums, int target){
        int sum=0;
        for(auto& i: nums) sum += i;
        if((sum+target) & 1 || (sum+target) < 0)
            return 0;
        return getNumSubsetSum(nums, (sum+target)/2);
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int target, exp;

    q = {1,1,1,1,1};
    target = 3;
    exp = 5;
    EXPECT_EQ(s.findTargetSumWays(q, target), exp);
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    int target, exp;

    q = {0,0,0,0,0,0,0,0,1};
    target = 1;
    exp = 256;
    EXPECT_EQ(s.findTargetSumWays(q, target), exp);
}

TEST(Solution, Test3){
    Solution s;
    vector<int> q;
    int target, exp;

    q = {100};
    target = -200;
    exp = 0;
    EXPECT_EQ(s.findTargetSumWays(q, target), exp);
}