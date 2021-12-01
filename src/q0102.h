#include <queue>
#include "tree_node.h"

/* Solution using queue */
class Solution_queue {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            if(cur.first == nullptr) continue;
            q.push({cur.first->left, cur.second+1});
            q.push({cur.first->right, cur.second+1});
            if(res.size() < cur.second+1)
                res.push_back(vector<int>());
            res[cur.second].push_back(cur.first->val);
        }
        return res;
    }
};

/* recursive solution */
class Solution {
private:
    void helper(TreeNode *root, int level, vector<vector<int>>& res){
        if(root == nullptr)
            return;
        if(level >= res.size())
            res.push_back(vector<int>());
        res[level].push_back(root->val);
        helper(root->left, level+1, res);
        helper(root->right, level+1, res);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        helper(root, 0, res);
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> ans;
    TreeNode root{{3,9,20,NULL_TNODE,NULL_TNODE,15,7}};

    ans = {{3},{9,20},{15,7}};
    EXPECT_EQ(s.levelOrder(&root), ans);

    root = TreeNode{vector<int>({1})};
    ans = {{1}};
    EXPECT_EQ(s.levelOrder(&root), ans);

    ans = vector<vector<int>>();
    EXPECT_EQ(s.levelOrder(nullptr), ans);
}