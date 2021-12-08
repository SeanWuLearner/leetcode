/* Solution : fill zeros in the end */
class Solution_FillZeros {
public:
    void moveZeroes(vector<int>& nums) {
        int w_idx = 0;
        for(int i = 0 ; i < nums.size() ; i++) {
            if(nums[i]==0){
                continue;
            }
            nums[w_idx++] = nums[i];
        }
        for(;w_idx < nums.size() ; w_idx++)
            nums[w_idx] = 0;
    }
};
/* Solution : swap the element to the back of seq which has no zeros */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        auto it{nums.begin()}; // point to the end of no-zeros seq.
        for(auto&& num : nums){
            if(num != 0){
                swap(*it, num);
                it++;
            }
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q, a;

    q = {0,1,0,3,12};
    a = {1,3,12,0,0};
    s.moveZeroes(q);
    EXPECT_EQ(q, a);

    q = {0};
    a = {0};
    s.moveZeroes(q);
    EXPECT_EQ(q, a);
}