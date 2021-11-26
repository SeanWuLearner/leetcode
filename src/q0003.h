/* two pointer solution */
class Solution_TwoPointer {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int l = 0, r = 0, maxlen = 0, curlen = 0;
        int cnt[256] = {0};
        while(r < n){
            while(r < n && cnt[s[r]] == 0 ){
                cnt[s[r]]++;
                r++;
                curlen++;
            }
            maxlen = max(maxlen, curlen);
            if(r==n)
                break;

            while(l < r && cnt[s[r]]==1 ){
                cnt[s[l]]--;
                l++;
                curlen--;
            }
        }
        return maxlen;
    }
};

/* Brilliant solution
max_length = current index to the previous occurance of current letter. 
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> prev_idx(256, -1);
        int left = -1, maxlen = 0;
        for(int i=0 ; i<s.length(); i++){
            left = max(left, prev_idx[s[i]]);
            prev_idx[s[i]] = i;
            maxlen = max(maxlen, i-left);
        }
        return maxlen;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.lengthOfLongestSubstring("abcabcbb"), 3);
    EXPECT_EQ(s.lengthOfLongestSubstring("bbbbb"), 1);
    EXPECT_EQ(s.lengthOfLongestSubstring("pwwkew"), 3);
    EXPECT_EQ(s.lengthOfLongestSubstring(""), 0);
}