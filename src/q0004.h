
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& a = (nums1.size() < nums2.size())? nums1 : nums2;  // a: shorter
        vector<int>& b = (nums1.size() < nums2.size())? nums2 : nums1;  // b: longer
        int m = a.size(), n = b.size();
        int imin = 0, imax = m;
        int i, j, half_len = (m+n+1) / 2;

        while(imin <= imax){
            i = (imin + imax) / 2;
            j = half_len - i;

            if(m==0 || n==0) break;

            if((i==0 || j==n || b[j]>=a[i-1]) && (i==m || j==0 || a[i]>=b[j-1])) // hit
                break;
            else if(a[i] < b[j-1]) //increase i
                imin = i+1;
            else if(b[j] < a[i-1]) //decrease i
                imax = i;
        }
        double a_i = (i==m)? DBL_MAX : a[i];
        double b_j = (j==n)? DBL_MAX : b[j];
        double a_i_1 = (i==0)? -DBL_MAX : a[i-1];
        double b_j_1 = (j==0)? -DBL_MAX : b[j-1];
        if((m+n) % 2 == 0)
            return (max(a_i_1, b_j_1) + min(a_i, b_j)) / 2;
        else
            return max(a_i_1, b_j_1);
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> nums1, nums2;

    nums1 = {1,3};
    nums2 = {2};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), 2);

    nums1 = {1,2};
    nums2 = {3,4};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), 2.5);

    nums1 = {0,0};
    nums2 = {0,0};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), 0);

    nums1 = {};
    nums2 = {1};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), 1.0);

    nums1 = {2};
    nums2 = {};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), 2.0);

    nums1 = {3};
    nums2 = {-2, -1};
    EXPECT_EQ(s.findMedianSortedArrays(nums1, nums2), -1.0);
}