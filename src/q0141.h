#include "listnode.h"
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast=head, *slow=head;
        while(fast!=nullptr && fast->next!=nullptr){
            fast = fast->next->next;
            slow = slow->next;
            if(slow == fast)
                return true;
        }
        return false;
    }
};

void assignNext(ListNode *l, int src, int dst){
    l->find(src)->next = l->find(dst);
}

TEST(Solution, Test1){
    Solution s;
    ListNode *q;

    q = ListNode::buildList({3,2,0,-4});
    assignNext(q, -4, 2);
    EXPECT_EQ(s.hasCycle(q), true);

    q = ListNode::buildList({1,2});
    assignNext(q, 2, 1);
    EXPECT_EQ(s.hasCycle(q), true);

    q = ListNode::buildList({1});
    EXPECT_EQ(s.hasCycle(q), false);
}