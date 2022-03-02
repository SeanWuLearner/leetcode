/* Solution 1: simply count every 1 for each number */
class Solution1 {
public:
    int numOnes(int n){
        int count=0;
        while(n!=0){
            count++;
            n &= n-1;  //set most significant 1 to 0.
        }
        return count;
    }
    vector<int> countBits(int n) {
        vector<int> res;
        for(int i=0 ; i<=n ; i++){
            res.push_back(numOnes(i));
        }
        return res;
    }
};

/* Solution 2: buttom-up DP : toggle MSB to 1 based on previous array
    00
    01
    10
    11
    can be derived to
    100
    101
    110
    111
    Only most significant bit was set to 1.
*/
class Solution2 {
public:
    template<typename T1, typename T2>
    int min(T1 &&a, T2 &&b){
        return (a<b)? a: b;
    }
    vector<int> countBits(int n) {
        vector<int> res(1,0);
        while(res.size() < n+1){
            int loop_size = min(n+1-res.size(), res.size());
            for(int i=0 ; i<loop_size ; i++){
                res.push_back(res[i]+1);
            }
        }
        return res;
    }
};

/* Solution 3: Top-down DP
    P(x) = P(x/2) + (x % 2)
    The num_ones of x is right shift x by one , plus the LSB (might be odd or even).
*/
class Solution3 {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1; i<=n ; i++){
            res[i] = res[i>>1] + (i%2);
        }
        return res;
    }
};

/* Solution 4: DP with set MSB to 1 (with trick x & (x-1))
    P(x) = P(x & (x-1)) + 1
*/
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1; i<=n ; i++){
            res[i] = res[i & (i-1)] + 1;
        }
        return res;
    }
};



TEST(Solution, Test1){
    Solution s;
    int n;
    vector<int> exp;

    n = 2;
    exp = {0,1,1};
    EXPECT_EQ(s.countBits(n), exp);

    n = 5;
    exp = {0,1,1,2,1,2};
    EXPECT_EQ(s.countBits(n), exp);
}