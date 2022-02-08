/* Solution 1: brute force */
class Solution1 {
public:
    int addDigits(int num) {
        while(num >= 10){
            int next=0, tmp = num;
            while(tmp!=0){
                next += tmp%10;
                tmp /= 10;
            }
            num = next;
        }
        return num;
    }
};

/* Solution 2: Mathmatic:
Check the cycle:

res  1  2  3  4  5  6  7  8  9
num 10 11 12 13 14 15 16 17 18
num 19 20 21 22 23 24 25 26 27

*/
class Solution {
public:
    int addDigits(int num) {
        if(num == 0)
            return 0;
        else{
            int mod9 = num % 9;
            return (mod9==0)? 9 : mod9;
        }
    }
};

TEST(Solution, test1){
    Solution s;
    EXPECT_EQ(s.addDigits(38), 2);
    EXPECT_EQ(s.addDigits(0), 0);
}