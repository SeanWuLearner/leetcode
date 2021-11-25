
class MySolution {
public:
    int reverse(int x) {
        int ans = 0;
        const int mul_hi_bound = INT_MAX / 10;
        const int mul_lo_bound = INT_MIN / 10;
        while(x != 0){
            if(ans > mul_hi_bound) return 0;
            if(ans < mul_lo_bound) return 0;
            ans *= 10;

            int num = x % 10;
            if(ans > 0 && ans > INT_MAX - num) return 0;
            if(ans < 0 && ans < INT_MIN - num) return 0;
            ans += num;
            x /= 10;
        }
        return ans;
    }
};

/* check boundary in one liner, not accecpted because of runtime error (overflow). */
class Solution {
public:
    int reverse(int x) {
        int ans = 0, prev_ans = 0;
        while(x != 0){
            ans = ans * 10 + (x % 10);
            if((ans - (x % 10)) / 10 != prev_ans)
                return 0;
            prev_ans = ans;
            x /= 10;
        }
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.reverse(123), 321);
    EXPECT_EQ(s.reverse(-123), -321);
    EXPECT_EQ(s.reverse(120), 21);
    EXPECT_EQ(s.reverse(0), 0);
}