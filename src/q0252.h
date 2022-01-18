#include "vector_util.h"

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });
        int prev_end = -1;
        for(auto&& intv : intervals){
            if(prev_end > intv[0]) return false;
            prev_end = intv[1];
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    bool exp;

    q = {{0,30},{5,10},{15,20}};
    exp = false;
    EXPECT_EQ(exp, s.canAttendMeetings(q));

    q = {{7,10},{2,4}};
    exp = true;
    EXPECT_EQ(exp, s.canAttendMeetings(q));

}