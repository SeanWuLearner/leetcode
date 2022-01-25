/* Solution1: binary to find r = mid+1 and mid NG, r OK
l , mid, r
X ,  X , O   ==> l = mid
X.,  O , O   ==> r = mid
O,  O,  O ==> res = l
*/
class Solution1 {
private:
    bool canFinished(vector<int>& piles, int k, int h){
        long sum = 0;
        for(int i : piles){
            sum += (i+(k-1)) / k;
        }
        return sum <= h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int mid, l=1, r=*max_element(piles.begin(), piles.end());
        if(canFinished(piles, l, h)) return l;
        while(l+1<r){
            mid = (l+r) >> 1;
            if(canFinished(piles, mid, h))
                r = mid;
            else
                l = mid;
        }
        return r;
    }
};
/*Solution 2: precise binary search*/
class Solution {
private:
    bool canFinished(vector<int>& piles, int k, int h){
        long sum = 0;
        for(int i : piles){
            sum += (i+(k-1)) / k;
        }
        return sum <= h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int mid, l=1, r=*max_element(piles.begin(), piles.end());
        while(l<r){
            mid = (l+r) >> 1;
            if(canFinished(piles, mid, h))
                r = mid;
            else
                l = mid+1;
        }
        return r;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;
    int h, exp;

    q = {3,6,7,11};
    h = 8;
    exp = 4;
    EXPECT_EQ(exp, s.minEatingSpeed(q, h));

    q = {30,11,23,4,20};
    h = 5;
    exp = 30;
    EXPECT_EQ(exp, s.minEatingSpeed(q, h));

    q = {30,11,23,4,20};
    h = 6;
    exp = 23;
    EXPECT_EQ(exp, s.minEatingSpeed(q, h));
}