class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int cnt[128] = {0};
        int desire_letter_cnt = 0;
        for(auto c:p){
            if(cnt[c] ==0)
                desire_letter_cnt++;
            cnt[c]++;
        }

        vector<int> res;
        for(int i=0 ; i<s.length() ; i++){
            if(i >= p.length()){ // need to shift window's left boundary.
                char rm_c = s[i-p.length()];
                if(cnt[rm_c] == 0){
                    desire_letter_cnt++;
                }
                cnt[rm_c]++;
            }

            //shift right boundary
            char c = s[i];
            cnt[c]--;
            if(cnt[c] == 0){
                desire_letter_cnt--;
                if(desire_letter_cnt == 0)
                    res.push_back(i-(p.length()-1));
            }
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.findAnagrams("cbaebabacd", "abc"), vector<int>({0,6}));
    EXPECT_EQ(s.findAnagrams("abab", "ab"), vector<int>({0,1,2}));
}