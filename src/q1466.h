#include <unordered_map>

/* Solution 1 : my messy one, build edges and inv_edges  */
class Solution_my {
private:
    void correctPath(unordered_map<int, vector<int>>& orig, unordered_map<int, vector<int>>& inv,
                     int start, int& correct_cnt, vector<bool>& visited, int& visited_cnt){
        if(visited[start]) return;
        visited[start] = true;
        visited_cnt++;

        if(orig.find(start) != orig.end()){
            for(int i : orig[start]){
                if(visited[i]) continue;
                correctPath(orig, inv, i, correct_cnt, visited, visited_cnt);
            }
        }

        if(visited_cnt == visited.size()) return;

        //find correction
        if(inv.find(start) != inv.end()){
            for(int i : inv[start]){
                if(visited[i]) continue;
                correct_cnt++;
                correctPath(orig, inv, i, correct_cnt, visited, visited_cnt);
            }
        }
    }
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<int>> orig;
        unordered_map<int, vector<int>> inv;

        for(auto&& edge : connections){
            int from = edge[0], to = edge[1];
            orig[to].push_back(from);
            inv[from].push_back(to);
        }

        vector<bool> visited(n);
        int cnt = 0, visited_cnt=0;
        correctPath(orig, inv, 0, cnt, visited, visited_cnt);
        return cnt;
    }
};

/* Solution 2 : Same idea as solution1, build edges and inv_edges, but more concise
    remove the opposite route to prevent revisiting.
*/
#include <unordered_set>
class Solution_2graph {
private:
    unordered_map<int, unordered_set<int>> out, in;
    int ans;

    void dfs(int start){
        for(auto i : in[start]){
            out[i].erase(start);
            dfs(i);
        }
        for(auto i : out[start]){
            ans++;
            in[i].erase(start);
            dfs(i);
        }
    }
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        ans = 0;

        for(auto&& edge : connections){
            int from = edge[0], to = edge[1];
            out[from].insert(to);
            in[to].insert(from);
        }

        dfs(0);
        return ans;
    }
};

/* Solution 3 : Single graph array, but using negtive '-' to indicate the opposite dir.
    visited array is used here.
*/
#include <unordered_set>
class Solution {
private:
    int dfs(unordered_map<int, vector<int>>& graph, int start, vector<bool>& visited){
        int change = 0;
        for(auto&& i : graph[start]){
            int abs_i = abs(i);
            if(visited[abs_i]) continue;
            visited[abs_i] = true;
            change += dfs(graph, abs_i, visited) + ((i<0)? 1:0 );
        }
        return change;
    }
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<int>> graph;

        for(auto&& edge : connections){
            int from = edge[0], to = edge[1];
            graph[to].push_back(from);
            graph[from].push_back(-to);
        }

        vector<bool> visited(n);
        visited[0] = true;
        return dfs(graph, 0, visited);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;
    int exp, n;

    q = {{0,1},{1,3},{2,3},{4,0},{4,5}};
    n = 6;
    exp = 3;
    EXPECT_EQ(s.minReorder(n, q), exp);
}

TEST(Solution, Test2){
    Solution s;
    vector<vector<int>> q;
    int exp, n;

    q = {{1,0},{1,2},{3,2},{3,4}};
    n = 5;
    exp = 2;
    EXPECT_EQ(s.minReorder(n, q), exp);
}

TEST(Solution, Test3){
    Solution s;
    vector<vector<int>> q;
    int exp, n;

    q = {{1,0},{2,0}};
    n = 3;
    exp = 0;
    EXPECT_EQ(s.minReorder(n, q), exp);
}