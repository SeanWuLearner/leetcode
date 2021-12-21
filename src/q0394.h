
/* Solution 1: recursion */
class Solution_recursion {
private:
    int getInt(string &s, int& idx){
        string buf;
        while(s[idx]>='0' && s[idx]<='9'){
            buf += s[idx];
            idx++;
        }
        return stoi(buf);
    }
    string duplicate(string&& s, int times){
        string res;
        while(times-->0){
            res += s;
        }
        return res;
    }
    string helper(string& s, int& idx){
        string res;
        int times = 0;
        while(idx < s.length()){
            switch(s[idx]){
            case ']':
                idx++;
                return res;
            case '[':
                idx++;
                res += duplicate(helper(s, idx), times);
                break;
            case 'a'...'z':
                res += s[idx];
                idx++;
                break;
            case '0'...'9':
                times = getInt(s, idx);
                break;
            default:
                cout << "Illegal char given:" << s[idx] << endl;
                return "";
            }
        }
        return res;
    }
public:
    string decodeString(string s) {
        int idx = 0;
        return helper(s, idx);
    }
};

/* Solution 2: using stack
    push string and times while encounter '['
    pop and merge them together while ']'
*/
#include <stack>
class Solution{
private:
    int getInt(string &s, int& idx){
        string buf;
        while(s[idx]>='0' && s[idx]<='9'){
            buf += s[idx];
            idx++;
        }
        return stoi(buf);
    }
    string duplicate(string& s, int times){
        string res;
        while(times-->0){
            res += s;
        }
        return res;
    }
public:
    string decodeString(string s) {
        int i = 0;
        stack<pair<string, int>> stk;
        string cur;
        int times;
        while(i < s.length()){
            switch(s[i]){
            case 'a'...'z':
                cur += s[i];
                i++;
                break;
            case '0'...'9':
                times = getInt(s, i);
                break;
            case '[':
                stk.push({cur, times});
                cur = "";
                i++;
                break;
            case ']':
                auto prev = stk.top();
                stk.pop();
                cur = prev.first + duplicate(cur, prev.second);
                i++;
                break;
            }
        }
        return cur;
    }
};

TEST(Solution, test1){
    Solution s;
    EXPECT_EQ(s.decodeString("3[a]2[bc]"), "aaabcbc");
    EXPECT_EQ(s.decodeString("3[a2[c]]"), "accaccacc");
    EXPECT_EQ(s.decodeString("2[abc]3[cd]ef"), "abcabccdcdcdef");
    EXPECT_EQ(s.decodeString("abc3[cd]xyz"), "abccdcdcdxyz");
}