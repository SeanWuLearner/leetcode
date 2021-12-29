/* exercise
    if f(x,y) =  100 - x / y,  z=0
              fix x = 1, binary search y, found out y cannot be found
                    y=1, res = 99,
                    y=1000, res = 100,
                    y= 500, res = 100 , cannot find the next y because z is always not in the range.
              fix x = 1000, binary search y,
                    y=1 , res = -900
                    y=1000, res = 99
                    y= 500, res = 98
                    decide to search y range [1:500]
                    y = 250, res = 96
*/

using CFun = int (*)(int, int);
class CustomFunction{
public:
    CFun f;
    CustomFunction(CFun f_ = nullptr):f(f_){}
};

/* Solution 1 : O(X+Y), use binary search on y each time, but the range of binary
                search shrinked down on each iteration.
 */
class Solution_my {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        int prev_y = 1000;

        for(int x=1 ; x<=1000; x++){
            int l=1, r=prev_y;
            int res_l = customfunction.f(x, l);
            int res_r = customfunction.f(x, r);
            while(l<=r){
                int m = (l+r)/2;
                int res_m = customfunction.f(x, m);
                if(res_m == z || res_l==z || res_r==z ){
                    int y = (res_m==z)? m : (res_l==z)? l : r;
                    res.push_back({x, y});
                    prev_y = y-1;
                    break;
                }else if(res_m > z && z > res_l){
                    r = m-1;
                    res_r = customfunction.f(x,r);
                }else if(res_r > z && z > res_m){
                    l = m+1;
                    res_l = customfunction.f(x,l);
                }else
                    break;
            }
        }
        return res;
    }
};
/* Solution 2 : O(X+Y), don't use binary search on y, just keep decreament. */
class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> res;
        int y = 1000;

        for(int x=1 ; x<=1000; x++){
            while(y>1 && customfunction.f(x,y) > z) y--;
            if(customfunction.f(x,y) == z){
                res.push_back({x,y});
            }
        }
        return res;
    }
};

#include "vector_util.h"

TEST(Solution, Test1){
    Solution s;
    CustomFunction cfun;
    vector<vector<int>> exp;
    int z;
    auto f_add = [](int a, int b){return a+b;};
    auto f_mul = [](int a, int b){return a*b;};

    cfun.f = f_add;
    z = 5;
    exp = {{1,4},{2,3},{3,2},{4,1}};
    EXPECT_EQ(sortVec(s.findSolution(cfun, z)), sortVec(exp));

    cfun.f = f_mul;
    z = 5;
    exp = {{1,5},{5,1}};
    EXPECT_EQ(sortVec(s.findSolution(cfun, z)), sortVec(exp));
}