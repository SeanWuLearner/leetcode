#include "listnode.h"
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = head;
        ListNode *prev = nullptr;
        while(cur!= nullptr){
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

TEST(Solution, Test1){
    Solution s;
    ListNode *q, *exp;

    q = ListNode::buildList({1,2,3,4,5});
    exp = ListNode::buildList({5,4,3,2,1});
    EXPECT_EQ(*s.reverseList(q), *exp);

    q = ListNode::buildList({1,2});
    exp = ListNode::buildList({2,1});
    EXPECT_EQ(*s.reverseList(q), *exp);

    q = nullptr;
    exp = nullptr;
    EXPECT_EQ(*s.reverseList(q), *exp);
}