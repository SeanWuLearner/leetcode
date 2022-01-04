#include "tree_node.h"

/* Solution 1: diff = root->val - either max or min of its subtrees.*/
class Solution_my {
private:
    int max3(int a, int b, int c){ return max(a, max(b, c));}
    int min3(int a, int b, int c){ return min(a, min(b, c));}

    void helper(TreeNode* root, int &max_val, int &min_val, int &max_diff){
        int max_sub=INT_MIN, min_sub=INT_MAX;
        if(root->left){
            helper(root->left, max_sub, min_sub, max_diff);
        }
        if(root->right){
            helper(root->right, max_sub, min_sub, max_diff);
        }

        int val = root->val;
        max_val = max3(max_val, max_sub, val);
        min_val = min3(min_val, min_sub, val);

        if(root->left || root->right)
            max_diff = max3(max_diff, abs(val-max_sub), abs(val-min_sub));
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        if(root==nullptr) return 0;
        int max_val=INT_MIN, min_val=INT_MAX, max_diff=INT_MIN;
        helper(root, max_val, min_val, max_diff);
        return max_diff;
    }
};

/* Solution 2: same idea, but more concise, author named it postorder dfs */
class Solution_postorder{
private:
    /* return <min,max> of the given tree */
    pair<int, int> dfs(TreeNode *root, int &ans){
        if(root==nullptr) return {INT_MAX, INT_MIN};
        auto [leftmin, leftmax] = dfs(root->left, ans);
        auto [rightmin, rightmax] = dfs(root->right, ans);
        auto curmin = min({leftmin, rightmin, root->val});
        auto curmax = max({leftmax, rightmax, root->val});
        ans = max({ans, root->val - curmin, curmax - root->val});
        return {curmin, curmax};
    }
public:
    int maxAncestorDiff(TreeNode *root){
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};

/* Solution 3: Preorder , top-down method
    Algorithm: maintain curMin and curMax, then for every nodes in subtree, check if
    there is any max_diff occur
*/
class Solution_preorder{
public:
    void dfs(TreeNode *root, int max_val, int min_val, int &ans){
        if(root==nullptr) return;
        max_val = max(max_val, root->val);
        min_val = min(min_val, root->val);
        ans = max(ans, max_val - min_val);
        dfs(root->left, max_val, min_val, ans);
        dfs(root->right, max_val, min_val, ans);
    }
    int maxAncestorDiff(TreeNode *root){
        if(root==nullptr) return 0;
        int ans = 0;
        dfs(root, root->val, root->val, ans);
        return ans;
    }
};

/* Solution 4: optimize solution 3 further, ONLY update max_diff while reaching the leaf node */
class Solution {
public:
    int maxAncestorDiff(TreeNode *root, int curmin=INT_MAX, int curmax=INT_MIN){
        if(root==nullptr) return curmax - curmin;
        curmax = max(curmax, root->val);
        curmin = min(curmin, root->val);
        return max(maxAncestorDiff(root->left, curmin, curmax),
                   maxAncestorDiff(root->right, curmin, curmax));
    }
};

#define null NULL_TNODE

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{8,3,10,1,6,null,14,null,null,4,7,13}};
    int exp = 7;
    EXPECT_EQ(s.maxAncestorDiff(&root), exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{1,null,2,null,0,3}};
    int exp = 3;
    EXPECT_EQ(s.maxAncestorDiff(&root), exp);
}