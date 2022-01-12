#include "tree_node.h"

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr) return new TreeNode(val);

        if(val > root->val)
            root->right = insertIntoBST(root->right, val);
        else
            root->left = insertIntoBST(root->left, val);
        return root;
    }
};

#define null NULL_TNODE

TEST(Solution, test1){
    Solution s;
    int insert = 5;
    TreeNode root{{4,2,7,1,3}};
    TreeNode exp{{4,2,7,1,3,5}};
    EXPECT_EQ(*s.insertIntoBST(&root, insert), exp);
}

TEST(Solution, test2){
    Solution s;
    int insert = 25;
    TreeNode root{{40,20,60,10,30,50,70}};
    TreeNode exp{{40,20,60,10,30,50,70,null,null,25}};
    EXPECT_EQ(*s.insertIntoBST(&root, insert), exp);
}

TEST(Solution, test3){
    Solution s;
    int insert = 5;
    TreeNode root{{4,2,7,1,3,null,null,null,null,null,null}};
    TreeNode exp{{4,2,7,1,3,5}};
    EXPECT_EQ(*s.insertIntoBST(&root, insert), exp);
}