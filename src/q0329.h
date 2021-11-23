using MatrixInt = vector<vector<int>>;
using MatrixBool = vector<vector<bool>>;
MatrixInt dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

/* Solution not accepted because time exceed limit.
  1. visisted array is not needed because it's impossible to go backward. (increasing order).
  2. the four dir coding can be improved.
*/
class Solution_NotAccepted {
public:
    bool isStart(MatrixInt& m, int i, int j){
        int left = (j-1<0)? INT_MAX : m[i][j-1];
        int up = (i-1<0)? INT_MAX : m[i-1][j];
        int right = (j+1>=m[0].size())? INT_MAX : m[i][j+1];
        int bottom = (i+1>=m.size())? INT_MAX : m[i+1][j];
        int num = m[i][j];
        return (num <= left && num <= right && num <= up && num <= bottom)? true:false;
    }
    int dfs(MatrixInt& m, MatrixBool& b, int i, int j){
        if(i<0 || i>= m.size() || j<0 || j>=m[0].size() || b[i][j]==true)
            return 0;
        b[i][j] = true;
        int longest = 0;
        int cur = m[i][j];
        // printf("m[%d][%d]=%d\n", i, j, m[i][j]);
        if(i-1 >= 0 && m[i-1][j] > cur)
            longest = max(longest, dfs(m, b, i-1, j));
        if(j-1 >= 0 && m[i][j-1] > cur)
            longest = max(longest, dfs(m, b, i, j-1));
        if(i+1 < m.size() && m[i+1][j] > cur)
            longest = max(longest, dfs(m, b, i+1, j));
        if(j+1 < m[0].size() && m[i][j+1] > cur)
            longest = max(longest, dfs(m, b, i, j+1));
        b[i][j] = false;
        // printf("i,j = (%d,%d), found longest=%d\n", i, j, 1+longest);
        return 1 + longest;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        MatrixBool visited(matrix.size(), vector<bool>(matrix[0].size()));
        int longest = INT_MIN;
        for(int i=0 ; i< matrix.size() ; i++){
            for(int j=0 ; j<matrix[0].size() ; j++){
                if(isStart(matrix, i, j) != true)
                    continue;
                // printf("m[%d][%d] = %d is a start\n", i, j, matrix[i][j]);
                longest = max(longest, dfs(matrix, visited, i, j));
            }
        }
        return longest;
    }
};
/* cache solution */
class Solution_cached_dfs {
    int m_;
    int n_;

public:
    int dfs(MatrixInt& matrix, MatrixInt& cache, int i, int j){
        if(cache[i][j] != 0)
            return cache[i][j];
        int &max_len = cache[i][j];
        for(auto& dir : dirs){
            int x = i+dir[0], y = j+dir[1];
            if(x<0 || x>=m_ || y<0 || y>=n_) continue;
            if(matrix[x][y] > matrix[i][j])
                max_len = max(max_len, dfs(matrix, cache, x, y));
        }
        return ++max_len;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m_ = matrix.size();
        n_ = matrix[0].size();
        MatrixInt cache(m_, vector<int>(n_, 0));
        int max_len = 0;

        for(int i=0 ; i<m_ ; i++)
            for(int j=0 ; j<n_ ; j++)
                max_len = max(max_len, dfs(matrix, cache, i, j));
        return max_len;
    }
};

/* Topological sorting on (Directed Acyclic Graph) DAG */
#include <queue>

class Solution {
    int m_;
    int n_;

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m_ = matrix.size();
        n_ = matrix[0].size();
        MatrixInt indeg(m_, vector<int>(n_, 0));

        for(int i=0 ; i<m_ ; i++)
            for(int j=0 ; j<n_ ; j++)
                for(auto&& dir : dirs){
                    int x = i+dir[0], y = j+dir[1];
                    if(x<0 || x>=m_ || y<0 || y>=n_) continue;
                    if(matrix[x][y] < matrix[i][j]){
                        indeg[i][j]++;
                    }

                }

        //push degree 0 nodes into queue
        queue<vector<int>> q;
        for(int i=0 ; i<m_ ; i++)
            for(int j=0 ; j<n_ ; j++)
                if(indeg[i][j] == 0)
                    q.push({i, j});

        int max_len=0;
        while(q.size() != 0){
            max_len++;
            int num_nodes = q.size();
            for(int i=0 ; i<num_nodes ; i++){
                auto coord = q.front();
                q.pop();
                for(auto&& dir : dirs){
                    int x = coord[0] + dir[0], y = coord[1] + dir[1];
                    if(x<0 || x>=m_ || y<0 || y>=n_) continue;
                    if(matrix[x][y] > matrix[coord[0]][coord[1]])
                    {
                        indeg[x][y]--;
                        if(indeg[x][y] == 0)
                            q.push({x,y});
                    }
                }
            }
        }
        return max_len;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    MatrixInt m;

    m = {{9,9,4},{6,6,8},{2,1,1}};
    EXPECT_EQ(s.longestIncreasingPath(m), 4);

    m = {{3,4,5},{3,2,6},{2,2,1}};
    EXPECT_EQ(s.longestIncreasingPath(m), 4);


    m = {{0,1},{5,5}};
    EXPECT_EQ(s.longestIncreasingPath(m), 3);
}