#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    friend ostream& operator<<(ostream& os, ListNode* node);

    static ListNode* buildList(vector<int>&& list){
        return buildList(list);
    }

    static ListNode* buildList(vector<int>& list){
        ListNode head;
        ListNode *cur = &head;
        for(auto&& i : list){
            cur->next = new ListNode(i);
            cur = cur->next;
        }
        return head.next;
    }

    bool equals(ListNode* node) {
        ListNode *cur1 = this;
        ListNode *cur2 = node;
        while(cur1!=nullptr && cur2!=nullptr){
            if(cur1->val != cur2->val)
                return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return (cur1==nullptr && cur2==nullptr);
    }
};

ostream& operator<<(ostream& os, ListNode *node){
    while(node!=nullptr){
        os << node->val << "-> ";
        node = node->next;
    }
    return os;
}