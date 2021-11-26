/* My solution, just try not to store a stack and handle it on 2nd pass... */
class MySolution {
public:
    string minRemoveToMakeValid(string s) {
        int cnt_open=0;
        string buf, res;
        // from left to right, drop illegal ')'
        for(auto c : s){
            if(c==')'){
                if(cnt_open==0)
                    continue;
                cnt_open--;
            }
            else if(c == '(')
                cnt_open++;

            buf += c;
        }
        //from right to left, drop illegal '('
        cnt_open = 0;
        for(auto it = buf.rbegin() ; it != buf.rend() ; it++){
            char c = *it;
            if(c=='('){
                if(cnt_open==0)
                    continue;
                cnt_open--;
            }
            else if(c == ')')
                cnt_open++;

            res += c;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/* 1. Use stack for marking the illegal open parenthesis
   2. Use '#' as special char (to be removed).
*/
#include <stack>
#include <algorithm>
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> opens;
        for(int i=0; i<s.length(); i++){
            if(s[i]=='(')
                opens.push(i);
            else if(s[i]==')'){
                if(opens.empty()){
                    s[i] = '#';
                    continue;
                }
                opens.pop();
            }
        }
        while(opens.empty()!=true){
            s[opens.top()] = '#';
            opens.pop();
        }

        // string res;
        // for(auto c : s){
        //     if(c!='#')
        //         res += c;
        // }
        // return res;

        //  in-place modification.
        s.erase(
            remove_if(s.begin(), s.end(), [](auto &c){return c=='#';}),
            s.end()
            );
        return s;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    string ans;

    ans = s.minRemoveToMakeValid("lee(t(c)o)de)");
    EXPECT_EQ(true, (ans=="lee(t(c)o)de" || ans=="lee(t(co)de)" || ans == "lee(t(c)ode)"));

    ans = s.minRemoveToMakeValid("a)b(c)d");
    EXPECT_EQ(ans, "ab(c)d");

    ans = s.minRemoveToMakeValid("))((");
    EXPECT_EQ(ans, "");

    ans = s.minRemoveToMakeValid("(a(b(c)d)");
    EXPECT_EQ(ans, "a(b(c)d)");
}