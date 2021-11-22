class MySolution {
public:
    bool isIsomorphic(string s, string t) {
        vector<char> map(256, 0);
        vector<char> rev_map(256, 0);
        for(int i=0 ; i<s.length() ; i++){
            if(map[s[i]] != 0){
                if(map[s[i]] != t[i])
                    return false;
            }
            else{
                if(rev_map[t[i]] != 0)
                    return false;
                map[s[i]] = t[i];
                rev_map[t[i]] = s[i];
            }
        }
        return true;
    }
};

/*very neat solution, just gave ID for each mapping intead of really mapping them.*/
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        char m1[128] = {0};
        char m2[128] = {0};
        for(int i=0 ; i<s.length() ; i++){
            if(m1[s[i]] != m2[t[i]]) return false;
            m1[s[i]] = m2[t[i]] = i+1;
        }
        return true;
    }
};

TEST(TestSolution, test1) {
    Solution s;

    EXPECT_EQ(s.isIsomorphic("egg", "add"), true);
    EXPECT_EQ(s.isIsomorphic("foo", "bar"), false);
    EXPECT_EQ(s.isIsomorphic("paper", "title"), true);
    EXPECT_EQ(s.isIsomorphic("badc", "baba"), false);
}