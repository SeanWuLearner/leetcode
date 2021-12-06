
/* Solution: Expand Around Possible Centers */
class Solution_expand {
private:
    int countPalindrome(string& s, int l, int r){
        int cnt = 0;
        while(l>=0 && r<s.length() && s[l]==s[r]){
            cnt++;
            l--; r++;
        }
        return cnt;
    }
public:
    int countSubstrings(string s) {
        int n = s.length();
        int cnt = 0;

        for(int i = 0 ; i < n ; i++){
            //odd
            cnt += countPalindrome(s, i, i);
            //even
            cnt += countPalindrome(s, i, i+1);
        }
        return cnt;
    }
};

/* dp solution:

    dp[l][r] = true, if s.substr(l, r-l+1) is palindrome

    let's say:   abc'dcb'xy from old to old, dp[l][r] = dp[l+1][r-1] == true && s[l] == s[r]
                 ab'cddc'xy from even to even, dp[l][r] = dp[l+1][r-1] == true && s[l] == s[r]
                 'aaa' from even to odd dp[l][r] = dp[l][r-1]==true && s[l] == s[r]
                 'aaaa' from odd to even dp[l][r] = dp[l][r-1]==true && s[l] == s[r]
                 'aaabaaa'
*/
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n));
        
        /* base case : 1 letter */
        int cnt = n;
        for(int i = 0 ; i < n ; i++)
            dp[i][i] = true;
        /* base case : 2 letters */
        for(int i = 0 ; i < n-1 ; i++){
            if(s[i] == s[i+1]){
                dp[i][i+1] = true;
                cnt++;
            }
        }
        
        for(int len = 3 ; len <=n ; len++){
            for(int l = 0 ; l <= n-len ; l++){
                int r = l + len - 1;
                if(dp[l+1][r-1] && s[l]==s[r]){
                    dp[l][r] = true;
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.countSubstrings("abc"), 3);
    EXPECT_EQ(s.countSubstrings("aaa"), 6);
}