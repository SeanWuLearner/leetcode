class Solution {
public:
    bool isAnagram(string s, string t) {
        int cnt[128]={0};
        for(auto&& c : s)
            cnt[c]++;
        for(auto&& c: t)
            cnt[c]--;

        for(int i=0 ; i<128 ; i++)
            if(cnt[i] != 0)
                return false;

        return true;
    }
};

TEST(TestSolution, test1) {
    Solution s;

    EXPECT_EQ(s.isAnagram("anagram", "nagaram"), true);
    EXPECT_EQ(s.isAnagram("rat", "car"), false);
}