#include "listnode.h"

#include <unordered_map>
// Definition for a Node.
#define NUL_PTR (INT_MAX)
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val=0) {
        val = _val;
        next = NULL;
        random = NULL;
    }

    static Node* create(vector<vector<int>>& list){
        Node head;
        Node *cur = &head;
        vector<Node*> ptr_list;

        for(auto&& l : list){
            cur->next = new Node(l[0]);
            cur = cur->next;
            ptr_list.push_back(cur);
        }

        for(int i=0 ; i<ptr_list.size() ; i++){
            if(list[i][1] == NUL_PTR) continue;
            ptr_list[i]->random = ptr_list[list[i][1]];
        }
        return head.next;
    }

    vector<vector<int>> toVector(){
        Node *cur = this;
        unordered_map<Node*, int> idxmap;
        int idx = 0;
        while(cur != nullptr){
            idxmap[cur] = idx++;
            cur = cur->next;
        }
        vector<vector<int>> res;
        cur = this;
        while(cur != nullptr){
            if(cur->random == nullptr)
                res.push_back({cur->val, NUL_PTR});
            else
                res.push_back({cur->val, idxmap[cur->random]});
            cur = cur->next;
        }
        return res;
    }
};

/*Solution 1: using hashmap to store all nodes*/
class Solution_map {
public:
    Node* copyRandomList(Node* head) {
        vector<Node*> ptr_clones;
        unordered_map<Node*, int> idxmap;

        Node clone_head;
        Node *clone_cur = &clone_head, *cur = head;
        int idx = 0;
        while(cur!=nullptr){
            clone_cur->next = new Node(cur->val);
            clone_cur = clone_cur->next;
            ptr_clones.push_back(clone_cur);
            idxmap[cur] = idx++;
            cur = cur->next;
        }
        cur = head;
        clone_cur = clone_head.next;
        while(cur != nullptr){
            if(cur->random != nullptr)
                clone_cur->random = ptr_clones[idxmap[cur->random]];
            cur = cur->next;
            clone_cur = clone_cur->next;
        }
        return clone_head.next;
    }
};

/*Solution 2: O(1) space method
    * 1st pass: loop thru next ptr, weaving the cloned node right after its source node.
    * 2nd pass: assign cloned nodes' random to the 'src_node->random->next'.
    Then, weaving all cloned nodes together.
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==nullptr) return nullptr;
        Node *cur = head;

        //weaving clone after its origin node.
        while(cur!=nullptr){
            Node *clone = new Node(cur->val);
            clone->next = cur->next;
            cur->next = clone;
            cur = clone->next;
        }

        //assign random ptrs
        cur = head;
        while(cur != nullptr){
            Node *clone = cur->next;
            if(cur->random!=nullptr)
                clone->random = cur->random->next;
            cur = clone->next;
        }

        //weaving clones together, and restore input list
        Node *res = head->next;
        cur = head;
        while(cur!=nullptr){
            Node *clone = cur->next;
            Node *next_cur = clone->next;
            cur->next = clone->next;
            clone->next = (clone->next==nullptr)? nullptr : clone->next->next;
            cur = next_cur;
        }
        return res;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    Node *qnode;

    q = {{7,NUL_PTR},{13,0},{11,4},{10,2},{1,0}};
    qnode = Node::create(q);
    EXPECT_EQ(s.copyRandomList(qnode)->toVector(), q);

    q = {{1,1},{2,1}};
    qnode = Node::create(q);
    EXPECT_EQ(s.copyRandomList(qnode)->toVector(), q);

    q = {{3,NUL_PTR},{3,0},{3,NUL_PTR}};
    qnode = Node::create(q);
    EXPECT_EQ(s.copyRandomList(qnode)->toVector(), q);

    q = {};
    qnode = Node::create(q);
    EXPECT_EQ(s.copyRandomList(qnode)->toVector(), q);
}