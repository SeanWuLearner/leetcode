#include <unordered_set>

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_multiset<int> memo;
        memo.insert(0);
        int acc = 0, ans = 0;
        for(auto i : nums){
            acc += i;
            ans += memo.count(acc - k);
            memo.insert(acc);
        }
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {1,1,1};
    EXPECT_EQ(s.subarraySum(q,2), 2);

    q = {1,2,3};
    EXPECT_EQ(s.subarraySum(q, 3), 2);

    q = {1,-1,0};
    EXPECT_EQ(s.subarraySum(q, 0), 3);

    q = {1};
    EXPECT_EQ(s.subarraySum(q, 0), 0);
}
