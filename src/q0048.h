/* Solution : Linear algebra, rotate = transpose + reverse */
class Solution {
private:
    void transpose(vector<vector<int>>& matrix){
        int n = matrix.size();
        for(int i = 0 ; i < n ; i++)
            for(int j=i+1 ; j < n ; j++)
                swap(matrix[i][j], matrix[j][i]);
    }
public:
    void rotate(vector<vector<int>>& matrix) {
        transpose(matrix);
        for(int i = 0; i<matrix.size(); i++){
            reverse(matrix[i].begin(), matrix[i].end());
        }

    }
};

/* Solution : Rotate of 4 cells a time */
class Solution_rotate {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int n_2 = n / 2 , last = n-1;
        int temp;
        for(int i=0 ; i<n_2  ; i++){
            for(int j=i ; j<=last-i-1 ; j++){
                temp = matrix[i][j];
                matrix[i][j] = matrix[last-j][i];
                matrix[last-j][i] = matrix[last-i][last-j];
                matrix[last-i][last-j] = matrix[j][last-i];
                matrix[j][last-i] = temp;
            }
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q, a;

    q = {{1,2,3},{4,5,6},{7,8,9}};
    a = {{7,4,1},{8,5,2},{9,6,3}};
    s.rotate(q);
    EXPECT_EQ(q, a);

    q = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    a = {{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};
    s.rotate(q);
    EXPECT_EQ(q, a);

}