/* Solution 1: my naive of a helper func only get rotation cnt of making
            all elements of array_a all equal to target.
*/
class Solution1 {
public:
    int numOfRotations(vector<int>& a, vector<int>& b, int target){
        int cnt=0;
        for(int i=0 ; i<a.size() ; i++){
            if(a[i]==target)
                continue;
            if(b[i]==target)
                cnt++;
            else
                return INT_MAX;
        }
        // cout << "target= " << target << ", cnt= " << cnt << endl;
        return cnt;
    }
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int res = min({numOfRotations(tops, bottoms, tops[0]),
                       numOfRotations(tops, bottoms, bottoms[0]),
                       numOfRotations(bottoms, tops, tops[0]),
                       numOfRotations(bottoms, tops, bottoms[0])});
        return (res==INT_MAX)? -1 : res;
    }
};
/* Solution 2: make the helper function can check BOTH array, then two iteration
            would be enough.
*/
class Solution{
private:
    int minRotations(vector<int>& a, vector<int>& b, int target){
        int i, cnt_a = 0, cnt_b = 0;
        for(i=0 ; i<a.size() ; i++){
            if(a[i] != target && b[i] != target)
                break;
            if(a[i]!= target) cnt_a++;
            if(b[i]!= target) cnt_b++;
        }
        return (i!=a.size())? INT_MAX : min(cnt_a, cnt_b);
    }
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int res = min(minRotations(tops, bottoms, tops[0]),
                      minRotations(tops, bottoms, bottoms[0])) ;
        return (res == INT_MAX)? -1 : res;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> top, down;
    int exp;

    top = {2,1,2,4,2,2};
    down = {5,2,6,2,3,2};
    exp = 2;
    EXPECT_EQ(exp, s.minDominoRotations(top, down));

    top = {3,5,1,2,3};
    down = {3,6,3,3,4};
    exp = -1;
    EXPECT_EQ(exp, s.minDominoRotations(top, down));
}