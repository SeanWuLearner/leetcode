/*
case1: l<m<r , min = l
case2: m>l>r , min is in [min+1 : r]
case3: m<r<l , min is in [l, m]
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            int m = (l+r) / 2;
            if(nums[m] >= nums[l])
                if(nums[l] > nums[r])
                    l = m+1;
                else
                    r = l; //found that l is the min.
            else
                r = m;
        }
        return nums[l];
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {3,4,5,1,2};
    exp = 1;
    EXPECT_EQ(exp, s.findMin(q));

    q = {4,5,6,7,0,1,2};
    exp = 0;
    EXPECT_EQ(exp, s.findMin(q));

    q = {11,13,15,17};
    exp = 11;
    EXPECT_EQ(exp, s.findMin(q));
}