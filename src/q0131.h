#include "vector_util.h"

/* Solution 1: my backtracking */
class Solution_backtracking1 {
private:
    vector<vector<string>> res;
    bool isPalindrome(string &s, int start, int end){
        int len = end - start;
        if(len==1) return true;
        int mid = (start+end) / 2;
        int l = mid - 1, r = (len%2==0)? mid : mid+1;
        while(r-l+1 <= len){
            if(s[l]!=s[r])
                return false;
            l--; r++;
        }
        return true;
    }
    void backtracking(string &s, int start, vector<string>& cur){
        if(start == s.length()){
            res.push_back(cur);
            return;
        }

        for(int i = start+1 ; i<=s.length() ; i++){
            if(isPalindrome(s, start, i)){
                cur.push_back(s.substr(start, i-start));
                backtracking(s, i, cur);
                cur.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> cur;
        backtracking(s, 0, cur);
        return res;
    }
};
/* Solution 2: backtracking with dp
dp[i,j] = indicate whether s[i:j+1] is palindrome.
 */
class Solution {
private:
    vector<vector<string>> res;
    vector<vector<bool>> dp;
    bool isPalindrome(string &s, int left, int right){
        if(s[left]!= s[right] || (left+1 < right && dp[left+1][right-1]==false)){
            dp[left][right] = false;
            return false;
        }
        dp[left][right] = true;
        return true;
    }
    void backtracking(string &s, int start, vector<string>& cur){
        if(start == s.length()){
            res.push_back(cur);
            return;
        }

        for(int end = start ; end < s.length() ; end++){
            if(isPalindrome(s, start, end)){
                cur.push_back(s.substr(start, end-start+1));
                backtracking(s, end+1, cur);
                cur.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> cur;
        int n = s.length();
        dp = vector<vector<bool>>(n, vector<bool>(n));
        backtracking(s, 0, cur);
        return res;
    }
};



#include "vector_util.h"
TEST(Solution, Test1){
    Solution s;
    string q;
    vector<vector<string>> exp;

    q = "aab";
    exp = {{"a","a","b"},{"aa","b"}};
    EXPECT_EQ(sortVec(s.partition(q)), sortVec(exp));
}

TEST(Solution, Test2){
    Solution s;
    string q;
    vector<vector<string>> exp;

    q = "a";
    exp = {{"a"}};
    EXPECT_EQ(sortVec(s.partition(q)), sortVec(exp));
}

TEST(Solution, Test3){
    Solution s;
    string q;
    vector<vector<string>> exp;

    q = "aaba";
    exp = {
        {"a","a","b","a"},
        {"aa","b","a"},
        {"a","aba"}
    };
    EXPECT_EQ(sortVec(s.partition(q)), sortVec(exp));
}