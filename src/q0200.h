/* Normal count and expansion answer */
class Solution_MarkAndCnt {
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


/* Union-find solution */
class UnionFind{
private:
    int col_size;
    int count;
    vector<int> parent;
    vector<int> rank;
public:
    int get1dIdx(int r, int c){
        return r * col_size + c;
    }
    UnionFind(vector<vector<char>>& grid){
        count = 0;
        col_size = grid[0].size();
        for(int i=0 ; i<grid.size() ; i++){
            for(int j=0 ; j<grid[0].size() ; j++){
                if(grid[i][j] == '1'){
                    count++;
                    parent.push_back(get1dIdx(i, j));
                    rank.push_back(1);
                }else{
                    parent.push_back(-1);
                    rank.push_back(0);
                }
            }
        }
    }

    int find(int r, int c){
        int i = get1dIdx(r,c);
        while(i != parent[i]){
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return parent[i];
    }

    void Union(int r1, int c1, int r2, int c2){
        int root1 = find(r1,c1), root2 = find(r2,c2);
        if(root1 == root2)
            return;

        if(rank[root1] > rank[root2]){
            parent[root2] = root1;
            rank[root1] += rank[root2];
        }else{
            parent[root1] = root2;
            rank[root2] += rank[root1];
        }
        count--;
    }
    int getCount(){
        return count;
    }
};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        UnionFind uf(grid);

        for(int i=0 ; i<m ; i++){
            for(int j=0; j<n ; j++){
                if(grid[i][j]=='1'){
                    if(i>0 && grid[i-1][j]=='1') uf.Union(i,j, i-1,j);
                    if(j>0 && grid[i][j-1]=='1') uf.Union(i,j, i,j-1);
                    if(i<m-1 && grid[i+1][j]=='1') uf.Union(i,j, i+1,j);
                    if(j<n-1 && grid[i][j+1]=='1') uf.Union(i,j, i,j+1);
                }
            }
        }
        return uf.getCount();
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