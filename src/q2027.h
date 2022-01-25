class Solution {
public:
    int minimumMoves(string s) {
        int cnt = 0;
        for(int i=0 ; i<s.length() ; ){
            if(s[i]=='O')
                i++;
            else{
                cnt++;
                i+=3;
            }
        }
        return cnt;
    }
};

TEST(Solution, test1){
    Solution s;
    int exp;
    string q;

    q = "XXX";
    exp = 1;
    EXPECT_EQ(s.minimumMoves(q), exp);

    q = "XXOX";
    exp = 2;
    EXPECT_EQ(s.minimumMoves(q), exp);

    q = "OOOO";
    exp = 0;
    EXPECT_EQ(s.minimumMoves(q), exp);
}