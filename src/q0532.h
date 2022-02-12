
/* Solution 1: two-pointers

s1. sort nums
    1,1,1,3,3,4,5 , k =0

l=0, r=1,  diff=0, found, fast-forward l, then r = l+1
l=3, r=4,  diff=0, found, fast-forward l, then r = l+1
l=5, r=6, diff=1 > k, move l, if l==r, r++

Case 2:
    1,1,1,3,3,4,5, 5 , k =2

l=0, r=1, diff=0, r++;
l=0, r=2, diff=0, r++;
l=0, r=3, diff=2=k, fast-forward l, move r if needed.
l=3, r=4, diff=0, r++;
l=3, r=5, diff =1, r++
l=3, r=6, diff =2=k, fast-forward l=5
l=5, r=6, diff = 1, r++;

Case 3:
    1,1,3,3,4,7 , k =3

l=0,r=1, diff=0, fast-forward r=2
l=0,r=2, diff=2, fast-forward r=4         : less than k
l=0,r=4, diff=3, fast-forward l=2, r+1    : equal to k
l=2,r=5, diff=4, fast-forward l=4         : greater than k

*/
class Solution1 {
public:
    void fastForward(vector<int>& nums, int &i){
        int old = nums[i];
        while(++i < nums.size()){
            if(nums[i]!=old)
                break;
        }
    }
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int cnt=0, l=0, r=1;
        while(r<nums.size()){
            int diff = nums[r] - nums[l];
            if(diff>=k){
                cnt += (diff==k)? 1:0;
                fastForward(nums, l);
                r=l+1;
            }else{
                fastForward(nums, r);
            }

        }
        return cnt;
    }
};

#include <unordered_map>
class Solution{
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for(auto&& i : nums){
            freq[i]++;
        }

        int ret=0;
        for(auto&& kv : freq){
            if( k!=0 && freq.find(kv.first + k) != freq.end() )
                ret++;
            else if (k==0 && kv.second>1)
                ret++;
        }
        return ret;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int k, exp;

    q = {3,1,4,1,5};
    k=2,exp=2;
    EXPECT_EQ(exp, s.findPairs(q, k));

    q = {1,2,3,4,5};
    k=1,exp=4;
    EXPECT_EQ(exp, s.findPairs(q, k));

    q = {1,3,1,5,4};
    k=0, exp=1;
    EXPECT_EQ(exp, s.findPairs(q, k));
}