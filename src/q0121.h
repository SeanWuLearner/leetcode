/* solution iterate from right to left*/
class Solution_FromRightToLeft {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1) return 0;

        int max_profit = 0;
        int highest = prices[prices.size()-1];
        for(int i=prices.size()-2 ; i>=0 ; i--){
            if(prices[i] > highest){
                highest = prices[i];
            }else{
                max_profit = max(max_profit, highest - prices[i]);
            }
        }
        return max_profit;
    }
};

/* solution iterate from left to right*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int minPrice = INT_MAX;
        int tmp;
        for (int &i : prices) {
            if (i < minPrice) {
                minPrice = i;
            } else if ((tmp = (i - minPrice)) > maxProfit) {
                maxProfit = tmp;
            }
        }
        return maxProfit;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> m;

    m = {7,1,5,3,6,4};
    EXPECT_EQ(s.maxProfit(m), 5);

    m = {7,6,4,3,1};
    EXPECT_EQ(s.maxProfit(m), 0);
}