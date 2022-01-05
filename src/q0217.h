/* Solution 1: sort it first */
class Solution_sort {
public:
    bool containsDuplicate(vector<int>& nums) {
        if(nums.size()==0) return true;
        sort(nums.begin(), nums.end());
        int prev = nums[0];
        for(int i=1; i<nums.size(); i++){
            if(prev == nums[i])
                return true;
            prev = nums[i];
        }
        return false;
    }
};


#include <unordered_set>
/* Solution 2: hash set*/
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if(nums.size()==0) return true;
        unordered_set<int> sets;
        for(auto&& i : nums){
            if(sets.find(i)!=sets.end())
                return true;
            sets.insert(i);
        }
        return false;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    bool exp;

    q= {1,2,3,1};
    exp = true;
    EXPECT_EQ(s.containsDuplicate(q), exp);

    q = {1,2,3,4};
    exp = false;
    EXPECT_EQ(s.containsDuplicate(q), exp);

    q = {1,1,1,3,3,4,3,2,4,2};
    exp = true;
    EXPECT_EQ(s.containsDuplicate(q), exp);
}