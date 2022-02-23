// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/*Solution 1: DFS*/
#include <unordered_map>
class Solution1 {
private:
    unordered_map<Node*, Node*> dict; //old->new
public:
    Node* cloneGraph(Node* node) {
        if(node==nullptr) return nullptr;
        auto it = dict.find(node);
        if(it!= dict.end()) return it->second;

        Node *clone = new Node(node->val);
        dict[node] = clone;
        for(Node* neighbor : node->neighbors){
            clone->neighbors.push_back(cloneGraph(neighbor));
        }
        return dict[node];
    }
};

/*Solution 2: BFS*/
#include <queue>
class Solution {
private:
    Node* addr_dict[101] = {0};
public:
    Node* cloneGraph(Node* node) {
        if(node==nullptr)
            return nullptr;
        queue<Node*> q;
        Node *ret = new Node(node->val);
        addr_dict[node->val] = ret;
        q.push(node);

        while(!q.empty()){
            Node *cur = q.front();  q.pop();
            for(auto &&n : cur->neighbors){
                if(addr_dict[n->val]==0){
                    addr_dict[n->val] = new Node(n->val);
                    q.push(n);
                }
                addr_dict[cur->val]->neighbors.push_back(addr_dict[n->val]);
            }
        }
        return ret;
    }
};