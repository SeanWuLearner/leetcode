#include "tree_node.h"
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr) return true;
        if(p==nullptr || q==nullptr) return false;

        if(p->val != q->val) return false;
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root1{{1,2,3}};
    TreeNode root2{{1,2,3}};
    bool exp = true;
    EXPECT_EQ(exp, s.isSameTree(&root1, &root2));
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root1{{1,2}};
    TreeNode root2{{1, NULL_TNODE,2}};
    bool exp = false;
    EXPECT_EQ(exp, s.isSameTree(&root1, &root2));
}

TEST(Solution, Test3){
    Solution s;
    TreeNode root1{{1,2,1}};
    TreeNode root2{{1,1,2}};
    bool exp = false;
    EXPECT_EQ(exp, s.isSameTree(&root1, &root2));
}