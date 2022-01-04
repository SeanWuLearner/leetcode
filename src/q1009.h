class Solution {
public:
    int bitwiseComplement(int n) {
        if(n==0) return 1;
        int capbit = 0x1;
        while(capbit-1 < n){
            capbit <<= 1;
        }
        return capbit - 1 -n;
    }
};

TEST(Solution, Test1){
    Solution s;
    int n, exp;

    n=5, exp=2;
    EXPECT_EQ(s.bitwiseComplement(n), exp);

    n=7, exp=0;
    EXPECT_EQ(s.bitwiseComplement(n), exp);

    n=10, exp=5;
    EXPECT_EQ(s.bitwiseComplement(n), exp);
}