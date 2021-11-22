class Solution {
public:
    int maxArea(vector<int>& height) {
        int i=0, j=height.size()-1;
        int max_area = 0;
        while(i<j){
            max_area = max(max_area, min(height[i], height[j]) * (j-i) );
            if(height[i] < height[j])
                i++;
            else
                j--;
        }
        return max_area;
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {1,8,6,2,5,4,8,3,7};
    EXPECT_EQ(s.maxArea(q), 49);

    q = {1,1};
    EXPECT_EQ(s.maxArea(q), 1);

    q = {4,3,2,1,4};
    EXPECT_EQ(s.maxArea(q), 16);

    q = {1,2,1};
    EXPECT_EQ(s.maxArea(q), 2);
}