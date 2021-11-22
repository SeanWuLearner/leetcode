class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        using VecInt = vector<int>;
        vector<VecInt> ans;

        sort(intervals.begin(), intervals.end(), [](VecInt& a, VecInt& b){
            return a[0] < b[0];
        });

        for(int i=0 ; i<intervals.size()-1 ; i++){
            vector<int> &cur = intervals[i], &next = intervals[i+1];
            if(cur[1] < next[0]){ //no overlap
                ans.push_back(cur);
            }else{
                next = {min(cur[0], next[0]), max(cur[1], next[1])};
            }
        }
        ans.push_back(intervals[intervals.size()-1]);
        return ans;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<vector<int>> q, a;

    q = {{1,3},{2,6},{8,10},{15,18}};
    a = {{1,6},{8,10},{15,18}};
    EXPECT_EQ(s.merge(q), a);

    q = {{1,4},{4,5}};
    a = {{1,5}};
    EXPECT_EQ(s.merge(q), a);
}