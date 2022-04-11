/* Solution 1: coord transformation */
class Solution1 {
private:
    int row_shift_;
    int col_shift_;
    int size_row_;
    int size_col_;
    void initVar(int size_row, int size_col, int k){
        size_row_ = size_row;
        size_col_ = size_col;
        row_shift_ = (k / size_col) % size_row;
        col_shift_ = k % size_col;
        // printf("initvar rowshift=%d, colshift=%d\n", row_shift_, col_shift_);
    }

    pair<int,int> getNewCoord(int row, int col){
        int new_col = col + col_shift_;
        int carry = 0;
        if (new_col >= size_col_){
            carry = 1;
            new_col %= size_col_;
        }
        int new_row = (row + row_shift_ + carry) % size_row_;
        return {new_row, new_col};
    }
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        initVar(m, n, k);

        for(int i=0; i<m ; i++){
            for(int j=0; j<n ; j++){
                auto [new_i, new_j] = getNewCoord(i, j);
                // printf("(%d,%d) = (%d,%d)\n", new_i, new_j, i, j);
                ans[new_i][new_j] = grid[i][j];
            }
        }
        return ans;
    }
};

/* Solution 2: don't do coord transform, use push_back to add elem in order
    so the last k elem will be added first.
*/
class Solution2 {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        vector<vector<int>> ans;
        int m = grid.size(), n = grid[0].size();
        int start = m*n - (k%(m*n));
        for(int i=start ; i<start+m*n ; i++){
            int r= (i/n) % m, c=i%n;
            if((i-start)%n==0)
                ans.push_back({});
            ans.back().push_back(grid[r][c]);
        }
        return ans;
    }
};

/* Solution 3: reverse method, treat it like 1D array

orig
  1 2 3 4 5 6 7
shift 3
  5 6 7 1 2 3 4

reverse all
  7 6 5 4 3 2 1
reverse first k, and reverse the rest
  [5 6 7] [1 2 3 4]

*/
class Solution {
public:
    void reverse(vector<vector<int>>& grid, int start, int end){
        int n = grid[0].size();
        for(;start<end ; start++, end--){
            int r1=start/n, c1=start%n;
            int r2=end/n, c2=end%n;
            swap(grid[r1][c1], grid[r2][c2]);
        }
    }
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        k = k %(m*n);
        reverse(grid, 0, m*n-1);
        reverse(grid, 0, k-1);
        reverse(grid, k, m*n-1);
        return grid;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q, exp;
    int k;

    q = {{1,2,3},{4,5,6},{7,8,9}};
    k=1;
    exp ={{9,1,2},{3,4,5},{6,7,8}};
    EXPECT_EQ(exp, s.shiftGrid(q, k));

    q = {{3,8,1,9},{19,7,2,5},{4,6,11,10},{12,0,21,13}};
    k=4;
    exp ={{12,0,21,13},{3,8,1,9},{19,7,2,5},{4,6,11,10}};
    EXPECT_EQ(exp, s.shiftGrid(q, k));

    q = {{1,2,3},{4,5,6},{7,8,9}};
    k=9;
    exp ={{1,2,3},{4,5,6},{7,8,9}};
    EXPECT_EQ(exp, s.shiftGrid(q, k));
}



