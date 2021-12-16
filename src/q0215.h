/* Solution1: using heap */
#include <set>
class Solution_heap {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> heap;
        for(auto&& i : nums){
            heap.insert(i);
            if(heap.size()>k)
                heap.erase(heap.begin());
        }
        return *heap.begin();
    }
};

#include "vector_util.h"
/* Solution2: quick select */
class Solution{
private:
    int partition(vector<int>& nums, int l, int r, int pivot){
        // printf("part l=%d, r=%d, pivot=%d\n", l, r, pivot);
        // printf("before part\n");
        // printVec(nums);

        swap(nums[r], nums[pivot]);
        pivot = r;

        int insert_idx=l;
        for(int i = l ; i<r ; i++){
            if(nums[i]<nums[pivot])
                swap(nums[i], nums[insert_idx++]);
        }
        swap(nums[insert_idx], nums[pivot]);
        // printf("after part, insert_idx=%d\n", insert_idx);
        // printVec(nums);
        return insert_idx;
    }
    void quickselect(vector<int>& nums, int l, int r, int k){
        if(l>=r) return;
        int pivot = (l+r) >> 1;
        // printf("select l=%d, r=%d, pivot=%d\n", l, r, pivot);
        int idx = partition(nums, l, r, pivot);
        if(idx == k) return;

        if(idx < k)
            quickselect(nums, idx+1, r, k);
        else
            quickselect(nums, l, idx-1, k);
    }
public:
    int findKthLargest(vector<int>& nums, int k){
        int n = nums.size();
        quickselect(nums, 0, n-1, n-k);
        return nums[n-k];
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int k, exp;

    q = {3,2,1,5,6,4};
    k = 2;
    exp = 5;
    EXPECT_EQ(s.findKthLargest(q, k), exp);
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    int k, exp;

    q = {3,2,3,1,2,4,5,5,6};
    k = 4;
    exp = 4;
    EXPECT_EQ(s.findKthLargest(q, k), exp);
}