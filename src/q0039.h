#include "vector_util.h"
using Matrix = vector<vector<int>>;
class Solution {
private:
    Matrix res;
    
    void backtracking(vector<int>& candidates, int idx, int target, vector<int>& acc){
        if(target < 0) 
            return;
        if(target == 0){
            res.push_back(acc);
            return;
        }

        for(int i = idx ; i < candidates.size() ; i++){
            acc.push_back(candidates[i]);
            backtracking(candidates, i, target - candidates[i], acc);
            acc.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> acc;
        backtracking(candidates, 0, target, acc);
        // printVec(res);
        return res;
    }
};

template<typename T>
bool isEqual(T& m1, T& m2){
    sort(m1.begin(), m1.end());
    sort(m2.begin(), m2.end());
    return m1==m2;
}

TEST(Solution, Test1){
    Solution s;
    vector<int> candidates;
    Matrix ans, exp;

    candidates = {2,3,6,7};
    ans = s.combinationSum(candidates, 7);
    exp = {{2,2,3},{7}};
    EXPECT_EQ(true, isEqual(ans, exp));
}

TEST(Solution, Test2){
    Solution s;
    vector<int> candidates;
    Matrix ans, exp;

    candidates = {2,3,5};
    ans = s.combinationSum(candidates, 8);
    exp = {{2,2,2,2},{2,3,3},{3,5}};
    EXPECT_EQ(true, isEqual(ans, exp));
}

TEST(Solution, Test3){
    Solution s;
    vector<int> candidates;
    Matrix ans, exp;

    candidates = {2};
    ans = s.combinationSum(candidates, 1);
    exp = {};
    EXPECT_EQ(true, isEqual(ans, exp));
}

TEST(Solution, Test4){
    Solution s;
    vector<int> candidates;
    Matrix ans, exp;

    candidates = {1};
    ans = s.combinationSum(candidates, 2);
    exp = {{1,1}};
    EXPECT_EQ(true, isEqual(ans, exp));
}