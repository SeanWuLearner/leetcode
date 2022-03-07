/*Solution 1: recursion */
class Solution1 {
public:
    Node* cloneTree(Node* root) {
        if(root==nullptr) return nullptr;
        Node *clone = new Node(root->val);
        for(Node* child:root->children){
            clone->children.push_back(cloneTree(child));
        }
        return clone;
    }
};

/*Solution 2: iterative BFS*/
class Solution {
public:
    Node* cloneTree(Node* root) {
        if(root==nullptr) return nullptr;
        Node *res = new Node(root->val);
        queue<pair<Node*,Node*>> q;
        q.push({root, res});
        while(!q.empty()){
            auto [cur, clone] = q.front(); q.pop();
            for(auto&& child : cur->children){
                clone->children.push_back(new Node(child->val));
                q.push({child, clone->children.back()});
            }
        }
        return res;
    }
};

/*extra: solution works for graph, avoid loop.*/
class Solution3 {
public:
    Node* get(unordered_map<Node*,Node*> &clones, Node *key){
        if(clones.find(key)==clones.end()){
            clones[key] = new Node(key->val);
        }
        return clones[key];
    }
    Node* cloneTree(Node* root) {
        if(root==nullptr) return nullptr;
        unordered_set<Node*> visited;
        unordered_map<Node*, Node*> clones;
        queue<Node*> q;
        q.push(root);
        clones[root] = new Node(root->val);
        while(!q.empty()){
            Node* cur = q.front(); q.pop();
            if(visited.find(cur)!=visited.end())
                continue;
            visited.insert(cur);
            Node* clone = clones[cur];
            for(Node* child : cur->children){
                q.push(child);
                clone->children.push_back(get(clones, child));
            }
        }
        return clones[root];
    }
};