// need O(n) space
class Solution1 {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<bool> mark(nums.size()+1);
        for(int n : nums){
            mark[n] = true;
        }
        vector<int> ans;
        for(int i = 1; i<mark.size() ; i++)
            if(mark[i] == false)
                ans.push_back(i);

        return ans;
    }
};

// Swaping elements to its correct idx
class Solution2 {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for(int i=0 ; i<nums.size() ; i++){
            while(nums[i] != i+1 && nums[nums[i]-1] != nums[i]){
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        vector<int> ret;
        for(int i=0 ; i<nums.size() ; i++){
            if(nums[i] != i+1)
                ret.push_back(i+1);
        }
        return ret;
    }
};

//using mark right in nums array, can be sign or highest bit.
class Solution{
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for(int i : nums){
            int n = abs(i);
            if(nums[n-1] > 0)
                nums[n-1] = nums[n-1] * (-1);
        }
        vector<int> ret;
        for(int i=0 ; i<nums.size() ; i++){
            if(nums[i] > 0)
                ret.push_back(i+1);
        }
        return ret;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {4,3,2,7,8,2,3,1};
    EXPECT_EQ(s.findDisappearedNumbers(q), vector<int>({5,6}));

    q = {1,1};
    EXPECT_EQ(s.findDisappearedNumbers(q), vector<int>({2}));

}