class MyNaiveSolution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> left_prod(n), right_prod(n), res(n);
        left_prod[0] = nums[0];
        right_prod[n-1] = nums[n-1];
        for(int i=1 ; i<n ; i++)
            left_prod[i] = nums[i] * left_prod[i-1];
        for(int i=n-2 ; i>=0 ; i--)
            right_prod[i] = nums[i] * right_prod[i+1];
        for(int i=0 ; i<n ; i++){
            int l = (i==0)? 1 : left_prod[i-1];
            int r = (i==n-1)? 1 : right_prod[i+1];
            res[i] = l*r;
        }
        return res;
    }
};

/* O(n) solution without extra space*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        res[0] = 1;
        for(int i = 1 ; i < n ; i++)
            res[i] = res[i-1] * nums[i-1];
        int right = 1;
        for(int i = n-2 ; i>=0 ; i--){
            right *= nums[i+1];
            res[i] *= right;
        }
        return res;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;

    q = {1,2,3,4};
    EXPECT_EQ(s.productExceptSelf(q), vector<int>({24,12,8,6}));

    q = {-1,1,0,-3,3};
    EXPECT_EQ(s.productExceptSelf(q), vector<int>({0,0,9,0,0}));
}