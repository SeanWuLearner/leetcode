#include <unordered_set>

/*Solution 1: building dict */
#define NIL (-1)
class Solution_recursiveDict {
private:
    unordered_set<string> dict;
    vector<int> dp;
    void buildDict(){
        for(int i=1 ; i<=26 ; i++)
            dict.insert(to_string(i));
    }
    int helper(string& s, int idx){
        if(idx==s.length()) return 1;
        if(dp[idx]!= NIL) return dp[idx];

        int num1 = (dict.find(s.substr(idx, 1))==dict.end())? 0 : helper(s, idx+1);
        int num2 = 0;
        if(s.length() - idx >= 2)
            num2 = (dict.find(s.substr(idx, 2))==dict.end())? 0 : helper(s, idx+2);
        dp[idx] = num1 + num2;
        return dp[idx];
    }
public:
    int numDecodings(string s) {
        buildDict();
        dp = vector<int>(s.length(), NIL);
        return helper(s, 0);
    }
};
/* Solution 2: same recusive dp, NOT building dict */
class Solution_recursiveNoDict {
private:
    vector<int> dp;
    int helper(string& s, int idx){
        if(idx==s.length()) return 1;
        if(dp[idx]!= NIL) return dp[idx];

        // one letter case handling
        if(s[idx]=='0') return dp[idx] = 0;
        int res = helper(s, idx+1);

        // two letters case handling
        if(idx < s.length()-1 &&
          (s[idx]=='1' || (s[idx]=='2' && s[idx+1] <= '6')) )
            res += helper(s, idx+2);

        dp[idx] = res;
        return dp[idx];
    }
public:
    int numDecodings(string s) {
        dp = vector<int>(s.length(), NIL);
        return helper(s, 0);
    }
};

/* Solution 3: bottom-up dp, constant space
    we only need to memorize dp[i+1] and dp[i+2]
*/
class Solution{
public:
    int numDecodings(string s) {
        int pre = 1, prepre;
        int cur = 0;
        for(int i = s.length()-1 ; i>=0 ; i--){
            cur = (s[i]== '0')? 0 : pre;
            if(i < s.length() - 1 &&
                (s[i]=='1' || (s[i]=='2' && s[i+1] <= '6')))
            {
                cur += prepre;
            }

            prepre = pre;
            pre = cur;
        }
        return cur;
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    int exp;

    q = "12";
    exp = 2;
    EXPECT_EQ(s.numDecodings(q), exp);

    q = "226";
    exp = 3;
    EXPECT_EQ(s.numDecodings(q), exp);
}