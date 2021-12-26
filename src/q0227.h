/*
data structure:
    stack of nums
    stack of ops : + - (* / will be consumed beforehand)

    s0. util: extract num and turn it into int
    s1. preprocess: drop spaces in s
    s2. for char in s, extract num and push it into stack.
    s3. extract operator
        if op is mul or div, than extract the next num and compute the result and put
            it in num stack.
        if op is add or sub, insert ops into stack of ops.
    s4. prepare: pop one num from stack in advance as num1.
        while non-empty stack:
            -get one op and one num from their stack.
            -perform computation with num1
            -keep the comutation result for next iteration.
    s5. return the final result;
*/

class Solution_MyStack {
private:
    bool isOperand(char c){
        return c=='+' || c=='-' || c=='*' || c=='/' ;
    }
    int parseNum(string &s, int& i){
        int end_idx;
        for(end_idx = i+1 ; end_idx < s.length(); end_idx++ ){
            if(isOperand(s[end_idx])) break;
        }
        int ret = stoi(s.substr(i, end_idx - i));
        i = end_idx;
        return ret;
    }
    string removeSpace(string& s){
        string res;
        for(auto& c: s)
            if(c!=' ')
                res+=c;
        return res;
    }
public:
    int calculate(string s) {
        vector<int> nums;
        vector<bool> is_add;

        s = removeSpace(s);

        char op = '+';
        int num1=0, num2=0;
        for(int i=0 ; i<s.length();){
            int num2 = parseNum(s, i);
            if(op=='*' || op=='/'){
                num1 = nums.back(); nums.pop_back();
                nums.push_back( (op=='*')? (num1*num2) : (num1/num2));
            }else
                nums.push_back(num2);

            if(i==s.length())
                break;

            // handling op
            op = s[i++];
            if(op=='+' || op=='-'){
                is_add.push_back(op=='+');
            }
        }
        //deal with add/sub
        num1 = nums[0];
        for(int i=1 ; i< nums.size(); i++){
            num2 = nums[i];
            num1 = (is_add[i-1])? (num1+num2) : (num1-num2);
        }
        return num1;
    }
};

/* Solution2 : same as Solution1, using stack, but
    we don't need stack of ops, just sort out the stack of nums that they can be
    simply "sum" up at 2nd pass.
*/
#include <stack>
class Solution_SingleStack{
public:
    int calculate(string s) {
        stack<int> nums;
        int cur_num=0, pre_num=0;
        char op = '+';
        for(int i=0 ; i<s.length() ; i++){
            char c = s[i];
            if(isdigit(c)){
                cur_num = cur_num * 10 + (c-'0');
            }

            if(i==s.length()-1 || (c!=' ' && !isdigit(c))){
                switch(op){
                case '+':
                    nums.push(cur_num);
                    break;
                case '-':
                    nums.push(-cur_num);
                    break;
                case '*':
                    pre_num = nums.top(); nums.pop();
                    nums.push(cur_num * pre_num);
                    break;
                case '/':
                    pre_num = nums.top(); nums.pop();
                    nums.push(pre_num / cur_num);
                    break;
                }
                op = c;
                cur_num = 0;
            }
        }

        int sum=0;
        while(!nums.empty()){
            sum += nums.top();
            nums.pop();
        }
        return sum;
    }
};

/*Solution3: No stack, because without parentheses, add/sub can be processed
    into the "result" immediately. Other than that, we only need and additional
    var 'pre_num' to keep the previous num
*/
class Solution{
public:
    int calculate(string s) {
        int cur_num=0, pre_num=0, res=0;
        char op = '+';
        for(int i=0 ; i<s.length() ; i++){
            char c = s[i];
            if(isdigit(c)){
                cur_num = cur_num * 10 + (c-'0');
            }

            if(i==s.length()-1 || (c!=' ' && !isdigit(c))){
                switch(op){
                case '+':
                    res += pre_num;
                    pre_num = cur_num;
                    break;
                case '-':
                    res += pre_num;
                    pre_num = -cur_num;
                    break;
                case '*':
                    pre_num *= cur_num ;
                    break;
                case '/':
                    pre_num /= cur_num;
                    break;
                }
                op = c;
                cur_num = 0;
            }
        }
        res += pre_num;
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    string q; int exp;

    q = "3+2*2";
    exp = 7;
    EXPECT_EQ(s.calculate(q), exp);

    q = " 3/2 ";
    exp = 1;
    EXPECT_EQ(s.calculate(q), exp);

    q = " 3+5 / 2 ";
    exp = 5;
    EXPECT_EQ(s.calculate(q), exp);
}