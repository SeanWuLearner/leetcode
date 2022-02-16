#include "listnode.h"

/* Solution 1: recursive merge-sort*/
class Solution1 {
public:
    ListNode* merge(ListNode *l1, ListNode *l2){
        ListNode head, *cur = &head;

        while(l1!=nullptr || l2!=nullptr){
            int i1 = (l1==nullptr)? INT_MAX : l1->val;
            int i2 = (l2==nullptr)? INT_MAX : l2->val;
            if(i1<i2){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        return head.next;
    }
    pair<ListNode*, ListNode*> splitByHalf(ListNode *l){
        ListNode *pre1=l, *out1=l, *out2=l;
        /* handle len(list) == 1 */
        if(l->next==nullptr){
            return {l, nullptr};
        }
        while(out2!=nullptr && out2->next!=nullptr){
            pre1 = out1;
            out1 = out1->next;
            out2 = out2->next->next;
        }
        pre1->next = nullptr;
        return {l, out1};
    }
    ListNode* sortList(ListNode* head) {
        if(head==nullptr || head->next==nullptr)
            return head;

        auto [l1, l2] = splitByHalf(head);
        auto res1 = sortList(l1);
        auto res2 = sortList(l2);
        auto ans = merge(res1, res2);
        return ans;
    }
};

/* Solution 2: iterative merge-sort, bottom-up*/
class Solution {
public:
    ListNode* merge(ListNode *l1, ListNode *l2, ListNode *prev_end){
        ListNode *cur = prev_end;
        while(l1!=nullptr && l2!=nullptr){
            if(l1->val < l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = (l1==nullptr)? l2 : l1;
        //fast-forward cur the the last node of the merged list.
        while(cur->next != nullptr){
            cur = cur->next;
        }
        return cur;
    }
    /* break the list with length n and return the ptr of the node after the list */
    ListNode* split(ListNode *node, int n){
        ListNode *cur = node, *prev=nullptr;
        for(int i=0 ; i<n && cur!=nullptr ; i++){
            prev = cur;
            cur = cur->next;
        }
        if(prev!=nullptr){
            prev->next=nullptr;
        }
        return cur;
    }
    int getListLen(ListNode *l){
        int len=0;
        while(l!=nullptr){
            len++;
            l = l->next;
        }
        return len;
    }
    ListNode* sortList(ListNode* head) {
        int len = getListLen(head);

        ListNode dummy(99), *prev_end;
        dummy.next = head;

        for(int step=1 ; step<len ; step <<=1 ){
            ListNode *cur = dummy.next;
            prev_end = &dummy;
            while(cur!=nullptr){
                ListNode *left = cur;
                ListNode *right = split(left, step);
                cur = split(right, step);
                auto new_end = merge(left, right, prev_end);
                prev_end = new_end;
            }
        }
        return dummy.next;
    }
};

TEST(Solution, Test1){
    Solution s;
    auto q = ListNode::buildList({4,2,1,3});
    auto exp = ListNode::buildList({1,2,3,4});
    EXPECT_EQ(*exp, *s.sortList(q));
}

TEST(Solution, Test2){
    Solution s;
    auto q = ListNode::buildList({-1,5,3,4,0});
    auto exp = ListNode::buildList({-1,0,3,4,5});
    EXPECT_EQ(*exp, *s.sortList(q));
}
