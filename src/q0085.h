
/* dp that memo the continues 1 on the row.*/
class Solution_dp_v1 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();

        //fill dp array.
        vector<vector<int>> dp(m, vector<int>(n));
        for(int i = m-1; i>=0 ; i--){
            int acc = 0;
            for(int j = n-1 ; j>=0 ; j--){
                if(matrix[i][j] == '1')
                    acc++;
                else
                    acc = 0;
                dp[i][j] = acc;
            }
        }

        //compute max area.
        int res = 0;
        for(int i=0 ; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(matrix[i][j] != '1') continue;
                int width = dp[i][j];
                int k = i;
                while(k<m){
                    if(matrix[k][j] != '1') break;
                    width = min(width, dp[k][j]);
                    res = max(res, width * (k-i+1));
                    k++;
                }
            }
        }
        return res;
    }
};

/* same idea dp solution, but more precise */
class Solution_dp_v2 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n));
        int res = 0;
        for(int i=0 ; i<m ; i++){
            for(int j=0 ; j<n ; j++){
                if(matrix[i][j]!='1') continue;
                int width;
                width = dp[i][j] = (j==0)? 1 : dp[i][j-1] + 1;
                for(int k=i ; k>=0 ; k--){
                    width = min(width, dp[k][j]);
                    res = max(res, width * (i-k+1));
                }
            }
        }
        return res;
    }
};

/* Using dp + stack, to further speed up the runtime to O(mn),
    Refer to q0084 for the way of using stack.
*/
#include <stack>
class Solution {
private:
    int findMaxAreaInHistogram(vector<int> heights){
        int n = heights.size();
        stack<int> stk;
        stk.push(-1); stk.push(0);
        int max_area = 0;
        for(int i=1 ; i<n ; i++){
            while(stk.top()!=-1 && heights[i] < heights[stk.top()]){
                int cur_h = heights[stk.top()];
                stk.pop();
                int cur_w = i - stk.top() - 1;
                max_area = max(max_area, cur_h * cur_w);
            }
            stk.push(i);
        }
        while(stk.top()!=-1){
            int cur_h = heights[stk.top()];
            stk.pop();
            int cur_w = n - stk.top() - 1;
            max_area = max(max_area, cur_h * cur_w);
        }
        return max_area;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n));
        int res = 0;
        for(int j=0 ; j<n ; j++){
            int acc = 0;
            for(int i=0 ; i<m ;i++){
                if(matrix[i][j] == '1')
                    acc++;
                else
                    acc = 0;
                dp[i][j] = acc;
            }
        }
        int max_area = 0;
        for(int i=0 ; i<m ; i++){
            max_area = max(max_area, findMaxAreaInHistogram(dp[i]));
        }
        return max_area;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<char>> q;

    q = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    EXPECT_EQ(s.maximalRectangle(q), 6);
    q = {};
    EXPECT_EQ(s.maximalRectangle(q), 0);
    q = {{'0'}};
    EXPECT_EQ(s.maximalRectangle(q), 0);
    q = {{'1'}};
    EXPECT_EQ(s.maximalRectangle(q), 1);
    q = {{'0', '0'}};
    EXPECT_EQ(s.maximalRectangle(q), 0);
}