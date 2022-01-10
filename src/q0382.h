#include "listnode.h"

/* Solution 1: rand() index in array.*/
class Solution1 {
private:
    vector<int> nums;
public:
    Solution1(ListNode* head) {
        while(head!=nullptr){
            nums.push_back(head->val);
            head = head->next;
        }
    }

    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

/*Solution2: Reservior Sampling*/
class Solution {
private:
    ListNode *head;
public:
    Solution(ListNode* head):head(head) {
    }

    int getRandom() {
        //fill reservior array
        int ret = head->val;

        //iter to replace element in reservior array.
        ListNode *cur=head->next;
        int i = 2;
        while(cur!=nullptr){
            int j = rand() % i;
            if(j < 1) ret = cur->val;
            cur = cur->next;
            i++;
        }
        return ret;
    }
};

bool InArray(int a, vector<int>& arr){
    for(auto&& i : arr){
        if(i==a)
            return true;
    }
    return false;
}

TEST(Solution, Test1){
    vector<int> arr{{1,2,3}};
    ListNode *l = ListNode::buildList(arr);
    Solution s(l);

    EXPECT_EQ(InArray(s.getRandom(), arr), true);
    EXPECT_EQ(InArray(s.getRandom(), arr), true);
    EXPECT_EQ(InArray(s.getRandom(), arr), true);
    EXPECT_EQ(InArray(s.getRandom(), arr), true);
    EXPECT_EQ(InArray(s.getRandom(), arr), true);
}