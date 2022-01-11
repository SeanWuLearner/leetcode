#include "tree_node.h"

/*Solution 1: recursive*/
class Solution1 {
private:
    void helper(TreeNode* node, int cur, int &sum){
        cur <<= 1;
        cur |= node->val;
        if(node->left==nullptr && node->right==nullptr){
            sum += cur;
            return;
        }
        if(node->left)
            helper(node->left, cur, sum);
        if(node->right)
            helper(node->right, cur, sum);
    }
public:
    int sumRootToLeaf(TreeNode* root) {
        if(root==nullptr) return 0;
        int sum=0;
        helper(root, 0, sum);
        return sum;
    }
};

/*Solution 1: recursive, super neat*/
class Solution {
public:
    int sumRootToLeaf(TreeNode* root, int val=0) {
        if(root==nullptr) return 0;
        val = val*2 + root->val;
        return (root->left==root->right)? val : sumRootToLeaf(root->left, val) +
                                                sumRootToLeaf(root->right, val);
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{1,0,1,0,1,0,1}};
    EXPECT_EQ(s.sumRootToLeaf(&root), 22);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{0};
    EXPECT_EQ(s.sumRootToLeaf(&root), 0);
}