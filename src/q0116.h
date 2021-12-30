#include <queue>
// Definition for a Node.
#define NIL (INT_MIN)
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}

    void getAllNextHelper(Node *node, vector<int> &res){
        if(node==nullptr) return;
        res.push_back((node->next==nullptr)? NIL :node->next->val);
        getAllNextHelper(node->left, res);
        getAllNextHelper(node->right, res);
    }

    /* return all next ptrs in pre-order trasversal */
    vector<int> getAllNext(){
        vector<int> res;
        getAllNextHelper(this, res);
        return res;
    }

    static Node* buildTree(vector<int> const &v){
        if (v.size() == 0)
            return nullptr;

        queue<Node *> q;
        Node *cur, *head = new Node(v[0]);
        q.push(head);
        int idx = 1;
        while (q.empty() == false && idx < v.size())
        {
            cur = q.front();
            q.pop();

            //cout << "cur->val" << cur->val;
            if (idx < v.size() && v[idx] != NIL)
            {
                cur->left = new Node(v[idx]);
                q.push(cur->left);
                //cout << ", left=" << cur->left->val;
            }
            idx++;

            if (idx < v.size() && v[idx] != NIL)
            {
                cur->right = new Node(v[idx]);
                q.push(cur->right);
                //cout << ", right=" << cur->right->val;
            }
            idx++;
            //cout << endl;
        }
        return head;
    }
};

/* solution 1: level order trasversal */
class Solution_level {
public:
    Node* connect(Node* root) {
        if(root==nullptr) return root;
        queue<Node*> q;
        Node *cur, *prev=nullptr;
        q.push(root); q.push(nullptr);
        while(!q.empty()){
            cur = q.front();  q.pop();
            if(cur==nullptr){
                if(q.empty())
                    continue;
                prev = nullptr;
                q.push(nullptr);
                continue;
            }
            // cout << cur->val << endl;

            cur->next = prev;
            if(cur->right!=nullptr)
                q.push(cur->right);
            if(cur->left!=nullptr)
                q.push(cur->left);
            prev = cur;

        }
        return root;
    }
};

/* solution 2: using previously establish next ptr, O(1) space */
class Solution{
public:
    Node* connect(Node* root) {
        //also check children existence (checking left is enough, it's perfect tree)
        if(root==nullptr || root->left==nullptr) return root;

        root->left->next = root->right;
        root->right->next = (root->next==nullptr)? nullptr : root->next->left;

        //Either going left or going right first would work.
        connect(root->right);
        connect(root->left);
        return root;
    }
};

TEST(Solution, Test1){
    Solution s;
    Node *q;
    vector<int> exp;

    q = Node::buildTree({1,2,3,4,5,6,7});
    exp = {NIL, 3, 5, 6, NIL, 7, NIL};
    EXPECT_EQ(s.connect(q)->getAllNext(), exp);
}

TEST(Solution, Test2){
    Solution s;
    Node *q;

    q = nullptr;
    EXPECT_EQ(s.connect(q), nullptr);
}