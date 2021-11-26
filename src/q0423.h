/*

z - 0
w - 2
u - 4
x - 6
g - 8

o - 1 ex (0,2,4)
h - 3 ex (8)
f - 5 ex (4)
s - 7 ex (6)
i - 9 ex (5, 6, 8)

*/
class Solution {
public:
    string originalDigits(string s) {
        int cnt[10] = {0};
        for(auto c : s){
            switch(c){
                case 'z': cnt[0]++; break;
                case 'o': cnt[1]++; break;
                case 'w': cnt[2]++; break;
                case 'h': cnt[3]++; break;
                case 'u': cnt[4]++; break;
                case 'f': cnt[5]++; break;
                case 'x': cnt[6]++; break;
                case 's': cnt[7]++; break;
                case 'g': cnt[8]++; break;
                case 'i': cnt[9]++; break;
            }
        }
            
        cnt[1] -= cnt[0] + cnt[2] + cnt[4];
        cnt[3] -= cnt[8];
        cnt[5] -= cnt[4];
        cnt[7] -= cnt[6];
        cnt[9] -= cnt[5] + cnt[6] + cnt[8];
            
        string ans;
        for(int i=0 ; i<10 ; i++){
            while(cnt[i]-- != 0){
                ans += '0' + i;
            }
        }
        return ans;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    EXPECT_EQ(s.originalDigits("owoztneoer"), "012");
    EXPECT_EQ(s.originalDigits("fviefuro"), "45");
}


