
/* Time Limit Exceeded:
    divide and conquer :
    1. Find the regional minimum.
    2. MaxArea would be max(
            A. height[idx_min] * regional_width,
            B. DivideAndConquer result on left,
            C. DivideAndConquer result on right
            )
*/
class Solution_DivAndConq {
public:
    int largestRectangleArea(vector<int>& heights) {
        return getMaxArea(heights, 0, heights.size());
    }
    int getMaxArea(vector<int>& heights, int start, int end){
        if(end <= start) return 0;
        int idx_min = start;
        for(int i = start+1 ; i < end ; i++)
            if(heights[i] < heights[idx_min])
                idx_min = i;
        return max(heights[idx_min] * (end - start),
            max(getMaxArea(heights, start, idx_min), getMaxArea(heights, idx_min+1, end))
        );
    }
};

/* one-pass solution with stack.
    The values tracking by the stack would only be inceasing, that way, we can assure the next top() would defintely
    lesser than current top(). So we the area between them would be heights[q.top()] * (q.top() - q.next_top()-1)
    if we store idx of heights in stack.
*/
#include <stack>
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.size() == 0) return 0;
        stack<int> stk;
        stk.push(-1); // for the sake of compute left-most marginal area.
        stk.push(0);
        int max_area = 0;
        for(int i=1 ; i<heights.size() ; i++){
            while(stk.top()!=-1 && heights[i] < heights[stk.top()]){
                int cur_height = heights[stk.top()];
                stk.pop();
                int cur_width = i - stk.top() - 1;
                max_area = max(max_area, cur_height * cur_width);
            }
            stk.push(i);
        }
        int end = heights.size();
        while(stk.top()!=-1){
            int cur_height = heights[stk.top()];
            stk.pop();
            int cur_width = end - stk.top() - 1;
            max_area = max(max_area, cur_height * cur_width);
        }
        return max_area;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {2,1,5,6,2,3};
    EXPECT_EQ(s.largestRectangleArea(q), 10);

    q = {2,4};
    EXPECT_EQ(s.largestRectangleArea(q), 4);

    q = {2,1,2};
    EXPECT_EQ(s.largestRectangleArea(q), 3);
}