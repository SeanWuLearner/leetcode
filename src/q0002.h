#include "listnode.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode();
        ListNode *cur = head;
        int n1,n2,carry=0;
        while(l1!=nullptr || l2!=nullptr || carry!=0){
            if(l1!=nullptr){
                n1 = l1->val;
                l1 = l1->next;
            }else
                n1 = 0;
            if(l2!=nullptr){
                n2 = l2->val;
                l2 = l2->next;
            }else
                n2 = 0;
            int sum = n1 + n2 + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            cur = cur->next;
        }
        cur = head->next;
        delete head;
        return cur;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    ListNode *l1, *l2, *ans;

    l1 = ListNode::buildList({2,4,3});
    l2 = ListNode::buildList({5,6,4});
    ans = ListNode::buildList({7,0,8});
    EXPECT_EQ(s.addTwoNumbers(l1, l2)->equals(ans), true);

    l1 = ListNode::buildList({0});
    l2 = ListNode::buildList({0});
    ans = ListNode::buildList({0});
    EXPECT_EQ(s.addTwoNumbers(l1, l2)->equals(ans), true);

    l1 = ListNode::buildList({9,9,9,9,9,9,9});
    l2 = ListNode::buildList({9,9,9,9});
    ans = ListNode::buildList({8,9,9,9,0,0,0,1});
    EXPECT_EQ(s.addTwoNumbers(l1, l2)->equals(ans), true);
}