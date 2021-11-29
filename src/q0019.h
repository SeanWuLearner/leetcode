#include "listnode.h"

class MySolution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode();
        dummy->next = head;
        ListNode *slow=dummy, *fast=dummy;
        while(fast->next != nullptr){
            fast = fast->next;
            if(n != 0)
                n--;
            else
                slow = slow->next;
        }
        if(slow->next != nullptr){
            ListNode *toBeRm = slow->next;
            slow->next = toBeRm->next;
            delete toBeRm;
        }
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

/* cleaner solution from discussion*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode();
        dummy->next = head;
        ListNode *slow=dummy, *fast=dummy;

        //one more gap than previous ans. Better call.
        for(int i=1; i<=n+1 ; i++)
            fast = fast->next;

        while(fast != nullptr){
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *toBeRm = slow->next;
        slow->next = toBeRm->next;
        delete toBeRm;
        ListNode *ans = dummy->next;
        delete dummy;
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    ListNode *q = ListNode::buildList({1,2,3,4,5});
    ListNode *a = ListNode::buildList({1,2,3,5});

    EXPECT_EQ(s.removeNthFromEnd(q, 2)->equals(a), true);

    q = ListNode::buildList({1});
    EXPECT_EQ(s.removeNthFromEnd(q, 1), nullptr);

    q = ListNode::buildList({1,2});
    a = ListNode::buildList({1});
    EXPECT_EQ(s.removeNthFromEnd(q, 1)->equals(a), true);

    q = ListNode::buildList({1,2});
    a = ListNode::buildList({2});
    EXPECT_EQ(s.removeNthFromEnd(q, 2)->equals(a), true);

}