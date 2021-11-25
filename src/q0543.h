#include "tree_node.h"

class Solution {
public:
    int helper(TreeNode *root, int &max_len){
        if(root == nullptr)
            return 0;

        int l = helper(root->left, max_len);
        int r = helper(root->right, max_len);
        max_len = max(max_len, l+r);
        return 1 + max(l, r);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int max_len = INT_MIN;
        helper(root, max_len);
        return max_len;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    TreeNode t;

    t = {{1,2,3,4,5}};
    EXPECT_EQ(s.diameterOfBinaryTree(&t), 3);

    t = {{1,2}};
    EXPECT_EQ(s.diameterOfBinaryTree(&t), 1);
}
