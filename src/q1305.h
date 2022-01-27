#include "tree_node.h"
/*Solution 1: sort out tree into vector via in-order trasversal (recursive),
    after that, we just weaving two vectors into one.
*/
class Solution1 {
private:
    void treeToVec(TreeNode *cur, vector<int>& res){
        if(cur == nullptr) return;
        treeToVec(cur->left, res);
        res.push_back(cur->val);
        treeToVec(cur->right, res);
    }
    vector<int> weave(vector<int>& v1, vector<int>& v2){
        vector<int> res;
        int i1=0, i2=0;
        while(i1<v1.size() && i2<v2.size()){
            if(v1[i1] < v2[i2]){
                res.push_back(v1[i1++]);
            }else{
                res.push_back(v2[i2++]);
            }
        }
        if(i1<v1.size())
            copy(v1.begin()+i1, v1.end(), back_inserter(res));
        if(i2<v2.size())
            copy(v2.begin()+i2, v2.end(), back_inserter(res));
        return res;
    }
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> vec1, vec2;
        treeToVec(root1, vec1);
        treeToVec(root2, vec2);
        return weave(vec1, vec2);
    }
};

/*Solution 2: create a class that has a getNext() return next val in in-order trasversal of the
              given tree. Then we just need to repeatly appending the smaller one between two tree
              to our result vector.
*/
#include <stack>
class InOrderDumper{
private:
    TreeNode *cur;
    stack<TreeNode*> stk;
public:
    InOrderDumper(TreeNode *root):cur(root){}
    TreeNode* getNext(){
        if(cur==nullptr && stk.empty()) return nullptr;

        while(cur != nullptr){
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();

        TreeNode *ret = cur;
        cur = cur->right;
        return ret;
    }
};
class Solution2{
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        InOrderDumper d1(root1), d2(root2);
        TreeNode *cur1 = d1.getNext(), *cur2 = d2.getNext();

        vector<int> res;
        while(cur1!=nullptr || cur2!=nullptr){
            if(cur1==nullptr || (cur2!=nullptr && cur2->val <= cur1->val)){
                res.push_back(cur2->val);
                cur2 = d2.getNext();
            }else{
                res.push_back(cur1->val);
                cur1 = d1.getNext();
            }
        }
        return res;
    }
};

/* Solution 3: still do it iteratively, but we don't need to create an extra class to do this...*/
class Solution{
public:
    void pushLeft(stack<TreeNode*> &s, TreeNode *cur){
        while(cur!=nullptr){
            s.push(cur);
            cur = cur->left;
        }
    }
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode*> s1, s2;
        pushLeft(s1, root1);
        pushLeft(s2, root2);

        vector<int> res;
        while(!s1.empty() || !s2.empty()){
            stack<TreeNode*> *s;
            s = (s1.empty() || (!s2.empty() && s2.top()->val <= s1.top()->val))? &s2 : &s1;
            TreeNode *cur = s->top(); s->pop();
            res.push_back(cur->val);
            pushLeft(*s, cur->right);
        }
        return res;
    }
};

#define null (NULL_TNODE)
TEST(Solution, test1){
    Solution s;
    TreeNode t1{{2,1,4}};
    TreeNode t2{{1,0,3}};
    vector<int> exp = {0,1,1,2,3,4};
    EXPECT_EQ(exp, s.getAllElements(&t1, &t2));
}

TEST(Solution, test2){
    Solution s;
    TreeNode t1{{1,null,8}};
    TreeNode t2{{8,1}};
    vector<int> exp = {1,1,8,8};
    EXPECT_EQ(exp, s.getAllElements(&t1, &t2));
}