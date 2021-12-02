class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for(int i = m-1 ; i>=0 ; i-- ){
            for(int j = n-1 ; j>=0 ; j--){
                if(i==m-1 && j==n-1) continue;
                int right = (j==n-1)? INT_MAX : grid[i][j+1];
                int down = (i==m-1)? INT_MAX : grid[i+1][j];
                grid[i][j] += min(right, down);
            }
        }
        return grid[0][0];
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;

    q = {{1,3,1},{1,5,1},{4,2,1}};
    EXPECT_EQ(s.minPathSum(q), 7);
    q = {{1,2,3},{4,5,6}};
    EXPECT_EQ(s.minPathSum(q), 12);
}