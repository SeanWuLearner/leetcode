#include "tree_node.h"
/* Solution1: reverse pre-order, and attach the previous travelled node to cur one.
    pre-order : root, left, right
    reverser pre-order : right, left, root
*/
class Solution {
private:
    TreeNode* helper(TreeNode* root, TreeNode* prev){
        if(root==nullptr) return prev;
        TreeNode *right = helper(root->right, prev);
        TreeNode *left = helper(root->left, right);
        root->right = left;
        root->left = nullptr;
        return root;
    }
public:
    void flatten(TreeNode* root) {
        helper(root, nullptr);
    }
};

#define null (NULL_TNODE)
TEST(Solution, Test1){
    Solution s;
    TreeNode q{{1,2,5,3,4,null,6}};
    TreeNode exp{{1,null,2,null,3,null,4,null,5,null,6}};
    s.flatten(&q);
    EXPECT_EQ(q, exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode *q = nullptr;
    s.flatten(q);
    EXPECT_EQ(q, nullptr);
}

TEST(Solution, Test3){
    Solution s;
    TreeNode q{{0}};
    TreeNode exp{{0}};
    s.flatten(&q);
    EXPECT_EQ(q, exp);
}