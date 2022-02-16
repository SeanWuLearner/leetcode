#include "listnode.h"

/*Solution 1: iterative, give the last node of last iteration, then you can link
                swapped list. */
class Solution1 {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy, *prev=&dummy;
        dummy.next = head;
        ListNode *cur=head, *cur2;
        while(cur!=nullptr){
            cur2 = cur->next;
            if(cur2==nullptr)
                break;
            prev->next = cur2;
            cur->next = cur2->next;
            cur2->next = cur;
            //prepare for next loop.
            prev = cur;
            cur = cur->next;
        }
        return dummy.next;
    }
};

/*Solution 2: recursive*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==nullptr || head->next==nullptr)
            return head;

        ListNode *second = head->next;
        head->next = swapPairs(second->next);
        second->next = head;
        return second;
    }
};

TEST(Solution, Test1){
    Solution s;
    auto q = ListNode::buildList({1,2,3,4});
    auto exp = ListNode::buildList({2,1,4,3});
    EXPECT_EQ(*s.swapPairs(q), *exp);
}

TEST(Solution, Test2){
    Solution s;
    EXPECT_EQ(s.swapPairs(nullptr), nullptr);
}
TEST(Solution, Test3){
    Solution s;
    auto q = ListNode::buildList({1});
    auto exp = ListNode::buildList({1});
    EXPECT_EQ(*s.swapPairs(q), *exp);
}
