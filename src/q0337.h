#include "tree_node.h"

/*
    For every single node, it will return two value,
    1. linked_ = root + unlinked_l + unlinked_r
    2. unlinked = max(linked_l, unlinked_l) + max(linked_r, unlinked_r)
*/
class Solution {
private:
    /*Returns: pair<linked_max, unlinked_max>*/
    pair<int,int> helper(TreeNode *root){
        if(root==nullptr)
            return {0,0};
        auto ret_l = helper(root->left);
        auto ret_r = helper(root->right);
        int linked = root->val + ret_l.second + ret_r.second;
        int unlinked = max(ret_l.first, ret_l.second) + max(ret_r.first, ret_r.second);
        return {linked, unlinked};
    }
public:
    int rob(TreeNode* root) {
        auto ret = helper(root);
        return max(ret.first, ret.second);
    }
};

TEST(TestSolution, test1) {
    Solution s;
    TreeNode t({3,2,3,NULL_TNODE,3,NULL_TNODE,1});

    EXPECT_EQ(s.rob(&t), 7);

    t = TreeNode({3,4,5,1,3,NULL_TNODE,1});
    EXPECT_EQ(s.rob(&t), 9);
}
