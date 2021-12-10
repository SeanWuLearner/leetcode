#include "listnode.h"

/* Solution1: Priority Queue */
class Solution_PQ {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head;
        ListNode *cur = &head;
        multimap<int, int> heap;

        //for each list, push one node into heap
        for(int i = 0 ; i< lists.size() ; i++){
            if(lists[i] != nullptr)
                heap.insert({lists[i]->val, i});
        }

        while(!heap.empty()){
            int idx = heap.begin()->second;
            heap.erase(heap.begin());
            cur->next = lists[idx];
            lists[idx] = lists[idx]->next;
            cur = cur->next;
            if(lists[idx] != nullptr)
                heap.insert({lists[idx]->val, idx});
        }
        return head.next;
    }
};
/* Solution2: Divide and conquer */
/*
    (l0, l1), (l2, l3), (l4, l5), l6
     l0        l2        l4       l6
     l0                  l4
     l0
*/
class Solution {
private:
    ListNode* merge2Lists(ListNode* l1, ListNode* l2){
        ListNode head;
        ListNode *cur = &head;
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
        if(l1 != nullptr)
            cur->next = l1;
        if(l2 != nullptr)
            cur->next = l2;
        return head.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists){
        int n = lists.size();
        for(int intv = 1 ; intv < n ; intv <<= 1){
            for(int i=0 ; i+intv < n ; i+= intv<<1){
                lists[i] = merge2Lists(lists[i], lists[i+intv]);
            }
        }
        return (n==0)? nullptr : lists[0];
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<ListNode*> l;
    ListNode *exp;

    l = {
        ListNode::buildList({1,4,5}),
        ListNode::buildList({1,3,4}),
        ListNode::buildList({2,6}),
    };
    exp = ListNode::buildList({1,1,2,3,4,4,5,6});
    EXPECT_EQ(s.mergeKLists(l)->equals(exp), true);

    l = {};
    exp = nullptr;
    EXPECT_EQ(s.mergeKLists(l), exp);

    l = {{}};
    exp = nullptr;
    EXPECT_EQ(s.mergeKLists(l), exp);
}