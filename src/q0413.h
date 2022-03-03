/* ex. 1,2,3,4,5

ans = [1,2,3], [2,3,4], [3,4,5], [1,2,3,4], [2,3,4,5], [1,2,3,4,5]

let's say we have n elements where their difference between any two consecutive elements are the same, how many subarray can be produced from there?

when n=3, res= 1 , pick 3 from 3.
when n=4, res= 2 + 1 = 3 , 2 cases pick 3 from 4, 1 case pick 4 from 4
when n=5, res= 3 + 2 + 1= 6
when n=6, res= 4 + 3 +2 +1 = 10, can be computed with  (1 + 4) * 4 / 2 = 10 , deduced to n * (n+1) / 2

ex. 4,1,2,3,4,7,10

pre-process , diff1 = 1-4 = -3 ,  cnt = 0, res = 0;
i = 2, diff2 = 2 - 1 = 1,   diff1!=diff2 do nothing ,
    diff1 = diff2 = 1
i = 3, diff2 = 3 - 2 = 1, diff1==diff2, cnt = cnt+1 = 1
    diff1 = diff2 = 1
i = 4, diff2 = 4 - 3 = 1, diff1==diff2, cnt = cnt+1 = 2
    diff1 = diff2 = 1
i = 5, diff2 = 7 - 4 = 3, diff1!=diff2, res += getSum(cnt) = 3  , then cnt=0
    diff1 = diff2 = 3
i = 6, diff2 = 10 - 7 = 3, diff1==diff2, cnt = cnt+1 = 1

handle the remaining cnt
    res += getSum(cnt) = 4

*/

/* solution 1 : using formula to compute some */
class Solution1 {
public:
    int numOfSubseq(int i){
        return i*(i+1) / 2;
    }
    int numberOfArithmeticSlices(vector<int>& nums) {
        if(nums.size() < 3)
            return 0;
        int seq_len = 0, res = 0;
        int diff2, diff1 = nums[1] - nums[0];
        for(int i = 2 ; i<nums.size() ; i++){
            diff2 = nums[i] - nums[i-1];
            if(diff1==diff2){
                seq_len++;
            }else{
                if(seq_len!=0){
                    res += numOfSubseq(seq_len);
                    seq_len = 0;
                }
                diff1 = diff2;
            }
        }
        if(seq_len != 0)
            res += numOfSubseq(seq_len);
        return res;
    }
};

/* Solution 2 : constant space dp
    Instead of compute the num of combinations using fomula at once. We can just accumulate the current len.
*/
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int res = 0, seqlen = 0;
        for(int i=2 ; i<nums.size() ; i++){
            if(nums[i] - nums[i-1] == nums[i-1] - nums[i-2]){
                seqlen++;
                res += seqlen;
            }else{
                seqlen = 0;
            }
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {1,2,3,4};
    exp = 3;
    EXPECT_EQ(exp, s.numberOfArithmeticSlices(q));

    q = {1};
    exp = 0;
    EXPECT_EQ(exp, s.numberOfArithmeticSlices(q));
}

