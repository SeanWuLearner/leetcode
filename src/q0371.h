
class Solution {
public:
    int getSum(int a, int b) {
        int sum;
        while(b!=0)
        {
            int c = a^b;
            b = (unsigned int)(a&b) << 1;
            a = c;
        }
        return a;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.getSum(1,2), 3);
    EXPECT_EQ(s.getSum(2,3), 5);
    EXPECT_EQ(s.getSum(-4,3), -1);
    EXPECT_EQ(s.getSum(-4,-3), -7);
    EXPECT_EQ(s.getSum(-1,1), 0);
    EXPECT_EQ(s.getSum(1,-1), 0);
}