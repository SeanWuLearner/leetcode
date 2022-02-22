/*Solution 1: easy as a pie */
class Solution1 {
public:
    int fixedPoint(vector<int>& arr) {
        for(int i=0 ;i<arr.size() ; i++){
            if(i==arr[i])
                return i;
        }
        return -1;
    }
};

/*Solution 2: binary search */
class Solution {
public:
    int fixedPoint(vector<int>& arr) {
        int l=0, r=arr.size()-1;
        while(l<r){
            int mid = (l+r) >> 1;
            if(arr[mid] < mid)
                l = mid+1;
            else
                r = mid;
        }
        return (l==arr[l])? l : -1;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {-10,-5,0,3,7};
    exp = 3;
    EXPECT_EQ(exp, s.fixedPoint(q));

    q = {0,2,5,8,17};
    exp = 0;
    EXPECT_EQ(exp, s.fixedPoint(q));

    q = {-10,-5,3,4,7,9};
    exp = -1;
    EXPECT_EQ(exp, s.fixedPoint(q));
}