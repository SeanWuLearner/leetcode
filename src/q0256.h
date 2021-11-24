class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        for(int i=1 ; i < n ; i++){
            costs[i][0] += min(costs[i-1][1], costs[i-1][2]);
            costs[i][1] += min(costs[i-1][0], costs[i-1][2]);
            costs[i][2] += min(costs[i-1][0], costs[i-1][1]);
        }
        return min(costs[n-1][0], min(costs[n-1][1], costs[n-1][2]));
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<vector<int>> costs;

    costs = {{17,2,17},{16,16,5},{14,3,19}};
    EXPECT_EQ(s.minCost(costs), 10);

    costs = {{7,6,2}};
    EXPECT_EQ(s.minCost(costs), 2);

}
