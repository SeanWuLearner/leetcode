#include <unordered_set>

class Solution_UsingSet {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> dic;
        for(int n : nums)
            dic.insert(n);
        int max_cnt = 0;
        for(int n : nums){
            if(dic.count(n-1) != 0)
                continue;
            int cnt = 1, i=n+1;
            while(dic.count(i++) != 0)
                cnt++;
            max_cnt = max(max_cnt, cnt);
        }
        return max_cnt;
    }
};

/*sort it at the beginning, the weird thing is, this is faster than using set...*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        sort(nums.begin(), nums.end());

        int count = 1, max_cnt=1;
        for(int i=1 ; i<nums.size(); i++){
            if(nums[i-1] + 1 == nums[i])
                count++;
            else if(nums[i-1] == nums[i])
                continue;
            else
                count = 1;
            max_cnt = max(max_cnt, count);
        }
        return max_cnt;
    }
};

TEST(TestSolution, test1) {
    MySolution s;
    vector<int> q;

    q = {100,4,200,1,3,2};
    EXPECT_EQ(s.longestConsecutive(q), 4);

    q = {0,3,7,2,5,8,4,6,0,1};
    EXPECT_EQ(s.longestConsecutive(q), 9);
}
