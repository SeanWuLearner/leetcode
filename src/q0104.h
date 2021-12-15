#include "tree_node.h"

class Solution_myRecursion {
private:
    int max_height = 0;
    void helper(TreeNode* root, int height){
        if(root == nullptr) return;
        max_height = max(max_height, height);
        helper(root->left, height+1);
        helper(root->right, height+1);
    }
public:
    int maxDepth(TreeNode* root) {
        max_height = 0;
        helper(root, 1);
        return max_height;
    }
};

/*Solution: super neat*/
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        return max(1+maxDepth(root->left), 1+maxDepth(root->right));
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode q1{{3,9,20,NULL_TNODE,NULL_TNODE,15,7}};
    EXPECT_EQ(s.maxDepth(&q1), 3);

    TreeNode q2{{1,NULL_TNODE,2}};
    EXPECT_EQ(s.maxDepth(&q2), 2);

    EXPECT_EQ(s.maxDepth(nullptr), 0);

    TreeNode q4{{0}};
    EXPECT_EQ(s.maxDepth(&q4), 1);
}