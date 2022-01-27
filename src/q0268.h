/* Solution 1: use the accumulative sum to subtract each num in nums. The residue is the answer.
    for acc 1 to 10 would be
        (1 + 10) * (10-1+1) / 2 = 55
*/
class Solution1 {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = (1+n) * (n) / 2;
        for(auto num : nums){
            sum -= num;
        }
        return sum;
    }
};

/* solution 2: using XOR , not easy to come out this answer.*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ret = nums.size();
        for(int i=0 ; i<nums.size() ; i++){
            ret ^= i^nums[i];
        }
        return ret;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q= {3,0,1};
    exp = 2;
    EXPECT_EQ(s.missingNumber(q), exp);

    q= {0,1};
    exp = 2;
    EXPECT_EQ(s.missingNumber(q), exp);

    q= {9,6,4,2,3,5,7,0,1};
    exp = 8;
    EXPECT_EQ(s.missingNumber(q), exp);
}
