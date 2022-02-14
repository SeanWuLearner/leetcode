/*Solution 1: 3 pointers starts from end.*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int wr_idx = m+n-1;
        int i=m-1, j=n-1;
        while(i>=0 || j>=0){
            if(i<0 || (j>=0 && nums1[i] < nums2[j])){
                nums1[wr_idx] = nums2[j];
                wr_idx--; j--;
            }else {
                nums1[wr_idx] =  nums1[i];
                wr_idx--; i--;
            }
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> nums1, nums2, exp;
    int m,n;

    nums1 = {1,2,3,0,0,0};
    m = 3;
    nums2 = {2,5,6};
    n = 3;
    exp = {1,2,2,3,5,6};
    s.merge(nums1, m, nums2, n);
    EXPECT_EQ(nums1, exp);

    nums1 = {1};
    m = 1;
    nums2 = {};
    n = 0;
    exp = {1};
    s.merge(nums1, m, nums2, n);
    EXPECT_EQ(nums1, exp);

    nums1 = {0};
    m = 0;
    nums2 = {1};
    n = 1;
    exp = {1};
    s.merge(nums1, m, nums2, n);
    EXPECT_EQ(nums1, exp);
}