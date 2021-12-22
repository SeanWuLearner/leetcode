class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.length();
        vector<int> res(n);
        int num_ones = 0 , acc = 0;

        //from left to right
        for(int i=0 ; i<n ; i++){
            acc += num_ones;
            res[i] = acc;
            if(boxes[i]=='1')
                num_ones++;
        }

        //from right to left
        num_ones = 0; acc = 0;
        for(int i=n-1; i>=0 ;i--){
            acc += num_ones;
            res[i] += acc;
            if(boxes[i]=='1')
                num_ones++;
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    vector<int> exp;

    q = "110";
    exp = {1,1,3};
    EXPECT_EQ(s.minOperations(q), exp);

    q = "001011";
    exp = {11,8,5,4,3,4};
    EXPECT_EQ(s.minOperations(q), exp);

}