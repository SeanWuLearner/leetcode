#include "tree_node.h"
class Solution {
private:
    int helper(TreeNode* root, int& k){
        if(root==nullptr) return -1;
        int left_val, right_val;
        left_val = helper(root->left, k);
        if(left_val != -1)
            return left_val;
        if(k==1)
            return root->val;
        k--;
        return helper(root->right, k);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        return helper(root, k);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> arr{3,1,4,NULL_TNODE,2};
    TreeNode root{arr};
    EXPECT_EQ(s.kthSmallest(&root, 1), 1);

    arr = {5,3,6,2,4,NULL_TNODE,NULL_TNODE,1};
    TreeNode root2{arr};
    EXPECT_EQ(s.kthSmallest(&root2, 3), 3);
}