class MySolution {
public:
    void reverse(vector<int>& nums, int start){
        int end = nums.size()-1;
        int num_loop = (end - start + 1) / 2;
        for(int i=0 ; i<num_loop ; i++){
            swap(nums[start+i], nums[end-i]);
        }
    }
    
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i;
        //find decreasing
        for(i = n-2 ; i>=0 ; i--)
            if(nums[i] < nums[i+1]) break;
        
        if(i==-1){
            reverse(nums, 0);
        }else{
            int j;
            //find the elem that just greater than nums[i]
            for(j = n-1; j>=0 ; j--){
                if(nums[j] > nums[i]){
                    swap(nums[i], nums[j]);
                    break;
                }
            }
            if(j==-1)
                reverse(nums, 0);
            else
                reverse(nums, i+1);
        }
        
    }
};

/* neat code from Solution*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i;
        //find decreasing
        for(i = n-2 ; i>=0 ; i--)
            if(nums[i] < nums[i+1]) break;
        
        if(i != -1){
            int j;
            for(j=n-1; j>=0 ; j--)
                if(nums[j] > nums[i]) break;
            swap(nums[j], nums[i]);
        }
        reverse(nums.begin()+i+1, nums.end());
    }
};


#include "vector_util.h"
TEST(Solution, Test1){
    Solution s;
    vector<int> nums;
    set<vector<int>> np;

    nums = {1,2,3,4};
    for(int i = 0 ; i<32 ; i++){
        // cout << "t " << i << endl;
        np.insert(nums);
        printVec(nums);
        s.nextPermutation(nums);
    }
    cout << "NP = " << np.size() << endl;
}