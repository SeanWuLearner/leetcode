
/* Solution: Search space reduction */
class Solution_spatial_search {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int i = m-1, j = 0;
        // printf("m=%d, n=%d, i=%d, j=%d\n", m, n, i, j);
        while(i>=0 && j<n){
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] < target)
                j++;
            else
                i--;
        }
        return false;
    }
};

/* divide and conquer solution:
    Divide whole matrix by half each time.
    Remove rectangular that:
    1. its top-left cell is greater than target.
    2. its bottom-right cell is less than target.
    Then, recursive the other two possible rectangulars.
*/
class Solution {
private:
    struct Rec{
        int x1; //top-left
        int y1;
        int x2; //bottom-right
        int y2;
    };
    bool findInRec(vector<vector<int>>& matrix, Rec& rec, int target){
        if(rec.y1 > rec.y2) return false;
        int mid_y = (rec.y1 + rec.y2) / 2;
        int i;
        // handle rec1
        for(i = rec.x1 ; i <= rec.x2 ; i++){
            if(matrix[i][mid_y] == target) return true;
            if(matrix[i][mid_y] > target) break;
        }
        Rec rec1{rec.x1, mid_y+1, i-1, rec.y2};
        if(findInRec(matrix, rec1, target) == true)
            return true;
        Rec rec2{i, rec.y1, rec.x2, mid_y-1};
        return findInRec(matrix, rec2, target);
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        Rec rec{0, 0, m-1, n-1};
        return findInRec(matrix, rec, target);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;

    q = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    EXPECT_EQ(s.searchMatrix(q, 5), true);

    q = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    EXPECT_EQ(s.searchMatrix(q, 20), false);
}