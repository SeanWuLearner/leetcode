#include <stack>

class Solution {
private:
    bool isBalanced(char o, char c){
        return (o=='(' && c==')') || (o=='[' && c==']') || (o=='{' && c=='}');
    }
public:
    bool isValid(string s) {
        stack<char> stk;
        for(auto c : s){
            if(c=='(' || c=='[' || c=='{'){
                stk.push(c);
                continue;
            }
            
            if(stk.empty())
                return false;
            
            if(isBalanced(stk.top(), c)==false)
                return false;
            
            stk.pop();
        }
        return stk.empty();
    }
};


TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.isValid("()"), true);
    EXPECT_EQ(s.isValid("()[]{}"), true);
    EXPECT_EQ(s.isValid("(]"), false);
    EXPECT_EQ(s.isValid("([)]"), false);
    EXPECT_EQ(s.isValid("{[]}"), true);
}
