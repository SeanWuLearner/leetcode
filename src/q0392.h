class Solution {
public:
    bool isSubsequence(string s, string t) {
        int idx = 0;
        for(char c: t){
            if(c==s[idx]){
                idx++;
                if(idx == s.length())
                    return true;
            }
        }
        return idx==s.length();
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.isSubsequence("abc", "ahbgdc"), true);
    EXPECT_EQ(s.isSubsequence("axc", "ahbgdc"), false);
}