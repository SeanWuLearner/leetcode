#include <string>
class Solution {
public:
    int getInt(string &s, int &i){
        if(i>=s.length()) return 0;
        string buf;
        for(;i<s.length() && s[i]!='.';i++){
            buf.push_back(s[i]);
        }
        i++;//skip "."
        return stoi(buf);
    }
    int compareVersion(string version1, string version2) {
        int i1=0, i2=0;
        while(i1<version1.length() || i2<version2.length()){
            int v1 = getInt(version1, i1);
            int v2 = getInt(version2, i2);
            if(v1<v2)
                return -1;
            if(v1>v2)
                return 1;
        }
        return 0;
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(0, s.compareVersion("1.01", "1.001"));
    EXPECT_EQ(0, s.compareVersion("1.0.0", "1.0"));
    EXPECT_EQ(-1, s.compareVersion("0.1", "1.1"));
}