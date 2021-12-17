
#include "listnode.h"

/* Solution1: two pointers
    - 1st list traversing, assign the runners to the head of other list
      when they encounter null.
    - 2nd traversing, the runners will eight meet at the intersection or reach
      null at the same time.
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa = headA, *pb = headB;
        while(pa != pb){
            pa = (pa==nullptr)? headB : pa->next;
            pb = (pb==nullptr)? headA : pb->next;
        }
        return pa;
    }
};

TEST(Solution, Test1){
    Solution s;
    ListNode *l1, *l2, *exp;

    l1 = ListNode::buildList({4,1,8,4,5});
    l2 = ListNode::buildList({5,6,1});
    exp = l1->find(8);
    l2->find(1)->next = exp;
    EXPECT_EQ(exp, s.getIntersectionNode(l1, l2));

    l1 = ListNode::buildList({1,9,1,2,4});
    l2 = ListNode::buildList({3});
    exp = l1->find(2);
    l2->find(3)->next = exp;
    EXPECT_EQ(exp, s.getIntersectionNode(l1, l2));

    l1 = ListNode::buildList({2,6,4});
    l2 = ListNode::buildList({1,5});
    exp = nullptr;
    EXPECT_EQ(exp, s.getIntersectionNode(l1, l2));
}