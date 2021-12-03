class Solution_My {
private:
    int m, n;
    vector<vector<bool>> visited;
    bool dfs(vector<vector<char>>& board, int i, int j, string word, int w_idx ){
        if(w_idx == word.length()) return true;
        if(i<0 || i>=m || j<0 || j>=n) return false;
        if(visited[i][j]==true) return false;
        if(board[i][j] != word[w_idx]) return false;
        visited[i][j] = true;
        if(dfs(board, i-1, j, word, w_idx+1)) return true;
        if(dfs(board, i+1, j, word, w_idx+1)) return true;
        if(dfs(board, i, j-1, word, w_idx+1)) return true;
        if(dfs(board, i, j+1, word, w_idx+1)) return true;
        visited[i][j] = false;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(); n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n));
            for(int i=0 ; i<m ; i++)
                for(int j=0 ; j<n ;j++)
                    if(dfs(board, i, j, word, 0))
                        return true;
        return false;
    }
};
/*solution that doesn't need visited array*/
class Solution {
private:
    int m, n;
    bool dfs(vector<vector<char>>& board, int i, int j, string word, int w_idx ){
        if(w_idx == word.length()) return true;
        if(i<0 || i>=m || j<0 || j>=n) return false;
        if(board[i][j] != word[w_idx]) return false;
        if(board[i][j]=='#') return false;
        board[i][j] = '#';
        if(dfs(board, i-1, j, word, w_idx+1)) return true;
        if(dfs(board, i+1, j, word, w_idx+1)) return true;
        if(dfs(board, i, j-1, word, w_idx+1)) return true;
        if(dfs(board, i, j+1, word, w_idx+1)) return true;
        board[i][j] = word[w_idx];
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(); n = board[0].size();
        for(int i=0 ; i<m ; i++)
            for(int j=0 ; j<n ;j++)
                if(dfs(board, i, j, word, 0))
                    return true;
        return false;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<char>> grid;

    grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    EXPECT_EQ(s.exist(grid, "ABCCED"), true);

    grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    EXPECT_EQ(s.exist(grid, "SEE"), true);

    grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    EXPECT_EQ(s.exist(grid, "ABCB"), false);

}