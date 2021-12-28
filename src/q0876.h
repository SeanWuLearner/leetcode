#include "listnode.h"
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

TEST(Solution, Test1){
    Solution s;
    ListNode *q;
    int exp;

    q = ListNode::buildList({1,2,3,4,5});
    exp = 3;
    EXPECT_EQ(s.middleNode(q)->val, exp);

    q = ListNode::buildList({1,2,3,4,5,6});
    exp = 4;
    EXPECT_EQ(s.middleNode(q)->val, exp);
}