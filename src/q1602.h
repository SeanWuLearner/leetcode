#include "tree_node.h"

/*Solution 1: level order transversal, from left to right, recursively */
class Solution1 {
public:
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        bool metTarget = false;

        while(!q.empty()){
            TreeNode *cur = q.front();
            q.pop();

            if(cur==nullptr){
                if(metTarget)
                    return nullptr;
                if(!q.empty())
                    q.push(nullptr);
                continue;
            }
            if(metTarget)
                return cur;
            if(cur == u){
                metTarget = true;
            }else{
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
        }
        return nullptr;
    }
};
/*Solution 2: level order transversal, from left to right, iteratively */
class Solution{
public:
    void dfs(TreeNode* root, TreeNode* u, int curlevel, int &tarlevel, TreeNode **res){
        if(*res!=nullptr || root==nullptr) return;

        if(root == u){
            tarlevel = curlevel;
        }else if(curlevel == tarlevel && (*res)==nullptr){
            *res = root;
        }else{
            dfs(root->left, u, curlevel+1, tarlevel, res);
            dfs(root->right, u, curlevel+1, tarlevel, res);
        }
    }
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        TreeNode *res = nullptr;
        int tarlevel = -1;
        dfs(root, u, 0, tarlevel, &res);
        return res;
    }
};

#define null (NULL_TNODE)
TEST(Solution, test1){
    Solution s;
    TreeNode root{{1,2,3,null,4,5,6}};
    TreeNode *u = root.find(4);
    int exp = 5;
    EXPECT_EQ(s.findNearestRightNode(&root, u)->val, exp);
}

TEST(Solution, test2){
    Solution s;
    TreeNode root{{3,null,4,2}};
    TreeNode *u = root.find(2);
    EXPECT_EQ(s.findNearestRightNode(&root, u), nullptr);
}