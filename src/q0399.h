#include <unordered_map>
#include <unordered_set>

void dump_dict(unordered_map<string, vector<pair<string, double>>> graph){
    for(auto& m:graph){
        cout << m.first << ":"<< endl;
        for(auto& v:m.second){
            cout <<"    ";
            printf("(%s, %f)\n", v.first.c_str(), v.second);
        }
    }
}

/* DFS solution */
class Solution_dfs {
public:
    unordered_map<string, vector<pair<string, double>>> graph;

    bool dfs(string* dividend, string* divisor, double &quotient, unordered_set<string>& visited){
        if(graph.count(*dividend)==0)
            return false;
        if(*divisor == *dividend){
            quotient = 1;
            return true;
        }
        visited.insert(*dividend);
        for(auto& v : graph[*dividend]){
            if(v.first==*divisor){
                quotient = v.second;
                return true;
            }

            if(visited.count(v.first)!=0)
                continue;

            double sub_quo;
            if(dfs(&v.first, divisor, sub_quo, visited)==true){
                quotient = v.second * sub_quo;
                return true;
            }

        }
        visited.erase(*dividend);
        return false;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        //build graph
        for(int i = 0 ; i<equations.size(); i++){
            auto &v = equations[i];
            graph[v[0]].push_back(make_pair(v[1], values[i]));
            graph[v[1]].push_back(make_pair(v[0], 1/values[i]));
        }
        // dump_dict(graph);
        //compute ans
        vector<double> ans;
        for(auto q: queries){
            double quo;
            unordered_set<string> visited;
            if(dfs(&q[0], &q[1], quo, visited)==true)
                ans.push_back(quo);
            else
                ans.push_back(-1);
        }
        return ans;
    }
};

/* union find solution*/
using RootMap = unordered_map<string, string>;
using WeightMap = unordered_map<string, double>;
class Solution {
private:
    RootMap root;
    WeightMap weight;
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        for(int i=0 ; i < equations.size(); i++)
            _union(equations[i][0], equations[i][1], values[i]);
        vector<double> ans;
        for(auto&& q : queries){
            // fix for geting unknown/unknown.
            if(root.find(q[0])==root.end() || root.find(q[1])==root.end()){
                ans.push_back(-1.0);
                continue;
            }
            string r1 = find(q[0]);
            string r2 = find(q[1]);
            if(r1!=r2){
                ans.push_back(-1.0);
                continue;
            }
            ans.push_back(weight[q[0]] / weight[q[1]]);
        }
        return ans;
    }
    void _union(string& dividend, string& divisor, double& quotient){
        string root_dividend = find(dividend);
        string root_divisor = find(divisor);
        root[root_dividend] = root_divisor;
        weight[root_dividend] = weight[divisor] * quotient / weight[dividend];
    }

    string find(string node){
        //create new node here.
        if(root.find(node) == root.end()){
            root[node] = node;
            weight[node] = 1.0;
            return node;
        }
        //path compression
        while(root[node] != node){
            weight[node] *= weight[root[node]];
            root[node] = root[root[node]];
            node = root[node];
        }
        return node;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<vector<string>> eq, q;
    vector<double> vals, ans;

    eq = {{"a","b"},{"b","c"}};
    vals = {2.0,3.0};
    q = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    ans = {6.00000,0.50000,-1.00000,1.00000,-1.00000};
    EXPECT_EQ(s.calcEquation(eq, vals, q), ans);
}

TEST(TestSolution, test2) {
    Solution s;
    vector<vector<string>> eq, q;
    vector<double> vals, ans;

    eq = {{"a","b"},{"b","c"},{"bc","cd"}};
    vals = {1.5,2.5,5.0};
    q = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};
    ans = {3.75000,0.40000,5.00000,0.20000};
    EXPECT_EQ(s.calcEquation(eq, vals, q), ans);
}

TEST(TestSolution, test3) {
    Solution s;
    vector<vector<string>> eq, q;
    vector<double> vals, ans;

    eq = {{"a","b"}};
    vals = {0.5};
    q = {{"a","b"},{"b","a"},{"a","c"},{"x","y"}};
    ans = {0.50000,2.00000,-1.00000,-1.00000};
    EXPECT_EQ(s.calcEquation(eq, vals, q), ans);
}