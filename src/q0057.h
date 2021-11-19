
/* my solution: solve it like open-close parentheses question*/
class MySolution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ret;
        int i=0,j=0;
        int m=intervals.size()*2, n=newInterval.size();
        int open = 0, prev_open = 0;
        while(i < m || j < n){
            int x = i/2, y = i%2;
            int val1 = (i>=m)? INT_MAX : intervals[x][y];
            int val2 = (j>=n)? INT_MAX : newInterval[j];
            int min_val = min(val1, val2);
            if(val1 < val2){
                open += (i%2==0)? 1 : -1;
                i++;
            }else if(val1 > val2){
                open += (j%2==0)? 1 : -1;
                j++;
            }else{
                if(i%2==0 && j%2==0)
                    open += 2;
                else if (i%2!=0 && j%2!=0)
                    open -=2;
                //open doesn't change on the other cases.

                i++; j++;
            }
            if(prev_open == 0 && open >= 1){
                ret.push_back({min_val});
            }else if(prev_open>=1 && open==0){
                ret.back().push_back(min_val);
            }
            prev_open = open;
        }
        return ret;
    }
};

/*0ms submission: 3 stages handling: before overlap, in overlap, after overlap*/
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ret;
        int idx = 0;
        while(idx < intervals.size() && intervals[idx][1] < newInterval[0]){
            ret.push_back(intervals[idx]);
            idx++;
        }

        int s = newInterval[0], e = newInterval[1];
        while(idx < intervals.size() && e >= intervals[idx][0]){
            s = min(s, intervals[idx][0]);
            e = max(e, intervals[idx][1]);
            idx++;
        }
        ret.push_back({s,e});

        while(idx < intervals.size())
        {
            ret.push_back(intervals[idx]);
            idx++;
        }
        return ret;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<vector<int>> intv;
    vector<int> new_intv;

    intv = {{1,3}, {6,9}};
    new_intv = {2,5};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{1,5}, {6,9}}));

    intv = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    new_intv = {4,8};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{1,2},{3,10},{12,16}}));

    intv = {};
    new_intv = {5,7};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{5,7}}));

    intv = {{1,5}};
    new_intv = {2,3};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{1,5}}));

    intv = {{1,5}};
    new_intv = {2,7};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{1,7}}));

    intv = {{1,5}};
    new_intv = {1,7};
    EXPECT_EQ(s.insert(intv, new_intv), vector<vector<int>>({{1,7}}));

}






