#include "tree_node.h"
/* Solution1 : my recursion */
class Solution1 {
private:
    bool helper(TreeNode *root, int presum, int target){
        if(root==nullptr)
            return false;
        presum += root->val;
        if(root->left==nullptr && root->right==nullptr){
            return presum == target;
        }
        if(helper(root->left, presum, target))
            return true;
        return helper(root->right, presum, target);
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return helper(root, 0, targetSum);
    }
};
/* Solution 2: concise recursion */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;
        if(root->left==nullptr && root->right==nullptr) return targetSum==root->val;
        targetSum -= root->val;
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{5,4,8,11,NULL_TNODE,13,4,7,2,NULL_TNODE,NULL_TNODE,NULL_TNODE,1}};
    int target = 22;
    bool exp = true;
    EXPECT_EQ(s.hasPathSum(&root, target), exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{1,2,3}};
    int target = 5;
    bool exp = false;
    EXPECT_EQ(s.hasPathSum(&root, target), exp);
}

TEST(Solution, Test3){
    Solution s;
    TreeNode *root = nullptr;
    int target = 0;
    bool exp = false;
    EXPECT_EQ(s.hasPathSum(root, target), exp);
}