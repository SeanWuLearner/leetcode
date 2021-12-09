/* Solution : DFS with loop detection. */
class Solution_dfs {
private:
    bool hasLoop(vector<vector<int>>& graph, int idx, vector<bool>& visited, vector<bool>& stack){
        if(stack[idx]) return true;
        if(visited[idx]) return false;
        stack[idx] = true;
        visited[idx] = true;
        for(int neighbor : graph[idx]){
            if(hasLoop(graph, neighbor, visited, stack))
                return true;
        }
        stack[idx] = false;
        return false;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto&& pre : prerequisites){
            graph[pre[0]].push_back(pre[1]);
        }
        vector<bool> visited(numCourses);
        for(int i=0 ; i<numCourses ; i++){
            if(visited[i])
                continue;
            vector<bool> stack(numCourses);
            if(hasLoop(graph, i, visited, stack))
                return false;
        }
        return true;
    }
};

/* Solution : Topological sorting */
class Solution{
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degrees(numCourses);
        vector<vector<int>> graph(numCourses);

        for(auto&& pre : prerequisites){
            degrees[pre[0]]++;
            graph[pre[1]].push_back(pre[0]);
        }

        for(int i = 0 ; i< numCourses ; i++){ //must solve num of numCourses.
            int j;
            for(j=0 ; j<numCourses ; j++){
                if(degrees[j]==0)
                    break;
            }
            if(j==numCourses)
                return false;

            degrees[j]--; //make it won't be solved again. Brilliant trick.
            for(auto&& dep : graph[j]){
                degrees[dep]--;
            }
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q;

    q = {{1,0}};
    EXPECT_EQ(s.canFinish(2, q), true);

    q = {{1,0}, {0,1}};
    EXPECT_EQ(s.canFinish(2, q), false);

}

