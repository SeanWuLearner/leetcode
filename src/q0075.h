class Solution {
public:
    void sortColors(vector<int>& nums) {
        int idx0 = 0, idx2 = nums.size()-1;
        for(int i = 0 ; i<=idx2 ; ){
            if(nums[i] == 0){
                swap(nums[i++], nums[idx0++]);
            }else if(nums[i] == 2)
                swap(nums[i], nums[idx2--]);
            else
                i++;
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q, a;

    q = {2,0,2,1,1,0};
    a = {0,0,1,1,2,2};
    s.sortColors(q);
    EXPECT_EQ(q, a);

    q = {2,0,1};
    a = {0,1,2};
    s.sortColors(q);
    EXPECT_EQ(q, a);

    q = {0};
    a = {0};
    s.sortColors(q);
    EXPECT_EQ(q, a);

    q = {1,2,0};
    a = {0,1,2};
    s.sortColors(q);
    EXPECT_EQ(q, a);
}