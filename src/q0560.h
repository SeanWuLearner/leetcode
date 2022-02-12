#include <unordered_set>

/*Solution1: hashset the acc*/
class Solution1 {
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

/*Solution 2: use hashmap, <acc, freq> instead of unordered_multiset*/
#include <unordered_map>
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> memo;
        memo[0] = 1;
        int acc = 0, ans = 0;
        for(auto i : nums){
            acc += i;
            ans += memo[acc - k];
            memo[acc]++;
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
