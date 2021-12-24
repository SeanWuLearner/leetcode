/* solution1 : O(1) mem, in-place
    Mark 0 existence at 1st row and col.
*/
class Solution_NoExtraMem {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool has_0_at_first_col = false, has_0_at_first_row = false;

        //figure out whether there is 0 on 1st col and row.
        for(int i = 0 ; i < m ; i++)
            if(matrix[i][0]==0){
                has_0_at_first_col = true;
                break;
            }

        for(int j = 0 ; j < n ; j++)
            if(matrix[0][j]==0){
                has_0_at_first_row = true;
                break;
            }

        //memo zeros at 1st col & row
        for(int i=1 ; i<m ; i++){
            for(int j=1 ; j<n ; j++){
                if(matrix[i][j]==0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // span zeros from col0
        for(int i=1 ; i<m ; i++){
            if(matrix[i][0]!=0) continue;
            auto&& row = matrix[i];
            fill(row.begin()+1, row.end(), 0);
        }

        //span zeros from row0
        for(int j=1 ; j<n ; j++){
            if(matrix[0][j]!=0) continue;
            for(int i=1; i<m ; i++)
                matrix[i][j] = 0;
        }

        //fill 0 to 1st row/col if needed
        if(has_0_at_first_row){
            auto&& row = matrix[0];
            fill(row.begin(), row.end(), 0);
        }
        if(has_0_at_first_col){
            for(int i=0 ; i<m ; i++)
                matrix[i][0] = 0;
        }
    }
};

/* Solution 2: additional mem, but the code is cleaner */
class Solution{
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<bool> row_memo(m), col_memo(n);

        for(int i=0 ; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(matrix[i][j]==0){
                    row_memo[i] = true;
                    col_memo[j] = true;
                }
            }
        }

        //set zeros to rows.
        for(int i=0 ; i<m ; i++){
            if(row_memo[i]==false) continue;
            fill(matrix[i].begin(), matrix[i].end(), 0);
        }

        //set zeros to rows
        for(int j=0 ; j<n ; j++){
            if(col_memo[j]==false) continue;
            for(int i=0 ; i<m ; i++)
                matrix[i][j] = 0;
        }
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    vector<vector<int>> exp;

    q = {{1,1,1},{1,0,1},{1,1,1}};
    exp = {{1,0,1},{0,0,0},{1,0,1}};
    s.setZeroes(q);
    EXPECT_EQ(q, exp);

    q = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    exp = {{0,0,0,0},{0,4,5,0},{0,3,1,0}};
    s.setZeroes(q);
    EXPECT_EQ(q, exp);
}