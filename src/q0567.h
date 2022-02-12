
/* Solution s1: sliding window
an array cnt[26] to keep the occurance of each letter.
an int to_meet to track if all 26 elements of cnt is zero or not.
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> cnt(26,0);
        int to_meet = 0;

        //build matching pattern
        for(char c: s1){
            int i = c-'a';
            if(cnt[i]==0)
                to_meet++;
            cnt[i]++;
        }

        //sliding window, right index decreasing the cnt, left index increasing the cnt.
        for(int r=0 ; r<s2.length() ; r++){
            int l = r - s1.length();
            int i = s2[r] - 'a';
            cnt[i]--;
            if(cnt[i]==0)
                to_meet--;
            if(l >= 0){
                int j = s2[l] - 'a';
                if(cnt[j]==0)
                    to_meet++;
                cnt[j]++;
            }
            if(to_meet==0)
                return true;
        }
        return false;
    }
};

TEST(Solution, Test1){
    Solution s;
    string s1, s2;
    bool exp;

    s1 = "ab";
    s2 = "eidbaooo";
    exp = true;
    EXPECT_EQ(s.checkInclusion(s1,s2), exp);

    s1 = "ab";
    s2 = "eidboaoo";
    exp = false;
    EXPECT_EQ(s.checkInclusion(s1,s2), exp);

}