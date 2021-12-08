#include "listnode.h"

/* Solution: Floyd's Tortoise and Hare */
class Solution_Floyd {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head==nullptr) return nullptr;
        ListNode *fast=head, *slow=head;
        while(fast!=nullptr && fast->next!=nullptr){
            slow = slow->next;
            fast = fast->next->next;
            if(fast==slow)
                break;
        }
        if(fast == nullptr || fast->next==nullptr) return nullptr;
        ListNode *cur = head;
        while(cur != slow){
            cur = cur->next;
            slow = slow->next;
        }
        return cur;
    }
};

/* Solution: just memo all walked nodes. */
#include <unordered_set>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> dict;
        ListNode *cur = head;
        while(cur != nullptr){
            if(dict.find(cur) != dict.end())
                return cur;
            dict.insert(cur);
            cur = cur->next;
        }
        return nullptr;
    }
};

void assignNext(ListNode* l, int from, int to){
    l->find(from)->next = l->find(to);
}

TEST(Solution, Test1){
    Solution s;
    ListNode *head;

    head = ListNode::buildList({3,2,0,-4});
    assignNext(head, -4, 2);
    EXPECT_EQ(s.detectCycle(head)->val, 2);

    head = ListNode::buildList({1,2});
    assignNext(head, 2, 1);
    EXPECT_EQ(s.detectCycle(head)->val, 1);

    head = ListNode::buildList({1});
    EXPECT_EQ(s.detectCycle(head), nullptr);
}