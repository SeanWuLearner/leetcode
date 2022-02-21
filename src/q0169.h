/*Soluton 1: Booyer-Moore Voting algo*/
class Solution1 {
public:
    int majorityElement(vector<int>& nums) {
        int major = nums[0], cnt=1;
        for(int i=1 ; i<nums.size() ; i++){
            if(nums[i]==major)
                cnt++;
            else
                cnt--;

            if(cnt<0){
                major = nums[i];
                cnt = 1;
            }
        }
        return major;
    }
};

/*Soluton 2: Hashmap*/
#include <unordered_map>
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int target_cnt = nums.size() / 2 + 1;
        unordered_map<int, int> counter;
        for(auto &&i : nums){
            counter[i]++;
            if(counter[i] >= target_cnt)
                return i;
        }
        return 0;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {3,2,3};
    exp = 3;
    EXPECT_EQ(s.majorityElement(q), exp);

    q = {2,2,1,1,1,2,2};
    exp = 2;
    EXPECT_EQ(s.majorityElement(q), exp);
}