/*Solution1: straightforward one pass */
class Solution_onePass {
public:
    bool checkRecord(string s) {
        int cnt_a = 0, cnt_l = 0;
        for(char c: s){
            if(c=='A')
                cnt_a++;
            if(c=='L'){
                cnt_l++;
                if(cnt_l>=3)
                    return false;
            }else
                cnt_l = 0;
        }
        return cnt_a < 2;
    }
};

/* Solution 2: Using regex*/
#include <regex>
class Solution {
public:
    bool checkRecord(string s) {
        regex reg(".*(A.*A|LLL).*");
        smatch m;
        return !regex_search(s, m, reg);
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    bool exp;

    q = "PPALLP";
    exp = true;
    EXPECT_EQ(s.checkRecord(q), exp);

    q = "PPALLL";
    exp = false;
    EXPECT_EQ(s.checkRecord(q), exp);

}