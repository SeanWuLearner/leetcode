#include "tree_node.h"

/* Solution 1: recursive
    let's say p < q
    case 1: p in left subtree, q in right subtree, return root
    case 2: p is root, q in right subtree, return p
    case 3: q is root, p in left subtree, return q
    other than that, if p q both in right subtree, then recursive right. Otherwise recursive left.
*/
class Solution_recursive {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root==q) return root;

        if(p->val > q->val)
            swap(p, q);

        if(root->val > p->val){
            if(root->val > q->val)
                return lowestCommonAncestor(root->left, p, q);
            else
                return root;
        }else
            return lowestCommonAncestor(root->right, p, q);
    }
};

/*iterative*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val > q->val)
            swap(p, q);

        TreeNode *cur = root;
        while(cur!=nullptr){
            if(cur==p || cur==q)
                return cur;
            if(cur->val > p->val){
                if(cur->val > q->val)
                    cur = cur->left;
                else
                    return cur;
            }else
                cur = cur->right;
        }
        return nullptr;
    }
};

#define null NULL_TNODE
TEST(Solution, Test1){
    Solution s;
    TreeNode root{{6,2,8,0,4,7,9,null,null,3,5}};
    TreeNode *p = root.find(2);
    TreeNode *q = root.find(8);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 6);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{6,2,8,0,4,7,9,null,null,3,5}};
    TreeNode *p = root.find(2);
    TreeNode *q = root.find(4);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 2);
}

TEST(Solution, Test3){
    Solution s;
    TreeNode root{{2,1}};
    TreeNode *p = root.find(2);
    TreeNode *q = root.find(1);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 2);
}