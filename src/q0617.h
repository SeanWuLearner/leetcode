#include "tree_node.h"
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr && root2==nullptr) return nullptr;
        int val1=0, val2=0;
        TreeNode *l1=nullptr, *l2=nullptr, *r1=nullptr, *r2=nullptr;
                
        if(root1 != nullptr){
            val1 = root1->val;
            l1 = root1->left;
            r1 = root1->right;
        }
        if(root2 != nullptr){
            val2 = root2->val;
            l2 = root2->left;
            r2 = root2->right;
        }
        TreeNode *cur = new TreeNode(val1+val2);
        cur->left = mergeTrees(l1, l2);
        cur->right = mergeTrees(r1, r2);
        return cur;
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode *ans;

    TreeNode t1({1,3,2,5,NULL_TNODE,NULL_TNODE,NULL_TNODE});
    TreeNode t2({2,1,3,NULL_TNODE, 4, NULL_TNODE, 7});
    TreeNode exp({3,4,5,5,4,NULL_TNODE,7});
    ans = s.mergeTrees(&t1, &t2);
    EXPECT_EQ(ans->draw(), exp.draw());
}

TEST(Solution, Test2){
    Solution s;
    TreeNode *ans;

    TreeNode t1({1});
    TreeNode t2({1,2});
    TreeNode exp({2,2});
    ans = s.mergeTrees(&t1, &t2);
    EXPECT_EQ(ans->draw(), exp.draw());
}