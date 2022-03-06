
/* Solution 1: bottom-up DP */
class Solution1 {
public:
    int get(unordered_map<int, int>& dict, int key, int def=0){
        if(dict.find(key)==dict.end())
            return def;
        else
            return dict[key];
    }
    void shift(int dp[3]){
        dp[2] = dp[1];
        dp[1] = dp[0];
    }
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> dict;
        int max_val = INT_MIN;
        for(int i : nums){
            dict[i] = get(dict, i) + i;
            max_val = max(max_val, i);
        }

        int dp[3] = {0};
        dp[1] = get(dict, 1);
        for(int i=2 ; i<= max_val ; i++){
            int gain = get(dict, i);
            dp[0] = max(gain + dp[2], dp[1]);
            shift(dp);
        }
        return dp[1];
    }
};

/* Solution 2: top-down DP */
class Solution{
private:
    unordered_map<int,int> dict;
    vector<int> dp;
public:
    int get(unordered_map<int, int>& dict, int key, int def=0){
        if(dict.find(key)==dict.end())
            return def;
        else
            return dict[key];
    }
    int maxEarn(int num){
        if(num <= 0) return 0;
        if(num == 1) return get(dict, num);
        if(dp[num]!= -1) return dp[num];

        int gain = get(dict, num);
        dp[num] = max(gain + maxEarn(num-2), maxEarn(num-1));
        return dp[num];
    }
    int deleteAndEarn(vector<int>& nums) {
        int max_val = INT_MIN;
        for(int i : nums){
            dict[i] = get(dict, i) + i;
            max_val = max(max_val, i);
        }
        dp = vector<int>(max_val+1, -1);
        return maxEarn(max_val);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {3,4,2};
    exp = 6;
    EXPECT_EQ(exp, s.deleteAndEarn(q));
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    int exp;

    q = {2,2,3,3,3,4};
    exp = 9;
    EXPECT_EQ(exp, s.deleteAndEarn(q));
}