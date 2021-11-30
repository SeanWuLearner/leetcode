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
class Solution {
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