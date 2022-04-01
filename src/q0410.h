/* Exercise:

ex1. [ 7,2,5,10,8 ] , m=2

    [7] [2,5,10,8]  -> 7, 25
    [7,2] [5,10,8]  -> 9, 23
    [7,2,5] [10,8]  -> 14, 18
    [7,2,5,10] [8]  -> 24, 8

ex2. [1,2,3,4,5] , m=3

[1][2][3,4,5] -> 1, 2, 12
[1][2,3][4,5] -> 1, 5, 9
[1][2,3,4][5] -> 1, 9, 5

[1,2][3][4,5] -> 3, 3, 9
[1,2][3,4][5] -> 3, 7, 5

[1,2,3][4][5] -> 6, 4, 5

brute force with DP

LargestSum(array, lo, hi, m):
    if m==0:
        return 0 if lo==hi else None.


    avail_len = hi - lo;    // let's say 5 element left, want to spit m=2 parts. The longest possible of current part is 2
    for len=1 to avail_len-(m-1):
        cur_sum += array[lo+len-1]
        other_sums = LargestSum(array, lo+len, hi, m-1)
        if other_sums == None:
            continue
        max_sum = max(cur_sum, other_sums)

--->> where hi is actually not needed.
*/

#include <unordered_map>
/* Solution 1: my top-down */
class Solution1 {
private:
    int nums_size;
    unordered_map<int, int> memo;

    int getKey(int m, int idx){ return m*nums_size + idx; }

    int helper(vector<int>& nums, int idx, int m){
        if(m==0)
            return (idx==nums_size)? 0 : -1;

        int key = getKey(m, idx);
        if(memo.find(key)!=memo.end())
            return memo[key];

        int cur_sum=0, min_sum=INT_MAX;
        for(int i=idx ; i<nums_size-m+1 ; i++){
            cur_sum += nums[i];

            if(cur_sum > min_sum)
                break;

            int part_sum = helper(nums, i+1, m-1);
            if(part_sum == -1)
                continue;
            int max_sum = max(cur_sum, part_sum);
            min_sum = min(min_sum, max_sum);
        }
        memo[key] = min_sum;
        return min_sum;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        nums_size = nums.size();
        return helper(nums, 0, m);
    }
};

/* Solution 2: Solution top-down. Two differences from mine
    1. use 2D array instead of hashmap
    2. use accumulation array to compute partition sum.
*/
class Solution2 {
private:
    /* est usage : sum(1,1) = accs[2] - accs[1]
              sum(0,0) = accs[1] - accs[0] , where accs[0] = 0
              sum(0,1) = accs[2] - accs[0],
              sum(1,2) = accs[3] - accs[1]
    */
    vector<int> accs;
    int memo[1001][51];
    int nums_size;

    void initAccsArray(vector<int>& nums){
        accs.push_back(0);
        int sum = 0;
        for(int i: nums){
            sum += i;
            accs.push_back(sum);
        }
    }

    int getRangeSum(int lo, int hi){
        return accs[hi+1] - accs[lo];
    }

    int minLargestSplitSum(int idx, int m){
        if(memo[idx][m] != -1)
            return memo[idx][m];

        // base case
        if(m==1){
            return memo[idx][m] = getRangeSum(idx, nums_size-1);
        }

        int min_sum = INT_MAX;
        for(int hi=idx ; hi<=nums_size-m ; hi++){
            int cur_sum = getRangeSum(idx, hi);
            int max_sum = max(cur_sum, minLargestSplitSum(hi+1, m-1));
            min_sum = min(min_sum, max_sum);
            if(cur_sum > min_sum)
                break;
        }
        return memo[idx][m] = min_sum;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        memset(memo, -1, sizeof(memo));
        nums_size = nums.size();
        initAccsArray(nums);
        return minLargestSplitSum(0, m);
    }
};

/* Solution 3 : bottom-up DP
    same as previous solution, memo[startIdx][splits]
*/
class Solution3 {
private:
    void initAccArray(vector<int> &nums, vector<int> &accs){
        accs.push_back(0);
        int sum = 0;
        for(int i : nums){
            sum += i;
            accs.push_back(sum);
        }
    }
    int getRangeSum(vector<int> &accs, int lo, int hi){
        return accs[hi+1] - accs[lo];
    }
public:
    int splitArray(vector<int>& nums, int m) {
        vector<vector<int>> memo(m+1, vector<int>(nums.size()));

        vector<int> accs;
        initAccArray(nums, accs);

        //fill base case, split = 1
        for(int i=0 ; i < nums.size() ; i++){
            memo[1][i] = getRangeSum(accs, i, nums.size()-1);
        }

        for(int splits = 2 ; splits<=m ; splits++){
            int hi = nums.size()-splits;
            for(int lo = 0 ; lo <= hi ; lo++){
                int min_sum = INT_MAX;
                for(int idx=lo ; idx<=hi ; idx++){
                    int cur_sum = getRangeSum(accs, lo, idx);
                    int max_sum = max(cur_sum, memo[splits-1][idx+1]);
                    min_sum = min(min_sum, max_sum);
                    if(cur_sum > min_sum)
                        break;
                }
                memo[splits][lo] = min_sum;
            }
        }

        return memo[m][0];
    }
};

/* Solution 4, binary search, guess the final answer directly.
    low_bound = maximum element in array,
    high_bound = sum of all array elements.

    Binary search part:
        if minSplitsRequired(nums, cap) <= m , then the cap is too big.
        if minSplitsRequired(nums, cap) > m , then the cap is too small.
        try to find the smallest cap,
*/
class Solution {
private:
    int minSplitsRequired(vector<int>& nums, int cap){
        int res = 1;
        int sum = 0;
        for(int i: nums){
            if(sum + i > cap){
                sum = i;
                res++;
            }else{
                sum += i;
            }
        }
        return res;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        int lo = INT_MIN;
        int hi = 0;
        for(int i : nums){
            lo = max(lo, i);
            hi += i;
        }

        while(lo < hi){
            int mid = (lo + hi) / 2 ;
            if(minSplitsRequired(nums, mid) > m)
                lo = mid+1;
            else
                hi = mid;
        }
        return lo;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int m, exp;

    q = {7,2,5,10,8};
    m = 2;
    exp = 18;
    EXPECT_EQ(exp, s.splitArray(q, m));
}

TEST(Solution, Test2){
    Solution s;
    vector<int> q;
    int m, exp;

    q = {1,2,3,4,5};
    m = 2;
    exp = 9;
    EXPECT_EQ(exp, s.splitArray(q, m));
}

TEST(Solution, Test3){
    Solution s;
    vector<int> q;
    int m, exp;

    q = {1,4,4};
    m = 3;
    exp = 4;
    EXPECT_EQ(exp, s.splitArray(q, m));
}