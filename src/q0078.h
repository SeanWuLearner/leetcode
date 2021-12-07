/* Solution1: backtracking */
class Solution_backtracking {
private:
    vector<vector<int>> ans;
    void backtracking(vector<int>& nums, int idx, int len, vector<int>& cur){
        if(len == 0){
            ans.push_back(cur);
            return;
        }

        for(int i = idx ; i < nums.size() ; i++){
            cur.push_back(nums[i]);
            backtracking(nums, i+1, len-1, cur);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> cur;
        for(int i = 0 ; i <=nums.size() ; i++){
            backtracking(nums, 0, i, cur);
        }
        return ans;
    }
};

/* Solution2: cascade */
class Solution{
private:
    vector<vector<int>> ans;
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        ans.push_back({});
        for(int i = 0 ; i <nums.size() ; i++){
            int sz_ans = ans.size();
            for(int j = 0 ; j < sz_ans ; j++){
                ans.push_back(ans[j]);
                ans.back().push_back(nums[i]);
            }
        }
        return ans;
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
    vector<int> q;
    vector<vector<int>> exp, ans;

    q = {1,2,3};
    exp = {{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3}};
    ans = s.subsets(q);
    EXPECT_EQ(isEqual(ans, exp), true);
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp, ans;

    q = {0};
    exp = {{},{0}};
    ans = s.subsets(q);
    EXPECT_EQ(isEqual(ans, exp), true);
}