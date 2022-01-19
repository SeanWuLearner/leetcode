#include <unordered_set>
/* Solution 1: recursive dfs, delete the backward path before dive in. */
class Solution1 {
    void buildGraph(vector<vector<int>>& edges,vector<unordered_set<int>>& graph){
        for(auto&& edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
    }
    bool hasLoop(vector<unordered_set<int>>& graph, int start, vector<bool>& visited){
        if(visited[start]==true) return true;
        visited[start] = true;

        for(int next : graph[start]){
            graph[next].erase(start);
            if(hasLoop(graph, next, visited))
                return true;
        }
        return false;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n);
        buildGraph(edges, graph);

        vector<bool> visited(n);
        if(hasLoop(graph, 0, visited))
            return false;

        for(bool v : visited){
            if(v==false)
                return false;
        }
        return true;
    }
};

/* Solution 2: same idea as Solution1. But 2 modifications
    1. iterative dfs.
    2. NOT to modify the graph, just provide parent node for each iteration so
       that we can ignore the path going back.
*/
#include <stack>
class Solution2 {
private:
    void buildGraph(vector<vector<int>>& edges,vector<vector<int>>& graph){
        for(auto&& edge: edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        buildGraph(edges, graph);

        stack<pair<int,int>> stk; // start, parent
        unordered_set<int> seen;
        stk.push({0, -1});

        while(!stk.empty()){
            auto [to, from] = stk.top();
            stk.pop();

            //loop detection
            if(seen.find(to)!=seen.end())
                return false;
            seen.insert(to);

            for(int next: graph[to]){
                //skip the path to parent
                if(next == from) continue;
                stk.push({next, to});
            }
        }
        return seen.size()==n;
    }
};

/* Solution 3: advanced graph theory
1. Check whether or not there are n - 1 edges. If there's not, then return false.
2. Check whether or not the graph is fully connected. Return true if it is, false if otherwise.
*/
#include <queue>
class Solution3 {
private:
    void buildGraph(vector<vector<int>>& edges,vector<vector<int>>& graph){
        for(auto&& edge: edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size() != n-1) return false;

        vector<vector<int>> graph(n);
        buildGraph(edges, graph);

        vector<bool> seen(n);
        queue<int> q;
        int cnt_seen = 1;
        q.push(0);
        seen[0] = true;

        while(!q.empty()){
            int start = q.front();
            q.pop();
            for(int neighbor : graph[start]){
                if(!seen[neighbor]){
                    seen[neighbor] = true;
                    cnt_seen++;
                    q.push(neighbor);
                }
            }
        }
        return cnt_seen == n;
    }
};

/* Solution 4: union find */
class Solution {
private:
    vector<int> root;
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size()!=n-1) return false;

        root = vector<int>(n, -1);
        for(auto&& edge :edges){
            int x = findRoot(edge[0]);
            int y = findRoot(edge[1]);

            //loop found
            if(x == y) return false;

            //union
            root[x] = y;
        }
        return true;
    }

    int findRoot(int i){
        if(root[i] == -1) return i;
        root[i] = findRoot(root[i]);
        return root[i];
    }
};

TEST(Solution, test1){
    Solution s;
    vector<vector<int>> q;
    int n;
    bool exp;

    q = {{0,1},{0,2},{0,3},{1,4}};
    n = 5;
    exp = true;
    EXPECT_EQ(exp, s.validTree(n, q));

    q = {{0,1},{1,2},{2,3},{1,3},{1,4}};
    n = 5;
    exp = false;
    EXPECT_EQ(exp, s.validTree(n, q));

    q = {{2,0},{2,1}};
    n = 3;
    exp = true;
    EXPECT_EQ(exp, s.validTree(n, q));

    q = {{0,1},{0,4},{1,4},{2,3}};
    n = 5;
    exp = false;
    EXPECT_EQ(exp, s.validTree(n, q));
}