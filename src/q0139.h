#include <unordered_set>
/*Solution 1: recusion with memo */
class Solution_RecursiveMemo {
private:
    bool helper(string& s, int idx, unordered_set<string>& dict, vector<bool>& failed){
        if(idx == s.length()) return true;
        if(failed[idx]==true) return false;
        for(int i = idx ; i<s.length() ; i++){
            auto it = dict.find(s.substr(idx, i-idx+1));
            if(it==dict.end())
                continue;
            if(helper(s, i+1, dict, failed)==true)
                return true;
        }
        failed[idx] = true;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> failed(s.length());
        return helper(s, 0, dict, failed);
    }
};

/*Solution 2: bottom-up dp, do it backward
    dp[i] indicates whether s[0:i] can be breaked with wordDict

    dp[0] = true, s[0:0], i.e. empty string can be breaked with wordDict.
    dp[i] = s[j:i] match a word && dp[j]==true;
    dp[n] = the result of the question
*/
class Solution{
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.length()+1);
        dp[0] = true;
        for(int i=1; i<=s.length(); i++){
            for(int j=0 ; j<i ; j++){
                if(dp[j] && dict.find(s.substr(j, i-j)) != dict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.length()];
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    vector<string> dict;
    bool exp;

    q = "leetcode";
    dict = {"leet","code"};
    exp = true;
    EXPECT_EQ(exp, s.wordBreak(q, dict));

    q = "applepenapple";
    dict = {"apple","pen"};
    exp = true;
    EXPECT_EQ(exp, s.wordBreak(q, dict));

    q = "catsandog";
    dict = {"cats","dog","sand","and","cat"};
    exp = false;
    EXPECT_EQ(exp, s.wordBreak(q, dict));
}