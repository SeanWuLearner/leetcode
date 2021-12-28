/* Solution 1: shift and count LSB */
class Solution1 {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n!=0){
            if(n&1)
                cnt++;
            n>>=1;
        }
        return cnt;
    }
};

/* Solution 2: n-1 trick */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n!=0){
            cnt++;
            n &= n-1;
        }
        return cnt;
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(3, s.hammingWeight(0xb));
    EXPECT_EQ(1, s.hammingWeight(0x80));
    EXPECT_EQ(31, s.hammingWeight(0xfffffffd));
}