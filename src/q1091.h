#include <queue>
/*

1. a dist array init with all INT_MAX
    dist[0][0] = 1

2. start from upper left,
    push all surrounding "greater" cells + "from_cell info" into queue

for each cell
    dist of cur cell = dist of from_cell + 1
    push all surrounding "greater" cells + "from_cell info" into queue

return dist of bottom-right.


must set surrounding dists first, then push them into next iter.

*/
class Solution1 {
public:

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0]==1 || grid[n-1][n-1]==1 ) return -1;

        const vector<vector<int>> DIRS{{0,1},{0,-1},{1,0},{-1,0},
                         {1,1},{1,-1},{-1,1},{-1,-1}};

        vector<vector<int>> dists(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        if(grid[0][0]==0){
            dists[0][0] = 1;
            q.push({0,0});
        }

        while(!q.empty()){
            auto [i, j] = q.front(); q.pop();

            for(auto &&dir : DIRS){
                int si = i+dir[0], sj = j+dir[1];
                if(si<0 || si>=n || sj<0 || sj>=n) continue;
                if(grid[si][sj]==1) continue;
                if(dists[si][sj] <= dists[i][j]+1) continue;
                dists[si][sj] = dists[i][j]+1;
                if(si==n-1 && sj==n-1)
                    return dists[si][sj];
                q.push({si, sj});
            }
        }

        return (dists[n-1][n-1]==INT_MAX)? -1 : dists[n-1][n-1];

    }
};

/* more optimal ver BFS

1. fill grid[][] to 1 to avoid revisit
2. store the dist into queue, then we don't need an additional dists array.
3. use two for loop [-1:1] to get rid of DIRS.
*/
struct Coord{
    int i;
    int j;
};
class Solution2 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0]==1 || grid[n-1][n-1]==1 ) return -1;

        queue<pair<Coord, int>> q;
        q.push({{0,0}, 1});

        while(!q.empty()){
            auto [coord, dist] = q.front(); q.pop();
            if(coord.i==n-1 && coord.j==n-1) return dist;

            for(int i=coord.i-1 ; i<coord.i+2 ; i++){
                for(int j=coord.j-1 ; j<coord.j+2 ; j++){
                    if(i<0 || i>=n || j<0 || j>=n) continue;

                    if(grid[i][j]!=0) continue;
                    grid[i][j]=1;
                    q.push({{i,j}, dist+1});
                }
            }
        }
        return -1;
    }
};

/*
a* search algo: more efficient, but not neccesarily find the optimal one.
    f = g + h
    where g is the real dist from src
    where h is a est cost to the dst, I use Euclidean dist here.

priority queue<tuple<double, int ,int, int, >>,
    where the data of tuple is < f, dist_to_src, coord.x, coord.y >
    Which allow us to use preferred cell to approach our solution faster.

- fill the cell to 1 to avoid revisit
- it's okay to lazily push same cell with different f val. The later one will be screen out by how we avoid revisiting.

*/
using Tuple = tuple<double, int, int, int>;
using Pair = pair<int,int>;

class Solution {
private:
    double getH(Pair cur, Pair& dst){
        return sqrt(pow(cur.first - dst.first, 2) + pow(cur.second - dst.second, 2));
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if(grid[0][0]==1 || grid[n-1][n-1]==1 ) return -1;

        priority_queue<Tuple, vector<Tuple>, greater<Tuple>> q;
        Pair dst{n-1,n-1};
        q.push({0.0, 1, 0, 0});

        while(!q.empty()){
            auto &now = q.top();
            int dist = get<1>(now);
            int i = get<2>(now), j = get<3>(now);
            if(i==n-1 && j==n-1) return dist;
            q.pop();

            grid[i][j] = 1;
            for(int ni = i-1 ; ni<=i+1 ; ni++){
                for(int nj=j-1 ;nj<=j+1; nj++){
                    if(ni < 0 || ni >= n || nj < 0 || nj>=n) continue;
                    if(grid[ni][nj]==1) continue;
                    double newf = dist+1 + getH({ni,nj}, dst);
                    q.push({newf, dist+1, ni, nj});
                }
            }
        }
        return -1;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q = {{0,1},{1,0}};
    exp = 2;
    EXPECT_EQ(exp, s.shortestPathBinaryMatrix(q));
}

TEST(Solution, Test2){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q = {{0,0,0},{1,1,0},{1,1,0}};
    exp = 4;
    EXPECT_EQ(exp, s.shortestPathBinaryMatrix(q));
}

TEST(Solution, Test3){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q = {{1,0,0},{1,1,0},{1,1,0}};
    exp = -1;
    EXPECT_EQ(exp, s.shortestPathBinaryMatrix(q));
}

TEST(Solution, Test4){
    Solution s;
    vector<vector<int>> q;
    int exp;

    q = {{0,0,1,0,0,1,0,1,0},{0,0,0,0,0,0,0,0,0},{0,1,1,0,1,1,1,1,1},{0,0,0,1,0,0,0,0,0},{1,1,0,0,0,1,0,0,0},{1,0,1,0,0,1,0,0,1},{1,1,1,1,0,0,1,0,0},{1,0,0,1,0,0,1,1,1},{0,0,0,0,0,0,0,0,0}};
    exp = 11;
    EXPECT_EQ(exp, s.shortestPathBinaryMatrix(q));
}