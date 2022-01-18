class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for(int i = 0 ; i<flowerbed.size() ; i++){
            if(flowerbed[i] == 1){
                i++;
                continue;
            }

            bool left_valid = (i==0 || flowerbed[i-1] == 0);
            bool right_valid = (i==flowerbed.size()-1 || flowerbed[i+1] == 0);
            if(left_valid && right_valid){
                n--;
                i++;
            }
            if(n<=0) return true;
        }
        return n==0;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;
    int n;
    bool exp;

    q = {1,0,0,0,1};
    n = 1;
    exp = true;
    EXPECT_EQ(exp, s.canPlaceFlowers(q, n));

    q = {1,0,0,0,1};
    n = 2;
    exp = false;
    EXPECT_EQ(exp, s.canPlaceFlowers(q, n));

    q = {1,0,0,0,1,0,0};
    n = 2;
    exp = true;
    EXPECT_EQ(exp, s.canPlaceFlowers(q, n));

    q = {1,0,1,0,1,0,1};
    n = 0;
    exp = true;
    EXPECT_EQ(exp, s.canPlaceFlowers(q, n));
}