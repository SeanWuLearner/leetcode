
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        int j=0;
        string ret;
        int dash_cnt = 0;

        for(int i = s.length()-1 ; i>=0 ; i--){
            if(s[i]!= '-'){
                if(j!=0 && j % k == 0)
                    ret += "-";
                ret += toupper(s[i]);
                j++;
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

TEST(TestSolution, test1) {
    Solution s;

    EXPECT_EQ(s.licenseKeyFormatting("5F3Z-2e-9-w", 4), "5F3Z-2E9W");
    EXPECT_EQ(s.licenseKeyFormatting("2-5g-3-J", 2), "2-5G-3J");
    EXPECT_EQ(s.licenseKeyFormatting("--a-a-a-a--", 2), "AA-AA");


}