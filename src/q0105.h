#include "tree_node.h"

/* my solution */
class Solution_naive {
private:
    TreeNode* helper(vector<int>& preorder, int& idx, vector<int>& inorder, int start, int end){
        if(idx >= preorder.size() || start==end) return nullptr;
        TreeNode *cur = new TreeNode(preorder[idx]);
        //find root node's idx of inorder seq
        int i;
        for(i=start ; i<end ; i++)
            if(preorder[idx] == inorder[i]) break;
        idx++;
        cur->left = helper(preorder, idx, inorder, start, i);
        cur->right = helper(preorder, idx, inorder, i+1, end);
        return cur;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int idx = 0;
        return helper(preorder, idx, inorder, 0, inorder.size());
    }
};

/* solution: use a inv_hash_map to speed up */
class Solution {
private:
    unordered_map<int, int> idx_map; //index map for inorder.
    int idx_pre;

    TreeNode* helper(vector<int>& preorder, int start, int end){
        if(start > end) return nullptr;
        int rootval = preorder[idx_pre++];
        TreeNode *cur = new TreeNode(rootval);
        cur->left = helper(preorder, start, idx_map[rootval] - 1);
        cur->right = helper(preorder, idx_map[rootval]+1 , end);
        return cur;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //build map
        for(int i = 0 ; i<inorder.size(); i++)
            idx_map[inorder[i]] = i;

        idx_pre = 0;
        return helper(preorder, 0, inorder.size()-1);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> pre, in;

    pre = {3,9,20,15,7};
    in = {9,3,15,20,7};
    TreeNode ans1{{3,9,20,NULL_TNODE,NULL_TNODE,15,7}};
    TreeNode *node = s.buildTree(pre, in);
    EXPECT_EQ(ans1.draw(), node->draw());

    delete node;
    pre = {-1};
    in = {-1};
    TreeNode ans2{vector<int>({-1})};
    node = s.buildTree(pre, in);
    EXPECT_EQ(ans2.draw(), node->draw());
}