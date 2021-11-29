class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int cur, n_1 = 2, n_2 = 1;
        for(int i = 3 ; i<=n ; i++){
            cur = n_1 + n_2;
            n_2 = n_1;
            n_1 = cur;

        }
        return cur;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.climbStairs(2), 2);
    EXPECT_EQ(s.climbStairs(3), 3);
    EXPECT_EQ(s.climbStairs(4), 5);
}