#include "tree_node.h"

/* Solution: level-order trasversal, from right to left, so only 1st elements of
    each level are inserted into answer vector.
 */
#include <queue>
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        TreeNode delimiter;
        queue<TreeNode*> q;
        q.push(root);
        q.push(&delimiter);
        vector<int> res;
        int level = 1;
        while(!q.empty()){
            TreeNode *cur = q.front();
            q.pop();
            if(cur == nullptr)
                continue;
            if(cur == &delimiter){
                level++;
                if(!q.empty())
                    q.push(&delimiter);
                continue;
            }

            if(res.size() < level){
                res.push_back(cur->val);
            }
            q.push(cur->right);
            q.push(cur->left);
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{1,2,3,NULL_TNODE,5,NULL_TNODE,4}};
    vector<int> exp = {1,3,4};
    EXPECT_EQ(s.rightSideView(&root), exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{1,NULL_TNODE,3}};
    vector<int> exp = {1,3};
    EXPECT_EQ(s.rightSideView(&root), exp);
}

TEST(Solution, Test3){
    Solution s;
    vector<int> exp;
    EXPECT_EQ(s.rightSideView(nullptr), exp);
}
