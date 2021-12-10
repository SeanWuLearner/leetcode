
/*Solution1:
    1. put the number to the right place, ex 1 should be at idx 0, 2 should be at idx 1, etc..
    2. check the first missing one.
*/
class Solution_bucketSort {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        //clean up, less and equal to 0 and greater than n
        for(auto& i : nums){
            if(i<0 || i>n)
                i = 0;
        }

        for(int i=0; i<n ; i++){
            while(nums[i]!=i+1 && (nums[i]-1 >=0) && (nums[i]-1 < n) && nums[i] != nums[nums[i]-1])
                swap(nums[i], nums[nums[i]-1]);
        }
        for(int i=0; i<n ; i++){
            if(nums[i]!= i+1)
                return i+1;
        }
        return n+1;
    }
};
/* Solution 2: Hash the existence info inplace with neg sign '-'. */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int i, n = nums.size();

        //check if 1 exists first, because we need to use 1 as our special token.
        for(i=0; i<n ; i++){
            if(nums[i] == 1)
                break;
        }
        if(i==n) return 1;

        //clean up, less and equal to 0 and greater than n
        for(auto& i : nums){
            if(i<=0 || i>n)
                i = 1;
        }

        //embed neg sign at the corresponding idx.
        for(auto& i : nums){
            int idx = abs(i) - 1;
            if(nums[idx] > 0)
                nums[idx] = -nums[idx];
        }

        for(int i=0; i< n ; i++){
            if(nums[i] > 0 )
                return i+1;
        }
        return n+1;
    }
};
/*Solution3: embed the num existence with plus n to that indexed num
    Very close to Solution2, no need to code it again.
*/

TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {1,2,0};
    EXPECT_EQ(s.firstMissingPositive(q), 3);

    q = {3,4,-1,1};
    EXPECT_EQ(s.firstMissingPositive(q), 2);

    q = {7,8,9,11,12};
    EXPECT_EQ(s.firstMissingPositive(q), 1);
}