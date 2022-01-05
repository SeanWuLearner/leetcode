/*Solution:
    1st pass: start with 0th elem, then the last elem cannot be counted
    2nd pass: start with 1st elem, then the last elem can be counted.
*/
class Solution {
public:
    int helper(vector<int>& nums, int start, int end){
        if(start > end) return 0;
        int n_2 = 0 , n_1 = 0, n = 0;
        for(int i=start; i<end ; i++){
            n = max(n_2 + nums[i], n_1);
            n_2 = n_1; n_1 = n;
        }
        return n;
    }
    int rob(vector<int>& nums) {
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];
        return max(helper(nums, 0, nums.size()-1), helper(nums, 1, nums.size()));
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {2,3,2};
    exp = 3;
    EXPECT_EQ(s.rob(q), exp);

    q= {1,2,3,1};
    exp = 4;
    EXPECT_EQ(s.rob(q), exp);

    q = {1,2,3};
    exp = 3;
    EXPECT_EQ(s.rob(q), exp);
}