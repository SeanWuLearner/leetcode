class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN, acc = INT_MIN;
        for(auto num : nums){
            acc = (acc<0)? num : acc+num;
            ans = max(ans, acc);
        }
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {-2,1,-3,4,-1,2,1,-5,4};
    EXPECT_EQ(6, s.maxSubArray(q));

    q = {1};
    EXPECT_EQ(1, s.maxSubArray(q));

    q = {5,4,-1,7,8};
    EXPECT_EQ(23, s.maxSubArray(q));
}