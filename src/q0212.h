struct Trie{
    Trie *next[26];
    string s;

    Trie():s(""){
        fill(begin(next), end(next), nullptr);
    }

    void addWord(string& s){
        Trie *cur = this;
        for(auto&& c : s){
            int i = c - 'a';
            if(cur->next[i]==nullptr)
                cur->next[i] = new Trie();
            cur = cur->next[i];
        }
        cur->s= s;
    }
};

/*Solution : use Trie to elminate O(num of words) */
class Solution{
private:
    const vector<vector<int>> dirs{{1,0},{-1,0},{0,1},{0,-1}};
    Trie *trie;
    void buildTrie(vector<string>& words){
        trie = new Trie();
        for(auto&& word : words)
            trie->addWord(word);
    }
    void dfs(vector<vector<char>>& board, int x, int y, Trie *node, vector<string>& res){
        if(x<0 || x>=board.size() || y<0 || y>=board[0].size() || board[x][y]=='#') return;
        int idx = board[x][y] - 'a';
        if(node->next[idx]==nullptr) return;
        node = node->next[idx];
        if(node->s!=""){
          res.push_back(node->s);
          node->s = "";  //prevent dup result.
        }

        char keep = board[x][y];
        board[x][y] = '#';
        for(auto&& dir:dirs)
            dfs(board, x+dir[0], y+dir[1], node, res);
        board[x][y] = keep;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        buildTrie(words);
        vector<string> res;
        for(int x=0 ; x<board.size() ; x++){
            for(int y=0 ; y<board[0].size() ; y++){
                dfs(board, x, y, trie, res);
            }
        }
        return res;
    }
};
/* Time Limit Exceeded */
// class Solution {
// private:
//     const vector<vector<int>> dirs = {{1,0}, {-1,0},{0,1},{0,-1}};
//     bool helper(vector<vector<char>>& board, int x, int y, string& word, int s_idx){
//         if(s_idx==word.size()) return true;
//         if(x<0 || x>=board.size() || y<0 || y>=board[0].size()) return false;
//         if(word[s_idx] != board[x][y]) return false;
//         char keep = board[x][y];
//         board[x][y] = ' ';
//         for(auto& dir:dirs){
//             if(helper(board, x+dir[0], y+dir[1], word, s_idx+1)){
//                 board[x][y] = keep;
//                 return true;
//             }
//         }
//         board[x][y] = keep;
//         return false;
//     }
//     bool isWordInBoard(vector<vector<char>>& board, string& word){
//         for(int x=0 ; x < board.size(); x++){
//             for(int y=0 ; y<board[0].size(); y++)
//                 if(helper(board, x, y, word, 0))
//                     return true;
//         }
//         return false;
//     }
// public:
//     vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
//         vector<string> res;
//         for(auto&& word : words)
//             if(isWordInBoard(board, word))
//                 res.push_back(word);
//         return res;
//     }
// };

#include "vector_util.h"
TEST(Solution, Test1){
    Solution s;
    vector<vector<char>> board;
    vector<string> words, exp;

    board = {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    words = {"oath","pea","eat","rain"};
    exp = {"eat","oath"};
    EXPECT_EQ(sortVec(s.findWords(board, words)), sortVec(exp));
}

TEST(Solution, Test2){
    Solution s;
    vector<vector<char>> board;
    vector<string> words, exp;

    board = {{'a','b'},{'c','d'}};
    words = {"abcd"};
    exp = {};
    EXPECT_EQ(sortVec(s.findWords(board, words)), sortVec(exp));
}