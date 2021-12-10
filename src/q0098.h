#include "tree_node.h"
#include <stack>

/* Solution1: check min/max for each node */
class Solution_MinMax {
private:
    bool isValid(TreeNode* root, long min_val, long max_val){
        if(root == nullptr) return true;
        if(root->val <= min_val) return false;
        if(root->val >= max_val) return false;
        return isValid(root->left, min_val, root->val) &&
                isValid(root->right, root->val, max_val);
    }
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LONG_MIN, LONG_MAX);
    }
};

/* Solution2: Using inorder transversal, the next node must be greater than cur one */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        int *prev = nullptr;
        TreeNode *cur = root;
        while(cur!=nullptr || !stk.empty()){
            while(cur!=nullptr){
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            if(prev!=nullptr && *prev >= cur->val) return false;
            prev = &cur->val;
            cur = cur->right;
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;

    TreeNode root1{{2,1,3}};
    EXPECT_EQ(s.isValidBST(&root1), true);

    TreeNode root2{{5,1,4,NULL_TNODE,NULL_TNODE,3,6}};
    EXPECT_EQ(s.isValidBST(&root2), false);
}