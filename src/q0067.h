
/* Solution 1: normal adder logic */
class Solution1 {
public:
    string addBinary(string a, string b) {
        int i=a.length()-1, j=b.length()-1;
        bool carry = false;
        string res;
        while(i>=0 || j>=0){
            bool bit_a = (i<0 || a[i]=='0')? false : true;
            bool bit_b = (j<0 || b[j]=='0')? false : true;
            i--; j--;
            res += ((bit_a != bit_b) != carry)? '1':'0';
            carry = (bit_a && bit_b) || (bit_a && carry) || (bit_b && carry);
        }
        if(carry)
            res += '1';
        reverse(res.begin(), res.end());
        return res;
    }
};

/*Solution 2 : var carry can be sum and carry at the same time */
class Solution {
public:
    string addBinary(string a, string b) {
        int i=a.length()-1, j=b.length()-1;
        int carry = 0;
        string res;
        while(i>=0 || j>=0){
            if(i>=0){
                carry += a[i] - '0';
                i--;
            }
            if(j>=0){
                carry += b[j] - '0';
                j--;
            }
            res += (carry % 2)? '1' : '0';
            carry >>= 1;
        }
        if(carry)
            res += '1';
        reverse(res.begin(), res.end());
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;

    EXPECT_EQ(s.addBinary("11", "1"), "100");
    EXPECT_EQ(s.addBinary("1010", "1011"), "10101");
}