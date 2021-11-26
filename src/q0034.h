/* my solution, must use the prev of upper_bound() */
class MySolution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size()==0)
            return {-1,-1};
        int l = findleft(nums, target);
        if(nums[l]!=target)
            return {-1,-1};
        int r = findright(nums, target);
        // printf("l=%d, r=%d\n", l, r);
        return {l, (nums[r]==target)? r : r-1};
    }

    int findleft(vector<int>& nums, int target){
        int l = 0, r = nums.size()-1;
        while(l<r){
            int mid = (l+r) / 2;
            if(nums[mid] >= target)
                r = mid;
            else
                l = mid+1;
        }
        return l;
    }
    int findright(vector<int>& nums, int target){
        int l = 0, r = nums.size()-1;
        while(l<r){
            int mid = (l+r) / 2;
            if(nums[mid] <= target)
                l = mid+1;
            else
                r = mid;
        }
        return l;
    }
};

/* More readable solution */
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {findleft(nums, target), findright(nums, target)};
    }

    int findleft(vector<int>& nums, int target){
        int idx = -1;
        int l = 0, r = nums.size()-1;
        while(l<=r){
            int mid = (l+r) / 2;
            if(nums[mid] >= target)
                r = mid-1;
            else
                l = mid+1;
            if(nums[mid]==target)
                idx = mid;
        }
        return idx;
    }
    int findright(vector<int>& nums, int target){
        int idx = -1;
        int l = 0, r = nums.size()-1;
        while(l<=r){
            int mid = (l+r) / 2;
            if(nums[mid] <= target)
                l = mid+1;
            else
                r = mid-1;
            if(nums[mid]==target)
                idx = mid;
        }
        return idx;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {5,7,7,8,8,10};
    EXPECT_EQ(s.searchRange(q, 8), vector<int>({3,4}));

    q = {5,7,7,8,8,10};
    EXPECT_EQ(s.searchRange(q, 6), vector<int>({-1,-1}));

    q = {};
    EXPECT_EQ(s.searchRange(q, 0), vector<int>({-1,-1}));

    q = {0,-1};
    EXPECT_EQ(s.searchRange(q, 0), vector<int>({0,0}));

    q = {2,2};
    EXPECT_EQ(s.searchRange(q, 2), vector<int>({0,1}));

}