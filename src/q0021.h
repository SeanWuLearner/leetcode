#include "listnode.h"
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode head;
        ListNode *cur = &head;
        while(list1 != nullptr && list2 != nullptr){
            if(list1->val < list2->val){
                cur->next = list1;
                list1 = list1->next;
            }
            else{
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if(list1)
            cur->next = list1;
        if(list2)
            cur->next = list2;

        return head.next;
    }
};

TEST(Solution, Test1){
    Solution s;
    ListNode *l1, *l2, *exp;

    l1 = ListNode::buildList({1,2,4});
    l2 = ListNode::buildList({1,3,4});
    exp = ListNode::buildList({1,1,2,3,4,4});
    EXPECT_EQ(true, s.mergeTwoLists(l1, l2)->equals(exp));

    l1 = l2 = exp = nullptr;
    EXPECT_EQ(nullptr, s.mergeTwoLists(l1, l2));

    l1 = nullptr;
    l2 = ListNode::buildList({0});
    exp = ListNode::buildList({0});
    EXPECT_EQ(true, s.mergeTwoLists(l1, l2)->equals(exp));
}