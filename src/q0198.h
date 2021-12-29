class Solution {
public:
    int rob(vector<int>& nums) {
        int sum[3] = {0};
        for(int i : nums){
            int new_sum = max(sum[0],sum[1]) + i;
            sum[0] = sum[1];
            sum[1] = sum[2];
            sum[2] = new_sum;
        }
        return max(sum[2],sum[1]);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {1,2,3,1};
    exp = 4;
    EXPECT_EQ(exp, s.rob(q));

    q = {2,7,9,3,1};
    exp = 12;
    EXPECT_EQ(exp, s.rob(q));
}