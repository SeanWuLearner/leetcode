/* Solution : two pointer, wr_idx and rd_idx */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int w_i = 1, dup = 1;
        for(int i=1 ; i<nums.size() ; i++){
            if(nums[i] == nums[i-1]){
                dup++;
            }else{
                dup=1;
            }
            if(dup <= 2)
                nums[w_i++] = nums[i];
        }
        return w_i;
    }
};

bool testPartVec(vector<int>& tar, vector<int>& patt, int num){
    for(int i=0; i<num ; i++)
        if(tar[i]!=patt[i])
            return false;
    return true;
}

TEST(Solution, test1){
    Solution s;
    vector<int> q, a;
    int exp;

    q = {1,1,1,2,2,3};
    a = {1,1,2,2,3};
    exp = 5;
    EXPECT_EQ(exp, s.removeDuplicates(q));
    EXPECT_EQ(true, testPartVec(a, q, exp));

    q = {0,0,1,1,1,1,2,3,3};
    a = {0,0,1,1,2,3,3};
    exp = 7;
    EXPECT_EQ(exp, s.removeDuplicates(q));
    EXPECT_EQ(true, testPartVec(a, q, exp));
}