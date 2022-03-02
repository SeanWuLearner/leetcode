/*
case 1. the first element, update iStart = nums[0]
case 2. non-1st element, and cur element == pre_elem + 1, nothing happen, defer pushing to output.
case 3. non-1st element, cur_elem != pre_elem + 1,
            - push {iStart, pre_elem} to output
            - iStart = cur_elem
case 4. end of of iteration,
        if last_elem == istart , push mono result
        else push pair result

*/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.size()==0)
            return {};
        int start = nums[0];
        vector<string> res;
        for(int i=1 ; i<=nums.size() ; i++){
            if(i==nums.size() || nums[i] != nums[i-1]+1){
                if(nums[i-1]==start)
                    res.push_back(to_string(nums[i-1]));
                else
                    res.push_back(to_string(start) + "->" + to_string(nums[i-1]));

                if(i!=nums.size())
                    start = nums[i];
            }
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    vector<string> exp;

    q = {0,1,2,4,5,7};
    exp = {"0->2","4->5","7"};
    EXPECT_EQ(s.summaryRanges(q), exp);

    q = {0,2,3,4,6,8,9};
    exp = {"0","2->4","6","8->9"};
    EXPECT_EQ(s.summaryRanges(q), exp);
}