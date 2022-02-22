/* Solution 1: left to right */
class Solution1 {
public:
    int titleToNumber(string columnTitle) {
        int res = 0;
        for(auto &&c : columnTitle){
            res *= 26;
            res += c-'A'+1;
        }
        return res;
    }
};

/* Solution 2: right to left */
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int res = 0;
        int base = 1;
        for(auto it=columnTitle.rbegin(); it!=columnTitle.rend() ; it++){
            auto c = *it;
            res += (c-'A'+1) * base;
            base *= 26;
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.titleToNumber("A"), 1);
    EXPECT_EQ(s.titleToNumber("AB"), 28);
    EXPECT_EQ(s.titleToNumber("ZY"), 701);
}