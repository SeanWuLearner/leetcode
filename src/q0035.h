class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while(l<r){
            int mid = (l+r) / 2;
            if(nums[mid] == target)
                return mid;
            if(nums[mid] < target)
                l = mid+1;
            else
                r = mid;
        }
        return l;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {1,3,5,6};
    EXPECT_EQ(s.searchInsert(q, 5), 2);
    EXPECT_EQ(s.searchInsert(q, 2), 1);
    EXPECT_EQ(s.searchInsert(q, 7), 4);
    EXPECT_EQ(s.searchInsert(q, 0), 0);
    q  ={1};
    EXPECT_EQ(s.searchInsert(q, 0), 0);
}