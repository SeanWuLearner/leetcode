#include <queue>

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        queue<int> to_visit;
        unordered_map<int, vector<int>> inv_pre;
        vector<int> cnt_pre(numCourses);
        for(auto& pre : prerequisites){
            inv_pre[pre[1]].push_back(pre[0]);
            cnt_pre[pre[0]]++;
        }
        for(int i=0; i<numCourses ; i++)
            if(cnt_pre[i]==0)
                to_visit.push(i);

        while(to_visit.empty()!=true){
            int course = to_visit.front();
            to_visit.pop();
            res.push_back(course);
            if(inv_pre.find(course) == inv_pre.end())
                continue;
            for(auto& i : inv_pre[course]){
                cnt_pre[i]--;
                if(cnt_pre[i]==0)
                    to_visit.push(i);
            }
        }
        return (res.size()==numCourses)? res : vector<int>();
    }
};

TEST(Solution, test1) {
    Solution s;
    vector<vector<int>> pre;
    vector<int> res;


    pre = {{1,0}};
    EXPECT_EQ(s.findOrder(2, pre), vector<int>({0,1}));

    pre = {{1,0},{2,0},{3,1},{3,2}};
    res = s.findOrder(4, pre);
    EXPECT_EQ(res == vector<int>({0,2,1,3}) || res == vector<int>({0,1,2,3}), true);

}