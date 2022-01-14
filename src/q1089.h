/* Solution1
exercise

[1,0,2,3,0,4,5,0] , len = 8
 0 2 3 4 6 7

in =  [1,0,2,3,4,5,0,8] , len = 8
       0 2 3 4 5 6 8
out = [1,0,0,2,3,4,5,0]

in = [1,2,3]
      0 1 2

 algo:
    s1. iter from left to right, count 1 while non-0, count 2 while 0, stop while cnt to n-1
    s2. set wr_idx to n-1, rd_idx = where we stop at step1, iter rd_idx until 0;
*/

class Solution1 {
public:
    void duplicateZeros(vector<int>& arr) {
        int i, cnt=-1, n = arr.size();
        for(i = 0 ; i < n && cnt<(n-1) ; i++){
            if(arr[i]==0)
                cnt+=2;
            else
                cnt+=1;
        }

        int wr_i = n-1;
        if(cnt==n){ //special case, 0 at the end
            arr[wr_i--] = arr[i-1];
            i--;
        }
        for(i=i-1; i>=0 ; i--){
            if(arr[i]==0){
                arr[wr_i--] = arr[i];
            }
            arr[wr_i--] = arr[i];
        }
    }
};

/* Solution 2: same idea, more precise
    wr_idx will start from the back of the extended array, however it only update to arr
    while wr_idx < n
*/
class Solution{
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size(), j = n + count(arr.begin(), arr.end(), 0) - 1;
        for(auto it = arr.rbegin(); it!=arr.rend() ; it++){
            if(*it==0){
                if(j<n) arr[j] = 0;
                j--;
            }
            if(j<n) arr[j] = *it;
            j--;
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q, exp;

    q = {1,0,2,3,0,4,5,0};
    exp = {1,0,0,2,3,0,0,4};
    s.duplicateZeros(q);
    EXPECT_EQ(q, exp);

    q = {1,2,3};
    exp = {1,2,3};
    s.duplicateZeros(q);
    EXPECT_EQ(q, exp);
}