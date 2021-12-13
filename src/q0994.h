
/* Analysis:
    - it's a topological sort like question : have to shortest distance (4-directionly)
      to the rotten oranges.
    WAY1 : start from every rotten orange, keep expanding until ....
        (1) boundary of grid.
        (2) No oranges there.
        (2) the previous distance is less than current recursion.
        Then, maximum distance of degree matrix would be the answer.
        (3) if there is still some fresh orange doesn't have a distance at all, then return -1.
*/
class Solution_Toplogical {
private:
    int m, n;
    vector<vector<int>> degrees;
    void rotting(vector<vector<int>>& grid, int x, int y, int degree){
        if(x < 0 || x >= m || y<0 || y>=n || grid[x][y]!= 1) return;
        if(degree >= degrees[x][y]) return;
        degrees[x][y] = degree;
        rotting(grid, x-1, y, degree+1);
        rotting(grid, x+1, y, degree+1);
        rotting(grid, x, y-1, degree+1);
        rotting(grid, x, y+1, degree+1);
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        degrees = vector<vector<int>>(m, vector<int>(n, INT_MAX));

        //compute degrees matrix
        for(int x = 0 ; x < m ; x++){
            for(int y=0 ; y<n ; y++){
                if(grid[x][y]==2){
                    degrees[x][y] = 0;
                    rotting(grid, x-1, y, 1);
                    rotting(grid, x+1, y, 1);
                    rotting(grid, x, y-1, 1);
                    rotting(grid, x, y+1, 1);
                }
            }
        }

        //find max degrees and if all fresh orange can be rotten.
        int min_time = 0;
        for(int x=0 ; x<m ; x++){
            for(int y=0 ; y<n ; y++){
                if(grid[x][y]==1){
                    min_time = max(min_time, degrees[x][y]);
                }
            }
        }
        return (min_time==INT_MAX)? -1 : min_time;
    }
};

/* BFS with a queue
    1. push all rotten oranges into queue. (x, y, degree)
    2. while dealing oranges in queue, if this cell has a fresh orange, then
       make rotten (modify it in place) and push all its neighbors into queue.
    3. repeat 2 until all cells are done. During this, keep tracking the max
       available degree in queue.

    Another queue arrangement is only store (x,y). But push a special token (likes (-1,-1))
    to discriminate the each rotting iteration.
*/
#include <queue>
class Solution{
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<vector<int>> q ; // x, y, degree
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};

        for(int i=0 ; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(grid[i][j] != 2) continue;

                for(auto&& dir : dirs){
                    int x = i+dir[0], y = j+dir[1];
                    q.push({x,y,1});
                }

            }
        }
        int max_elapsed = 0;

        while(!q.empty()){
            auto p = q.front();
            int i = p[0], j=p[1], deg=p[2];
            q.pop();
            if(i<0 || i>=m || j<0 || j>=n || grid[i][j]!= 1)
                continue;
            grid[i][j] = 2;
            max_elapsed = max(max_elapsed, deg);
            for(auto&& dir : dirs){
                int x=i+dir[0], y=j+dir[1];
                q.push({x,y,deg+1});
            }
        }

        for(auto&& line : grid)
            for(auto&& orange : line)
                if(orange == 1)
                    return -1;
        return max_elapsed;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q = {{2,1,1},{1,1,0},{0,1,1}} ;
    exp = 4;
    EXPECT_EQ(s.orangesRotting(q), exp);

    q = {{2,1,1},{0,1,1},{1,0,1}};
    exp = -1;
    EXPECT_EQ(s.orangesRotting(q), exp);

    q = {{0,2}};
    exp = 0;
    EXPECT_EQ(s.orangesRotting(q), exp);
}