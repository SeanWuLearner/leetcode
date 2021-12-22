#include "vector_util.h"

/* Solution1: Dijkstra's algorithm */
#include <queue>
#include <algorithm>
using PII = pair<int,int>;
class Solution_Dijkstra {
private:
    vector<vector<PII>> buildGraph(vector<vector<int>>& times, int n){
        vector<vector<PII>> graph(n);
        for(auto&& v: times){
            int src=v[0]-1, dst=v[1]-1, time=v[2];
            graph[src].push_back({dst, time});
        }
        return graph;
    }
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<PII>> graph = buildGraph(times, n);
        priority_queue<PII, vector<PII>, greater<PII>> pq; // delay, vertex // greater<PII> is necessary..
        vector<int> src(n, -1), dist(n, INT_MAX);
        dist[k-1] = 0;
        vector<bool> visited(n);
        pq.push({0, k-1});

        while(!pq.empty()){
            auto top = pq.top();
            pq.pop();

            int vertex = top.second, basetime = top.first;
            if(visited[vertex])
                continue;
            visited[vertex] = true;

            for(auto&& line : graph[vertex]){
                int dst = line.first, newtime = line.second + basetime;

                if(dst == src[dst]) continue;

                if(dist[dst] > newtime){
                    src[dst] = vertex;
                    dist[dst] = newtime;
                    pq.push({newtime, dst});
                }
            }
        }
        int max_delay = *max_element(dist.begin(), dist.end());
        return (max_delay == INT_MAX)? -1: max_delay;
    }
};

/* Solution2: Bellman Ford algorithm */
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<int> dist(n+1, INT_MAX);
        dist[k] = 0;
        for(int i=1 ; i<=n ; i++){
            for(auto&& v : times){
                int src=v[0], dst=v[1], time=v[2];
                if(dist[src]!=INT_MAX && dist[dst] > dist[src] + time){
                    dist[dst] = dist[src] + time;
                }
            }
        }
        int max_dist=INT_MIN;
        for(int i=1 ; i<=n ; i++){
            max_dist = max(max_dist, dist[i]);
        }
        return (max_dist==INT_MAX)? -1 : max_dist;
    }
};

TEST(Solution, Test1){
    Solution_Dijkstra s;
    vector<vector<int>> q;
    int n, k, exp;

    q = {{2,1,1},{2,3,1},{3,4,1}};
    n = 4 ; k = 2;
    exp = 2;
    EXPECT_EQ(s.networkDelayTime(q, n, k), exp);

    q = {{1,2,1}};
    n = 2; k=1 ; exp=1;
    EXPECT_EQ(s.networkDelayTime(q, n, k), exp);

    q = {{1,2,1}};
    n=2; k=2 ; exp = -1;
    EXPECT_EQ(s.networkDelayTime(q, n, k), exp);

    q = {{4,2,76},{1,3,79},{3,1,81},{4,3,30},{2,1,47},{1,5,61},{1,4,99},{3,4,68},{3,5,46},{4,1,6},{5,4,7},{5,3,44},{4,5,19},{2,3,13},{3,2,18},{1,2,0},{5,1,25},{2,5,58},{2,4,77},{5,2,74}};
    n = 5; k=3; exp=59;
    EXPECT_EQ(s.networkDelayTime(q, n, k), exp);
}