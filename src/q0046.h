#include "vector_util.h"
/*Solution1: backtracking*/
class Solution_VisitedArray {
private:
    void backtracking(vector<int>& nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& res){
        if(cur.size() == nums.size()){
            res.push_back(cur);
            return;
        }

        for(int i=0 ; i<nums.size(); i++){
            if(used[i]) continue;
            used[i] = true;
            cur.push_back(nums[i]);
            backtracking(nums, used, cur, res);
            cur.pop_back();
            used[i] = false;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> cur;
        vector<bool> used(nums.size(), false);
        vector<vector<int>> res;
        backtracking(nums, used, cur, res);
        return res;
    }
};

/*Solution2: backtracking with swapping, O(1) space, but backtrack call is still O(n) deep.*/
class Solution {
private:
    void backtrack(vector<int>& nums, int first, vector<vector<int>>& res){
        if(first == nums.size()-1){
            res.push_back(nums);
            return;
        }
        for(int i=first; i < nums.size() ; i++){
            swap(nums[i], nums[first]);
            backtrack(nums, first+1, res);
            swap(nums[i], nums[first]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(nums, 0,  res);
        return res;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp, ans;

    q = {1,2,3};
    exp = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
    ans = s.permute(q);
    EXPECT_EQ(sortVec(exp), sortVec(ans));

    q = {0,1};
    exp = {{0,1},{1,0}};
    ans = s.permute(q);
    EXPECT_EQ(sortVec(exp), sortVec(ans));
}