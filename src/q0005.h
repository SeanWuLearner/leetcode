class Solution {
private:
    int getMaxPalinedromeLen(string &s, int l, int r){
        int max_len = 0;
        while( l >=0 && r < s.length() && s[l] == s[r]){
            max_len = max(max_len, r-l+1);
            l--; r++;
        }
        return max_len;
    }
public:
    string longestPalindrome(string s) {
        int max_len = 0, max_idx = 0;
        for(int i = 0 ; i< s.length() ; i++){
            int len = getMaxPalinedromeLen(s, i, i);
            if(len > max_len){
                max_len = len;
                max_idx = i;
            }
            len = getMaxPalinedromeLen(s, i, i+1);
            if(len > max_len){
                max_len = len;
                max_idx = i;
            }
        }
        if(max_len % 2 == 0)
            return s.substr(max_idx - (max_len/2 - 1), max_len);
        else
            return s.substr(max_idx - (max_len/2), max_len);
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.longestPalindrome("babad"), "bab");
    EXPECT_EQ(s.longestPalindrome("cbbd"), "bb");
    EXPECT_EQ(s.longestPalindrome("a"), "a");
    EXPECT_EQ(s.longestPalindrome("ac"), "a");
}