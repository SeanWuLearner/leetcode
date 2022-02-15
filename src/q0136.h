/*Solution 1: bit manipulation, O(1) space*/
class Solution1 {
public:
    int singleNumber(vector<int>& nums) {
        int res=0;
        for(auto&& i: nums)
            res ^= i;
        return res;
    }
};
/*Solution 2: Hashset, O(n) space
    in for nums loop, insert num to hashset while not exist in hashset.
                      remove num from hashset while it exists in hashset.
*/
#include <unordered_set>
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> memo;
        for(auto &&i: nums){
            if(memo.find(i)==memo.end()){
                memo.insert(i);
            }else{
                memo.erase(i);
            }
        }
        return *memo.begin();
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {2,2,1};
    exp = 1;
    EXPECT_EQ(exp, s.singleNumber(q));

    q = {4,1,2,1,2};
    exp = 4;
    EXPECT_EQ(exp, s.singleNumber(q));

    q = {1};
    exp = 1;
    EXPECT_EQ(exp, s.singleNumber(q));
}