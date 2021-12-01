class Solution {
private:
    int min(int a, int b){
        return (a<b)? a: b;
    }
    int max(int a, int b){
        return (a>b)? a: b;
    }
    int min(int a, int b, int c){
        return min(min(a,b), c);
    }
    int max(int a, int b, int c){
        return max(max(a,b), c);
    }
public:
    int maxProduct(vector<int>& nums) {
        int max_snap = nums[0], min_snap = nums[0], res = nums[0];
        for(int i=1 ; i< nums.size(); i++){
            int cur = nums[i];
            if(cur == 0){
                max_snap = min_snap = 0;
            }else{
                int a = max_snap*cur, b = min_snap*cur;
                max_snap = max(a, b, cur);
                min_snap = min(a, b, cur);
            }
            res = max(res, max_snap);
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {2,3,-2,4};
    EXPECT_EQ(s.maxProduct(q), 6);

    q = {-2,0,-1};
    EXPECT_EQ(s.maxProduct(q), 0);

    q = {-2};
    EXPECT_EQ(s.maxProduct(q), -2);
}