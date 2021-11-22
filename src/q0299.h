/* two pass solution */
class MySolution {
public:
    string getHint(string secret, string guess) {
        vector<int> cnt_s(10), cnt_g(10);
        int a=0, b=0;
        for(int i=0 ; i<secret.length() ; i++){
            if(secret[i] == guess[i])
                a++;
            else{
                cnt_s[secret[i]-'0']++;
                cnt_g[guess[i]-'0']++;
            }
        }
        for(int i=0 ; i<10 ; i++){
            b += min(cnt_s[i], cnt_g[i]);
        }
        ostringstream oss;
        oss << a << "A" << b << "B";
        return oss.str();
    }
};

/* one pass solution, genius just using ++/-- to record secret/guess traveled.*/
class Solution {
public:
    string getHint(string secret, string guess) {
        vector<int> cnt(10);
        int a=0, b=0;
        for(int i=0 ; i<secret.length() ; i++){
            if(secret[i] == guess[i])
                a++;
            else{
                if(cnt[secret[i]-'0'] < 0) b++;
                if(cnt[guess[i]-'0'] > 0) b++;
                cnt[secret[i] - '0']++;
                cnt[guess[i] - '0']--;
            }
        }

        ostringstream oss;
        oss << a << "A" << b << "B";
        return oss.str();
    }
};

TEST(TestSolution, test1) {
    Solution s;

    EXPECT_EQ(s.getHint("1807", "7810"), "1A3B");
    EXPECT_EQ(s.getHint("1123", "0111"), "1A1B");
    EXPECT_EQ(s.getHint("1", "0"), "0A0B");
    EXPECT_EQ(s.getHint("1", "1"), "1A0B");
}
