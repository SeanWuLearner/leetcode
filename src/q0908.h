
class MySolution {
public:
    int expressiveWords(string s, vector<string>& words) {
        int ret = 0;
        for(auto&& word : words){
            int i=0, j=0;
            int m=s.length(), n=word.length();
            while(i<m && j<n){
                if(s[i] != word[j])
                    break;
                //count repeated length on both strings
                char c = s[i];
                int start_i = i, start_j = j;
                while(i < m && c == s[i]) i++;
                while(j < n && c == word[j]) j++;
                int cnt_s = i-start_i, cnt_w = j-start_j;

                //judge whether it's stretchy according to the letter cnt.
                if((cnt_s!=cnt_w && cnt_s<3) || cnt_w > cnt_s)
                    break;
                if(i==m && j==n)
                    ret++;
            }
        }
        return ret;
    }
};

/* Same idea, two pointers, but modularized. */
class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans=0;
        for(auto&& word : words){
            if(isStretchy(s, word))
                ans++;
        }
        return ans;
    }
    bool isStretchy(string& s, string& word){
        int i=0, j=0;
        int m=s.length(), n=word.length();
        while(i<m && j<n){
            if(s[i] != word[j])
                return false;
            int cnt_s = getRepeatedLength(s, i);
            int cnt_w = getRepeatedLength(word, j);
            if((cnt_s!=cnt_w && cnt_s<3) || cnt_w > cnt_s)
                return false;
            i+=cnt_s; j+=cnt_w;
        }
        return (i==m && j==n);
    }
    int getRepeatedLength(string& s, int i){
        int j = i;
        while(j<s.length() && s[i]==s[j])
            j++;
        return j - i;
    }

};


TEST(TestSolution, test1) {
    Solution s;
    vector<string> words = {"hello", "hi", "helo"};

    EXPECT_EQ(s.expressiveWords("heeellooo", words), 1);

    words = {"zzyy","zy","zyy"};
    EXPECT_EQ(s.expressiveWords("zzzzzyyyyy", words), 3);
}
