#include "tree_node.h"

/* solution1: my inefficient presum,
    child-to-parent, involve a lot of data moving.
*/
class Solution_naive {
private:
    vector<int> pathsum;
    int cnt=0;
public:
    vector<int> helper(TreeNode *root, int target){
        if(root==nullptr) return {};

        vector<int> pathL = helper(root->left, target);
        vector<int> pathR = helper(root->right, target);
        for(auto&& i : pathL){
            i += root->val;
            if(i == target)
                cnt++;
        }
        for(auto&& i : pathR){
            i += root->val;
            if(i == target)
                cnt++;
        }
        if(root->val==target){
            cnt++;
        }
        //merge two list and itself.
        pathL.push_back(root->val);
        for(auto && i : pathR)
            pathL.push_back(i);
        return pathL;
    }
    int pathSum(TreeNode* root, int targetSum) {
        helper(root, targetSum);
        return cnt;
    }
};

/* solution 2: neat and efficient presum, from top to down */
class Solution{
private:
    unordered_map<int, int> sum_cnt;
    int res;

    void acc(TreeNode* root, int targetSum, int preSum){
        if(root==nullptr) return;

        preSum += root->val;
        res += sum_cnt[preSum-targetSum];
        sum_cnt[preSum]++;
        acc(root->left, targetSum, preSum);
        acc(root->right, targetSum, preSum);
        sum_cnt[preSum]--;
    }
public:
    int pathSum(TreeNode* root, int targetSum){
        res = 0;
        sum_cnt[0] = 1;
        acc(root, targetSum, 0);
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    TreeNode root1{{10,5,-3,3,2,NULL_TNODE,11,3,-2,NULL_TNODE,1}};
    int target = 8;
    int exp = 3;
    EXPECT_EQ(s.pathSum(&root1, target), exp);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root1{{5,4,8,11,NULL_TNODE,13,4,7,2,NULL_TNODE,NULL_TNODE,5,1}};
    int target = 22;
    int exp = 3;
    EXPECT_EQ(s.pathSum(&root1, target), exp);
}

TEST(Solution, Test3){
    Solution s;
    TreeNode root1{{1}};
    int target = 1;
    int exp = 1;
    EXPECT_EQ(s.pathSum(&root1, target), exp);
}

TEST(Solution, Test4){
    Solution s;
    TreeNode root1{{1,-2,-3}};
    int target = -1;
    int exp = 1;
    EXPECT_EQ(s.pathSum(&root1, target), exp);
}