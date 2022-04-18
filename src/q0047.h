#include "vector_util.h"

/* Solution 1: normal backtrack with used array */
class Solution1{
public:
    void backtrack(vector<int> &nums, vector<bool> &used, vector<int> &perm, vector<vector<int>> &ans){
        if(perm.size() == nums.size()){
            ans.push_back(perm);
            return;
        }
        for(int i=0 ; i<nums.size() ; i++){
            if(used[i]) continue;
            if(i>0 && nums[i]==nums[i-1] && !used[i-1]) continue;
            used[i] = true;
            perm.push_back(nums[i]);
            backtrack(nums, used, perm, ans);
            perm.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> used(nums.size(), false);
        vector<int> perm;
        vector<vector<int>> ans;
        backtrack(nums, used, perm, ans);
        return ans;
    }
};

/* Solution 2: get permuations with swapping */
class Solution {
public:
    void backtrack(vector<int> nums, int start, vector<vector<int>> &ans){
        if(start == nums.size()-1){
            ans.push_back(nums);
            return;
        }
        for(int i=start ; i<nums.size() ; i++){
            if(i!=start && nums[i]==nums[start]) continue;
            swap(nums[i], nums[start]);
            backtrack(nums, start+1, ans);
            // swap(nums[i], nums[start]);

        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        backtrack(nums, 0, ans);
        return ans;
    }
};



TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp, res;

    q = {1,2,3};
    exp = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
    EXPECT_EQ(sortVec(exp), sortVec(s.permuteUnique(q)));
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp, res;

    q = {2,2,1,1};
    exp = {{1,1,2,2},{1,2,1,2},{1,2,2,1},{2,1,1,2},{2,1,2,1},{2,2,1,1}};
    EXPECT_EQ(sortVec(exp), sortVec(s.permuteUnique(q)));
}

TEST(Solution, Test3){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp, res;

    q = {1,1,2};
    exp = {{1,1,2},{1,2,1},{2,1,1}};
    EXPECT_EQ(sortVec(exp), sortVec(s.permuteUnique(q)));
}