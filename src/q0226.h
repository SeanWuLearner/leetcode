#include "tree_node.h"
/* Solution1 : recursive */
class Solution_recursive {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr) return nullptr;

        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

/* Solution2 : iterative */
#include <queue>
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode *node = q.front();
            q.pop();
            if(node==nullptr) continue;

            q.push(node->left);
            q.push(node->right);
            swap(node->left, node->right);
        }
        return root;
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{4,2,7,1,3,6,9}}, exp{{4,7,2,9,6,3,1}};
    EXPECT_EQ(*s.invertTree(&root), exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{2,1,3}}, exp{{2,3,1}};
    EXPECT_EQ(*s.invertTree(&root), exp);
}

TEST(Solution, Test3){
    Solution s;
    EXPECT_EQ(s.invertTree(nullptr), nullptr);
}