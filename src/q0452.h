#include "vector_util.h"
/*
Exercise: it seems the greedy should work.

([0,0]), ([1, 2], [2,3]), ([3,4], [3,5])  -> 3 shots
([0,0]), ([1, 2]), ([2,3], [3,4], [3,5])  -> 3 shots
([0,1], [1, 2]), ([2,3], [3,4], [3,5])  -> 2 shots
*/
/* Solution 1: my naive union greedy method, actually, overlap[0] is useless.. */
class Solution1 {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        });
        vector<int> overlap = points[0];
        int cnt = 1;
        for(int i = 1 ; i < points.size() ; i++){
            if(overlap[1] >= points[i][0]){
                //can merge
                overlap[0] = max(overlap[0], points[i][0]);
                overlap[1] = min(overlap[1], points[i][1]);
            }else{
                cnt++;
                overlap = points[i];
            }
        }
        return cnt;
    }
};

/* Solution 2: greedy, sort the end*/
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });
        int pos = points[0][1];
        int cnt = 1;
        for(int i = 1 ; i < points.size() ; i++){
            if(pos >= points[i][0])
                continue;

            cnt++;
            pos = points[i][1];
        }
        return cnt;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q =  {{10,16},{2,8},{1,6},{7,12}};
    exp = 2;
    EXPECT_EQ(s.findMinArrowShots(q), exp);

    q = {{1,2},{3,4},{5,6},{7,8}};
    exp = 4;
    EXPECT_EQ(s.findMinArrowShots(q), exp);

    q = {{1,2},{2,3},{3,4},{4,5}};
    exp = 2;
    EXPECT_EQ(s.findMinArrowShots(q), exp);
}