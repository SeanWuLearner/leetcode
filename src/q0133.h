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

#include <unordered_map>
class Solution {
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