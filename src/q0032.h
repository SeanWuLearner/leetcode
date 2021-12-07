
/* My poor and naive solution:
Exercises:
    ( () (()) )

    ( (()) )  // if prev close_idx is right next to cur close_idx, we can sum the len together.

    () () (())  //need a stack of close_idx, used to see if open_idx was next to it. if yes, we can sum the len together.
*/
#include <stack>
class Solution_poor {
public:
    int longestValidParentheses(string s) {
        stack<int> opens; // stack of open_idx
        stack<vector<int>> closes;  //close_idx , close_len
        int max_len = 0;
        for(int i=0 ; i<s.length() ; i++){
            if(s[i]== '('){
                opens.push(i);
            }else{
                if(opens.empty())
                    continue;

                int close_len = 2;
                if(!closes.empty() && closes.top()[0] == i-1){
                    close_len += closes.top()[1];
                    closes.pop();
                }
                if(!closes.empty() && opens.top() == closes.top()[0] + 1){
                    close_len += closes.top()[1];
                    closes.pop();
                }
                opens.pop();
                closes.push({i, close_len});
                max_len = max(max_len, close_len);
            }
        }
        return max_len;
    }
};

/* REAL stack method from Solution
    stack is used to track the previous ending idx that we can use it to count length of valid parentheses.
*/
class Solution_stack {
public:
    int longestValidParentheses(string s) {
        stack<int> stk({-1});
        int max_len = 0;
        for(int i=0 ; i<s.length() ; i++){
            if(s[i] == '('){
                stk.push(i);
            }else{
                stk.pop();
                if(stk.empty())
                    stk.push(i);
                else
                    max_len = max(max_len, i-stk.top());
            }
        }
        return max_len;
    }
};
/* DP solution: dp to memo the max valid len at current idx.
    "()" : dp[i] = 2 + dp[i-2]
    "))" : if s[i-dp[i-1]] == '(' then it match to current ')'
           dp[i] = 2 + dp[i-1] + dp[i - dp[i-1] - 2]
*/

class Solution_dp{
public:
    int longestValidParentheses(string s){
        vector<int> dp(s.length());
        int max_len = 0;
        for(int i = 1; i < s.length() ; i++){
            if(s[i] == ')'){
                if(s[i-1] == '('){
                    dp[i] = 2 + ((i>=2)? dp[i-2] : 0);
                }
                else if(i-dp[i-1] > 0 && s[ i-dp[i-1] -1 ] == '('){
                    dp[i] = 2 + dp[i-1] + ((i-dp[i-1]-2 < 0)? 0 : dp[i-dp[i-1]-2]);
                }
                max_len = max(max_len, dp[i]);
            }
        }
        return max_len;
    }
};

/*Solution that without extra space.... super smart
    - two scans: one from left to right, one right to left.
    - two counter, 'left' count open parenthese, 'right' count close parenthese
    - treat it as valid string len only when left counter == right counter.
    - reset both counter while right > left
*/
class Solution{
public:
    int longestValidParentheses(string s){
        int left = 0, right = 0, max_len = 0;
        for(char c : s){
            if(c=='(')
                left++;
            else
                right++;
            if(right>left){
                left = right = 0;
            }else if(right == left){
                max_len = max(max_len, left << 1);
            }
        }
        left = right = 0;
        for(auto it = s.rbegin(); it != s.rend() ; it++){
            char c = *it;
            if(c=='(')
                left++;
            else
                right++;
            if(left > right){
                left = right = 0;
            }else if(right == left){
                max_len = max(max_len, left << 1);
            }
        }
        return max_len;
    }
};



TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.longestValidParentheses("(()"), 2);
    EXPECT_EQ(s.longestValidParentheses(")()())"), 4);
    EXPECT_EQ(s.longestValidParentheses(")(()))"), 4);
    EXPECT_EQ(s.longestValidParentheses(""), 0);
    EXPECT_EQ(s.longestValidParentheses(")(()))(((()))()))(("), 10);
}