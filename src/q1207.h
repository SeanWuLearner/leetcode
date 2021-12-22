#include <unordered_map>
#include <unordered_set>
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> cnts;
        for(int i : arr)
            cnts[i]++;

        unordered_set<int> memo;
        for(auto&& info: cnts){
            int cnt = info.second;
            if(memo.find(cnt)!=memo.end())
                return false;
            memo.insert(cnt);
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    bool exp;

    q = {1,2,2,1,1,3};
    exp = true;
    EXPECT_EQ(s.uniqueOccurrences(q), exp);

    q = {1,2};
    exp = false;
    EXPECT_EQ(s.uniqueOccurrences(q), exp);

    q = {-3,0,1,-3,1,1,1,-3,10,0};
    exp = true;
    EXPECT_EQ(s.uniqueOccurrences(q), exp);
}