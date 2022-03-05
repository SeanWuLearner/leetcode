#include "tree_node.h"
/* Solution : iterative Level order trasversal or BFS */
class Solution1 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode*, long>> q;
        q.push({root,0});
        long max_width = 0;

        while(!q.empty()){
            int size = q.size();
            long base = q.front().second;
            long min_val = INT_MAX, max_val = INT_MIN;
            while(size-->0){
                auto [node, val] = q.front(); q.pop();
                val -= base;
                min_val = min(min_val, val);
                max_val = max(max_val, val);
                max_width = max(max_width, max_val - min_val + 1);
                if(node->left)
                    q.push({node->left, val*2});
                if(node->right)
                    q.push({node->right, val*2+1});
            }
        }
        return max_width;
    }
};

/* Solution 2: DFS, need an array to memo the left most index for each level*/
class Solution {
public:
    unsigned long dfs(TreeNode *node, int level, unsigned long val, vector<unsigned long>& mins){
        if(node==nullptr) return 0;
        if(mins.size() < level + 1)
            mins.push_back(val);
        unsigned long min_val = mins[level];
        val -= min_val;
        return max({val+1,
                    dfs(node->left, level+1, val*2, mins),
                    dfs(node->right, level+1, val*2+1, mins)});
    }
    int widthOfBinaryTree(TreeNode* root) {
        vector<unsigned long> mins;
        return dfs(root, 0, 0, mins);
    }
};

#define null (NULL_TNODE)

TEST(Solution, Test1){
    Solution s;
    int exp=4;
    TreeNode root{{1,3,2,5,3,null,9}};
    EXPECT_EQ(exp, s.widthOfBinaryTree(&root));
}

TEST(Solution, Test2){
    Solution s;
    int exp=2;
    TreeNode root{{1,3,null,5,3}};
    EXPECT_EQ(exp, s.widthOfBinaryTree(&root));
}

TEST(Solution, Test3){
    Solution s;
    int exp=2;
    TreeNode root{{1,3,2,5}};
    EXPECT_EQ(exp, s.widthOfBinaryTree(&root));
}