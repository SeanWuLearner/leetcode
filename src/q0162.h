class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            // printf("l,r = %d,%d\n", l, r);
            int mid1 = (l+r) / 2;
            int mid2 = mid1+1;
            if(nums[mid1] > nums[mid2])
                r = mid1;
            else
                l = mid2;
        }
        return l;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {1,2,3,1};
    EXPECT_EQ(s.findPeakElement(q), 2);

    q= {1,2,1,3,5,6,4};
    EXPECT_EQ(s.findPeakElement(q)==1 || s.findPeakElement(q)==5, true);

    q= {2,1};
    EXPECT_EQ(s.findPeakElement(q) , 0);

    q= {1,2};
    EXPECT_EQ(s.findPeakElement(q) , 1);
}
