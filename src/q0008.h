/* NG solution, "+-12" should fail the myAtoi..... Gosh */
class Solution_NG {
public:
    void getSignAndNumRange(string& s, pair<int,int>& range, bool &is_neg){
        bool has_num = false;
        is_neg = false;
        range.second = s.length();
        for(int i=0 ; i<s.length(); i++){
            if(has_num){
                if(isdigit(s[i]))
                    continue;
                else{
                    range.second = i;
                    break;
                }
            }

            //before num happens
            if(s[i]=='-'){
                is_neg = true;
                continue;
            }else if(isdigit(s[i])){
                has_num = true;
                range.first = i;
            }else if(s[i] != ' ' && s[i] != '+'){
                range.first = range.second = i;
                break;
            }
            // printf("%s, get range(%d,%d), is_neg(%d)\n", s, );
        }
    }
    long str2long(string &s, pair<int,int> &range, bool is_neg){
        long res=0;
        const long bound = (is_neg)? ((long)INT_MAX)+1 : INT_MAX;
        for(int i = range.first; i < range.second ; i++){
            res *= 10;
            res += s[i] - '0';
            if(res > bound)
                return bound;
        }
        return res;
    }
    int myAtoi(string s) {
        bool is_neg = false;
        pair<int, int> range;

        getSignAndNumRange(s, range, is_neg);
        long num = str2long(s, range, is_neg);
        return (is_neg)? -num : num;
    }
};

/* Solution : state machine */
enum State{
    q0, //initial state
    q1, // get sign
    q2, // get num
    qd  /* dead state cases:
            1. get non whitespace and non sign char at q0
            2. get non number at q1
            3. get non number at q2
            4. overflow at q2
        */
};

class StateMachine{
private:
    State state;
    int sign, res;

    void toStateQ1(char c){
        sign = (c=='-')? -1 : 1;
        state = q1;
    }

    void toStateQd(){
        state = qd;
    }

    void toStateQ2(char c){
        state = q2;

        int digit = c - '0';
        if(res > (INT_MAX / 10) || (res == (INT_MAX / 10)  && digit > INT_MAX % 10)){
            if(sign==-1){
                res = INT_MIN;
                sign = 1;
            }else{
                res = INT_MAX;
            }
            toStateQd();
            return;
        }

        res = res*10 + digit;
    }
public:
    StateMachine(): state(q0), sign(1), res(0) {}
    int getResult(){
        return res * sign;
    }
    int isDead(){
        return state == qd;
    }
    void transit(char c){
        if(state == qd) return;
        if(state == q0){
            if(c == ' ') return;
            if(c == '+' || c == '-')
                toStateQ1(c);
            else if(isdigit(c))
                toStateQ2(c);
            else
                toStateQd();
        }else if(state == q1){
            if(isdigit(c))
                toStateQ2(c);
            else
                toStateQd();
        }else{ // state = q2
            if(isdigit(c))
                toStateQ2(c);
            else
                toStateQd();
        }
    }
};

class Solution{
public:
    int myAtoi(string s) {
        StateMachine sm;
        for(auto c : s){
            sm.transit(c);
        }
        return sm.getResult();
    }
};



TEST(Solution, Test1){
    Solution s;
    string q;
    int exp;

    q = "42";
    exp = 42;
    EXPECT_EQ(s.myAtoi(q), exp);

    q = "   -42";
    exp = -42;
    EXPECT_EQ(s.myAtoi(q), exp);

    q = "4193 with words";
    exp = 4193;
    EXPECT_EQ(s.myAtoi(q), exp);

    q = "words and 987";
    exp = 0;
    EXPECT_EQ(s.myAtoi(q), exp);

    q = "+-12";
    exp = 0;
    EXPECT_EQ(s.myAtoi(q), exp);

    q = "-91283472332";
    exp = INT_MIN;
    EXPECT_EQ(s.myAtoi(q), exp);
}