#include <unordered_set>
#include <unordered_map>

/*Solution 1: Hash + whether we need one temperary letter */
class Solution1 {
public:
    bool canConvert(string str1, string str2) {
        char dict[26] = {0};
        unordered_set<char> occur;
        for(int i = 0 ; i < str1.length(); i++){
            char c1 = str1[i], c2 = str2[i];
            int idx1 = c1 - 'a', id2 = c2 - 'a';
            if(dict[idx1] != 0 && dict[idx1] != c2)
                return false;
            if(dict[idx1]==0){
                dict[idx1] = c2;
                occur.insert(c2);
            }
        }
        return (occur.size()==26 && str1!=str2)? false : true;
    }
};

/* Solution 2: same idea, but more concise */
class Solution {
public:
    bool canConvert(string str1, string str2) {
        if(str1==str2) return true;
        unordered_map<char, char> dict;
        for(int i=0 ; i<str1.length() ; i++){
            char c1 = str1[i], c2 = str2[i];
            auto it = dict.find(c1);
            if(it != dict.end() && it->second!=c2)
                return false;
            dict[c1] = c2;
        }
        return unordered_set(str2.begin(), str2.end()).size() < 26 ;
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.canConvert("aabcc", "ccdee"), true);
    EXPECT_EQ(s.canConvert("leetcode", "codeleet"), false);
    EXPECT_EQ(s.canConvert("abcdefghijklmnopqrstuvwxyz",
                           "bcadefghijklmnopqrstuvwxzz"), true);

}