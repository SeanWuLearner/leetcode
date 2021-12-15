#include "vector_util.h"
/* Solution1: recursion with top-down DP

{matching algo}
    While without '*', forward both s and p by 1. (first char must match)
    While with '*', it's determined as matched while either of below cases hold true.
        1. consume '*' and continue the following matching. Few possible cases here
            a) first char match: forward s by 1
            b) first char NOT match : must drop 2 chars from pattern.

        2. NOT consume 'a*' and continue the following matching.

{DP}
    While i, j is the index to s and p separately.
    dp[i, j] = -1 , not yet evaluated before.
                0 , s[i:] NOT matched to p[j:]
                1 , s[i:] does matched to p[j:]
*/
class Solution_TopDown1 {
private:
    vector<vector<int>> dp;

    bool isMatch(string& s, int i, string& p, int j){
        if(j==p.length()) return (i==s.length());
        if(dp[i][j] != -1) return dp[i][j];

        //need to deal with s='' p='a*'
        bool first_match = (i < s.length()) && (s[i]==p[j] || p[j]== '.');

        if(j+1 < p.length() && p[j+1] == '*'){
            dp[i][j] = (first_match && isMatch(s, i+1, p, j)) || isMatch(s, i, p, j+2);
        }else{
            dp[i][j] = first_match && isMatch(s, i+1, p, j+1);
        }
        return dp[i][j];
    }
public:
    bool isMatch(string s, string p) {
        dp = vector<vector<int>>(s.length()+1, vector<int>(p.length()+1, -1));
        bool res = isMatch(s, 0, p, 0);
        return res;
    }
};

/*Solution 2: bottom-up DP
    Same dp notation as Solution 1
    dp[s.length][p.length] = true,  empty strings match to each other.
    dp[0][0] will be the result;
*/
class Solution_BottomUp{
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.length()+1, vector<bool>(p.length()+1));
        dp[s.length()][p.length()] = true;
        for(int i=s.length() ; i>=0 ; i--){
            for(int j=p.length()-1 ; j>=0 ; j--){
                bool first_match = i<s.length() && (s[i]==p[j] || p[j]=='.');
                if(j+1 < p.length() && p[j+1] == '*'){
                    dp[i][j] = (first_match && dp[i+1][j]) || dp[i][j+2];
                }else{
                    dp[i][j] = first_match && dp[i+1][j+1];
                }
            }
        }
        return dp[0][0];
    }
};
/* Solution 3: Another bottom-up DP
    dp[0][0] = true, empty strings match each other
    dp[m][n] will be the result.

    dp[i][j] = whether s[0:i] can match p[0:j]. Plz note s[0:1] = s[1] , so dp[1][1] is to match the
    0th char of both s and p. (index offset by 1)

{dp init}
    dp[i>=1][0] = false, empty pattern cannot match to non-empty text.
    dp[0][j], while matching to empty text, ONLY 'n*' can match to empty text.
        so, dp[0][j] = (p[j-1]=='*') && dp[0][j-2];

{while matching}
    * 2 for loops from 0 to s.length and p.length
    * if p[j-1] != '*', dp[i][j] = is_match(s[i-1], j[-1]) && dp[i-1][j-1];
      if p[j-1] == '*', dp[i][j] = or logic of these two logic
        case1. 'x*' account for nothing, dp[i][j-2]
            ex. s="123" p="1234*", dp[3][5] = dp[3][5-2]
        case2. 'x*' account for 1 letter, dp[i][j-1]
        case3. 'x*' account for multiple letter, dp[i-1][j] && s[i-1]==p[j-1]
            ex. s="123444" p="1234*",dp[6][5] = dp[5][5] = dp[4][5] = dp[3][5]
            ex. s="missi", p="mis*", dp[5][4] = (s[4] == p[3]) && dp[i-1][j]
*/
class Solution{
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.length()+1, vector<bool>(p.length()+1));
        //init dp
        dp[0][0] = true;
        for(int j=1 ; j<p.length() ; j++){
            dp[0][j+1] = p[j]=='*' && dp[0][j-1];
        }
        //matching
        for(int i=0 ; i<s.length() ; i++){  //i, j as index for string, idx for dp needs to +1.
            for(int j=0 ; j<p.length() ; j++){
                bool first_match = (s[i]==p[j] || p[j]=='.');
                if(p[j] == '*'){
                    bool prev_match = (s[i]==p[j-1] || p[j-1]=='.');
                    dp[i+1][j+1] = (prev_match && dp[i][j+1]) || dp[i+1][j-1] || dp[i+1][j];
                }else{
                    dp[i+1][j+1] = first_match && dp[i][j];
                }
            }
        }
        // printVec(dp);
        return dp[s.length()][p.length()];
    }
};


TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.isMatch("aa", "a"), false);
    EXPECT_EQ(s.isMatch("aa", "a*"), true);
    EXPECT_EQ(s.isMatch("ab", ".*"), true);
    EXPECT_EQ(s.isMatch("aab", "c*a*b"), true);
    EXPECT_EQ(s.isMatch("mississippi", "mis*is*p*."), false);
    EXPECT_EQ(s.isMatch("mississippi", "mis*is*ip*."), true);
    EXPECT_EQ(s.isMatch("ab", ".*c"), false);
    EXPECT_EQ(s.isMatch("aaa", "ab*ac*a"), true);
    EXPECT_EQ(s.isMatch("aaa", "ab*a*c*a"), true);
    EXPECT_EQ(s.isMatch("aaa", ".*"), true);

}