class Solution1 {
public:
    int search(vector<int>& nums, int target) {
        int l=0, r=nums.size()-1;
        while(l<=r){
            int m = (l+r) / 2;
            if(nums[m] == target)
                return m;
            else if(nums[m] < target)
                l = m+1;
            else
                r = m-1;
        }
        return -1;
    }
};

/* Standardized binary search from 101 tutoring */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0, r=nums.size()-1;
        while(l<r){
            int m = (l+r) >> 1;
            if(nums[m] < target)
                l = m+1;
            else
                r = m;
        }
        return (nums[l]==target)? l : -1;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int target, exp;

    q = {-1,0,3,5,9,12};
    target = 9;
    exp = 4;
    EXPECT_EQ(exp, s.search(q, target));

    q = {-1,0,3,5,9,12};
    target = 2;
    exp = -1;
    EXPECT_EQ(exp, s.search(q, target));
}