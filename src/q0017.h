void printv(vector<string> v){
    for(auto &i : v){
        cout << i << ", ";
    }
    cout << endl;
}

class Solution_backtracking {
private:
    unordered_map<char, string> num_letters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
    void backtracking(string& digits, int idx, string& acc, vector<string>& res){
        if(acc.length() == digits.length()){
            res.push_back(acc);
            return;
        }
        string& letters = num_letters[digits[idx]];
        for(char c : letters){
            acc += c;
            backtracking(digits, idx+1, acc, res);
            acc.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if(digits.length()==0) return {};
        vector<string> res;
        string acc;
        backtracking(digits, 0, acc, res);
        return res;
    }
};

/* iterative solution */
class Solution {
private:
    unordered_map<char, string> num_letters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
public:
    vector<string> letterCombinations(string digits) {
        if(digits.length()==0)
            return{};

        vector<string> res = {""};
        for(char d : digits){
            vector<string> tmp;
            for(char c : num_letters[d]){
                for(string& s : res ){
                    tmp.push_back(s + c);
                }
            }
            res.swap(tmp);
        }
        // printv(res);
        return res;
    }
};

#include <unordered_set>
template<typename T>
bool isUnorderedlyEqual(vector<T> v1, vector<T> v2){
    unordered_set<T> t1(v1.begin(), v1.end());
    unordered_set<T> t2(v2.begin(), v2.end());
    return t1==t2;
}

TEST(TestSolution, test1) {
    Solution s;
    vector<string> ans;
    ans = {"ad","ae","af","bd","be","bf","cd","ce","cf"};
    EXPECT_EQ(isUnorderedlyEqual(s.letterCombinations("23"), ans), true);

    EXPECT_EQ(s.letterCombinations(""), vector<string>());

    ans = {"a", "b", "c"};
    EXPECT_EQ(isUnorderedlyEqual(s.letterCombinations("2"), ans), true);
}