#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> dict;
        for(int i=0 ; i<nums.size(); i++){
            auto it = dict.find(target - nums[i]);
            if(it == dict.end())
                dict.insert({nums[i], i});
            else
                return {it->second, i};
        }
        return {};
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<int> q{3,2,3};
    EXPECT_EQ(s.twoSum(q, 6), vector<int>({0,2}));
}

TEST(TestSolution, test2) {
    Solution s;
    vector<int> q{2,7,11,15};
    EXPECT_EQ(s.twoSum(q, 9), vector<int>({0,1}));
}