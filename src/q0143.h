#include "listnode.h"
class Solution {
private:
    void splitListByHalf(ListNode *head, ListNode **out1, ListNode **out2){
        ListNode *fast = head, *slow = head, *pre_slow = slow;
        while(fast!=nullptr && fast->next!=nullptr){
            pre_slow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre_slow->next = nullptr;
        *out1 = (fast==slow)? nullptr : head;  // fast==slow means only one node in list.
        *out2 = slow;
    }
    ListNode* reverse(ListNode *head){
        ListNode *cur = head, *prev = nullptr;
        while(cur != nullptr){
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
public:
    void reorderList(ListNode* head) {
        if(head==nullptr) return;
        ListNode *l1, *l2;
        splitListByHalf(head, &l1, &l2);
        l2 = reverse(l2);
        //weave them
        ListNode tmp;
        ListNode *res = &tmp;
        while(l1!=nullptr && l2!=nullptr){
            ListNode* l1_next = l1->next;
            ListNode* l2_next = l2->next;
            res->next = l1;
            res->next->next = l2;
            l1 = l1_next;
            l2 = l2_next;
            res = res->next->next;
        }
        if(l2 != nullptr)
            res->next = l2;
        head = res;
    }
};

TEST(Solution, Test1){
    Solution s;
    ListNode *q, *exp;

    q = ListNode::buildList({1,2,3,4});
    exp = ListNode::buildList({1,4,2,3});
    s.reorderList(q);
    EXPECT_EQ(*q, *exp);

    q = ListNode::buildList({1,2,3,4,5});
    exp = ListNode::buildList({1,5,2,4,3});
    s.reorderList(q);
    EXPECT_EQ(*q, *exp);

    q = ListNode::buildList({1});
    exp = ListNode::buildList({1});
    s.reorderList(q);
    EXPECT_EQ(*q, *exp);
}