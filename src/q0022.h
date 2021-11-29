

class Solution {
private:
    string path;
    int n_;
    vector<string> res;


    void backtracking(int open_cnt, int close_cnt){
        if(path.length() == n_<<1){
            res.push_back(path);
            return;
        }
        if(open_cnt != n_){
            path += '(';
            backtracking(open_cnt+1, close_cnt);
            path.pop_back();
        }
        if(close_cnt < open_cnt){
            path += ')';
            backtracking(open_cnt, close_cnt+1);
            path.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        n_ = n;
        backtracking(0, 0);
        return res;
    }
};

#include <unordered_set>
template<typename T>
bool isEqual(vector<T> v1, vector<T> v2){
    if(v1.size() != v2.size())
        return false;
    unordered_set<T> s1(v1.begin(), v1.end());
    unordered_set<T> s2(v2.begin(), v2.end());
    return s1==s2;
}

TEST(Solution, test1){
    Solution s;
    vector<string> ans;

    ans = {"((()))","(()())","(())()","()(())","()()()"};
    EXPECT_EQ(isEqual(s.generateParenthesis(3), ans), true);
}

TEST(Solution, test2){
    Solution s;
    vector<string> ans;

    ans = {"()"};
    EXPECT_EQ(isEqual(s.generateParenthesis(1), ans), true);
}