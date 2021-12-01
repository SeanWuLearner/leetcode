class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int l = 0, r = (m*n)-1;
        int i, j, mid;
        // printf("m=%d, n=%d\n", m, n);
        while(l<r){
            mid = (l+r)/2;
            i = mid / n; j = mid % n;
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] < target)
                l = mid + 1;
            else
                r = mid;
        }
        i = l/n; j = l%n;
        return matrix[i][j]==target;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<vector<int>> q;

    q = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    EXPECT_EQ(s.searchMatrix(q, 3), true);

    q = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    EXPECT_EQ(s.searchMatrix(q, 13), false);
}