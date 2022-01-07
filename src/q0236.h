
#include "tree_node.h"

/* Solution1: use a vector to record the path to p or q */
class Solution_vector {
private:
    bool getPathToNode(TreeNode *root, TreeNode *target, vector<TreeNode*> &path){
        if(root==nullptr) return false;

        path.push_back(root);
        if(root==target)
            return true;
        if(getPathToNode(root->left, target, path))
            return true;
        if(getPathToNode(root->right, target, path))
            return true;
        path.pop_back();
        return false;

    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path_p, path_q;
        getPathToNode(root, p, path_p);
        getPathToNode(root, q, path_q);

        auto it_p = path_p.begin(), it_q = path_q.begin();
        while(it_p!=path_p.end() && it_q!=path_q.end() && *it_p==*it_q){
            it_p++; it_q++;
        }
        return *(it_p-1);
    }
};

/*Solution 2: recursive
    two cases when it finds the answer:
    1. the p and q is on this nodes left and right individually.
    2. the result node is either p or q, the other is on one of its subtrees.
*/
class Solution_recursive{
private:
    TreeNode *ans = nullptr;
    /** @brief Two main purposes of this helper func.
        1. record ans node whenever the requirement meet.
        2. return whether either p or q is a descendent of root.
    *  @return 1 while either p or q is a descendent of root, otherwise return 0.
    */
    int helper(TreeNode *root, TreeNode *p, TreeNode *q){
        if(root==nullptr) return 0;
        int res = (root==p || root==q)? 1 : 0;
        res += helper(root->left, p , q);
        res += helper(root->right, p , q);
        if(res == 2)
            ans = root;
        return (res>0)? 1 : 0;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        helper(root, p, q);
        return ans;
    }
};

/* Solution 3: iterative
    s1. have a dict to look up each one's parent nodes
    s2. Then put all p's parents ptr into a set.
    s3. start to-parent travel from q, once it find out any ptr appear in the set,
        it's the lowestCommonAncestor.
*/
#include <unordered_map>
#include <unordered_set>
#include <queue>
class Solution_parentsDict{
private:
    void buildParentDict(TreeNode *root, unordered_map<TreeNode*, TreeNode*>& dict){
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode *cur = q.front();
            q.pop();

            if(cur==nullptr) continue;
            if(cur->left){
                q.push(cur->left);
                dict[cur->left] = cur;
            }
            if(cur->right){
                q.push(cur->right);
                dict[cur->right] = cur;
            }
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, TreeNode*> parent_dict;
        buildParentDict(root, parent_dict);

        //build p's parents set
        unordered_set<TreeNode*> p_parents;
        TreeNode *cur = p;
        while(cur != root){
            p_parents.insert(cur);
            cur = parent_dict[cur];
        }
        p_parents.insert(root);

        //find answer
        cur = q;
        while(cur != root){
            auto it = p_parents.find(cur);
            if(it != p_parents.end())
                return *it;
            cur = parent_dict[cur];
        }
        return root;
    }
};

/*Solution 4: Genius recursion: lowestCommonAncestor() returns
        case 1: return root if root is either p or q
        case 2: return root if p and q are returned separately by its left/right
                subtree's call to lowestCommonAncestor()
        case 3: return either left/right substree's lowestCommonAncestor() call if
                only one side return a non-null ptr.
*/
class Solution{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==nullptr || root==q || root==p) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if(left!=nullptr && right!=nullptr) return root;
        return (left==nullptr)? right:left;
    }
};


#define null NULL_TNODE

TEST(Solution, Test1){
    Solution s;
    TreeNode root{{3,5,1,6,2,0,8,null,null,7,4}};
    TreeNode *p = root.find(5);
    TreeNode *q = root.find(1);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 3);
}

TEST(Solution, Test2){
    Solution s;
    TreeNode root{{3,5,1,6,2,0,8,null,null,7,4}};
    TreeNode *p = root.find(5);
    TreeNode *q = root.find(4);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 5);
}

TEST(Solution, Test3){
    Solution s;
    TreeNode root{{1,2}};
    TreeNode *p = root.find(1);
    TreeNode *q = root.find(2);
    EXPECT_EQ(s.lowestCommonAncestor(&root, p, q)->val, 1);
}