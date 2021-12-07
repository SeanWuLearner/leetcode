#include "tree_node.h"

/* recursive */
class Solution_recursive {
private:
    bool helper(TreeNode* left, TreeNode* right){
        if(left == nullptr && right == nullptr) return true;
        if(left == nullptr) return false;
        if(right == nullptr) return false;
        if(left->val != right->val) return false;

        if(helper(left->left, right->right)==false) return false;
        return helper(left->right, right->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) return true;
        return helper(root->left, root->right);
    }
};

/* iterative */
#include <queue>
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) return true;
        queue<TreeNode*> ql, qr;
        ql.push(root->left); qr.push(root->right);
        while(!ql.empty()){
            TreeNode *left = ql.front(); ql.pop();
            TreeNode *right = qr.front(); qr.pop();
            if(left == nullptr && right==nullptr) continue;
            if(left == nullptr) return false;
            if(right == nullptr) return false;
            if(left->val != right->val) return false;
            ql.push(left->left); qr.push(right->right);
            ql.push(left->right); qr.push(right->left);
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;

    TreeNode root1{{1,2,2,3,4,4,3}};
    EXPECT_EQ(s.isSymmetric(&root1), true);

    TreeNode root2{{1,2,2,NULL_TNODE,3,NULL_TNODE,3}};
    EXPECT_EQ(s.isSymmetric(&root2), false);

}