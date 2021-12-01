#ifndef TREENODE_H
#define TREENODE_H

#include <queue>
#include <climits>
#include <vector>

using namespace std;

#define NULL_TNODE (INT_MIN)

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

    /* give v in level order traversal seq, where the INT_MIN element is equivalent
       to NULL.This is exact the same representation used in LeetCode. */
    TreeNode(const vector<int> v): left(NULL), right(NULL)
    {
        if (v.size() == 0)
            return;

        queue<TreeNode *> q;
        TreeNode *cur;
        int idx = 1;
        this->val = v[0];
        q.push(this);
        while (q.empty() == false && idx < v.size())
        {
            cur = q.front();
            q.pop();

            //cout << "cur->val" << cur->val;
            if (idx < v.size() && v[idx] != NULL_TNODE)
            {
                cur->left = new TreeNode(v[idx]);
                q.push(cur->left);
                //cout << ", left=" << cur->left->val;
            }
            idx++;

            if (idx < v.size() && v[idx] != NULL_TNODE)
            {
                cur->right = new TreeNode(v[idx]);
                q.push(cur->right);
                //cout << ", right=" << cur->right->val;
            }
            idx++;
            //cout << endl;
        }
    }
    ~TreeNode(){
        deinitHelper(this->left);
        deinitHelper(this->right);
    }
    void deinitHelper(TreeNode *node){
        if(node == nullptr) return;
        deinitHelper(node->left);
        deinitHelper(node->right);
        delete node;
    }
    void draw (){
        string str;
        drawHelper(str, "", "");
        cout << str << endl;
    }
private:
    void drawHelper(string& buf, string prefix, string child_prefix){
        buf += prefix;
        buf += to_string(val);
        buf += "\n";
        vector<TreeNode*> childs{right, left};

        for(auto&& c : childs){
            if(c==nullptr)
                continue;
            if(c!= childs[childs.size()-1])
                c->drawHelper(buf, child_prefix + "├── ", child_prefix+"│   ");
            else
                c->drawHelper(buf, child_prefix + "└── ", child_prefix+"    ");
        }
    }
};

#endif
