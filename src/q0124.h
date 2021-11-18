
#include "TreeNode.h"

class MySolution {
    int max_sum;
public:
    int helper(TreeNode* root){
        if(root==nullptr)
            return 0;

        int res_l = helper(root->left);
        int res_r = helper(root->right);
        int local_max = root->val;
        int ret = root->val;
        if(res_l > 0){
            local_max += res_l;
            if(res_l > res_r)
                ret += res_l;
        }
        if(res_r > 0){
            local_max += res_r;
            if(res_r > res_l)
                ret += res_r;
        }
        max_sum = max(max_sum, local_max);
        return ret;
    }
    int maxPathSum(TreeNode* root) {
        max_sum = INT_MIN;
        helper(root);
        return max_sum;
    }
};

/* 4ms submission*/
class Solution {
    int max_sum;
public:
    int helper(TreeNode* root){
        if(root==nullptr)
            return 0;

        int res_l = helper(root->left);
        int res_r = helper(root->right);
        max_sum = max(max_sum, root->val + res_l + res_r);
        return max(max(max(res_l, res_r) + root->val , root->val), 0);
    }
    int maxPathSum(TreeNode* root) {
        max_sum = 0;
        helper(root);
        return max_sum;
    }
};


TEST(TestSolution, test1) {
    Solution s;

    TreeNode t{{1,2,3}};
    EXPECT_EQ(s.maxPathSum(&t), 6);

    t = {{-10,9,20,NULL_TNODE,NULL_TNODE,15,7}};
    EXPECT_EQ(s.maxPathSum(&t), 42);

    t = {{5,4,8,11,NULL_TNODE,13,4,7,2,NULL_TNODE,NULL_TNODE,NULL_TNODE,1}};
    EXPECT_EQ(s.maxPathSum(&t), 48);

}