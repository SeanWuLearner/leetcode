/* Solution 1. plant spiral...
Exercise:
    for a 3x4 array
    go right 4
    go down 2
    go left 3
    go up 1
    go right 2
    go down 0
    so... go right/left using the same counter
          go up / down using the same counter
          stop while either one counter reach 0
*/
class Solution_PlantSpiral {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size() - 1, n = matrix[0].size() - 1;
        //manually push first line, because it is a special case
        vector<int> res(matrix[0].begin(), matrix[0].end());
        int i = 0 , j = n;
        int cnt;
        while(true){
            //go down
            if(m==0) break;
            cnt = m--;
            while(cnt-->0){
                res.push_back(matrix[++i][j]);
            }

            //go left
            if(n==0) break;
            cnt = n--;
            while(cnt-->0){
                res.push_back(matrix[i][--j]);
            }

            //go up
            if(m==0) break;
            cnt = m--;
            while(cnt-->0){
                res.push_back(matrix[--i][j]);
            }

            //go right
            if(n==0) break;
            cnt = n--;
            while(cnt-->0){
                res.push_back(matrix[i][++j]);
            }
        }
        return res;
    }
};

/* Solution 2: set 4 boundary */
class Solution_4Boundaries {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        //four boundaries
        int left = 0, right = n-1;
        int up = 0 , down = m-1;
        vector<int> res;
        while(res.size() < m*n){
            //go left
            for(int col = left; col <=right ; col++)
                res.push_back(matrix[up][col]);
            up++;

            //go down
            for(int row = up ; row <= down ; row++)
                res.push_back(matrix[row][right]);
            right--;

            //go left
            if(up > down) break;
            for(int col=right ; col >= left ; col--)
                res.push_back(matrix[down][col]);
            down--;

            //go up
            if(left > right) break;
            for(int row = down ; row >= up ; row--)
                res.push_back(matrix[row][left]);
            left++;
        }
        return res;
    }
};

/* Solution 3: mark visited while -100 <= matrix[i][j] <= 100 */
#define VISITED (INT_MIN)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        int i=0, j=0;
        while(res.size() < m*n){
            //go left
            for(; j<n && matrix[i][j]!=VISITED ; j++){
                res.push_back(matrix[i][j]);
                matrix[i][j] = VISITED;
            }
            j--; i++;

            //go down
            for(; i<m && matrix[i][j]!=VISITED ; i++){
                res.push_back(matrix[i][j]);
                matrix[i][j] = VISITED;
            }
            i--; j--;

            //go left
            if(j>=0 && matrix[i][j]==VISITED) break; //exit if the first elem is already visited
            for( ; j>=0 && matrix[i][j]!=VISITED  ; j--){
                res.push_back(matrix[i][j]);
                matrix[i][j] = VISITED;
            }
            j++; i--;

            //go up
            if(i>=0 && matrix[i][j]==VISITED) break; //exit if the first elem is already visited
            for( ; i>=0 && matrix[i][j]!=VISITED ; i--){
                res.push_back(matrix[i][j]);
                matrix[i][j] = VISITED;
            }
            i++; j++;
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    vector<int> exp;

    q = {{1,2,3},{4,5,6},{7,8,9}};
    exp = {1,2,3,6,9,8,7,4,5};
    EXPECT_EQ(s.spiralOrder(q), exp);

    q = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    exp = {1,2,3,4,8,12,11,10,9,5,6,7};
    EXPECT_EQ(s.spiralOrder(q), exp);
}