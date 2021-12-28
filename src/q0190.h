/* Solution 1: bitshift */
class Solution_BitShift {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ret = 0;
        int i = 32;
        while(i-->0){
            ret <<= 1;
            if(n & 0x1)
                ret |= 0x1;
            n >>= 1;
        }
        return ret;
    }
};

/*Solution 2: bit swap*/
class Solution_bitswap {
private:
    void swapbit(uint32_t &n, int l, int r){
        uint32_t mask_l = 0x1<<l, mask_r = 0x1<<r;
        bool l_set = n & mask_l, r_set = n & mask_r;
        if(l_set)
            n |= mask_r;
        else
            n &= ~mask_r;

        if(r_set)
            n |= mask_l;
        else
            n &= ~mask_l;
    }
public:
    uint32_t reverseBits(uint32_t n) {
        for(int i=0 ; i<16 ;i++)
            swapbit(n, i, 31-i);
        return n;
    }
};

/*Solution 3: mask and shift, genius */
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = n>>16 | n<<16;
        n = ((0xff00ff00 & n) >> 8) | ((0x00ff00ff & n) << 8);
        n = ((0xf0f0f0f0 & n) >> 4) | ((0x0f0f0f0f & n) << 4);
        n = ((0xcccccccc & n) >> 2) | ((0x33333333 & n) << 2);
        n = ((0xaaaaaaaa & n) >> 1) | ((0x55555555 & n) << 1);
        return n;
    }
};



TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.reverseBits(43261596), 964176192 );
    EXPECT_EQ(s.reverseBits(4294967293), 3221225471 );
}