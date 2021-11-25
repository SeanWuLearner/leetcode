class Solution {
private:
    int m,n;
public:
    void markIsland(vector<vector<char>>& grid, int i, int j){
        if(i<0 || i>=m || j<0 || j>=n) return;
        if(grid[i][j] == '1'){
            grid[i][j] = '2';
            markIsland(grid, i-1, j);
            markIsland(grid, i+1, j);
            markIsland(grid, i, j-1);
            markIsland(grid, i, j+1);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int num = 0;
        m = grid.size();
        n = grid[0].size();

        for(int i=0 ; i<m ; i++){
            for(int j=0; j<n ; j++){
                if(grid[i][j]=='1'){
                    num++;
                    markIsland(grid, i, j);
                }
            }
        }
        return num;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<vector<char>> g;

    g = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    EXPECT_EQ(s.numIslands(g), 1);

    g = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    EXPECT_EQ(s.numIslands(g), 3);

}