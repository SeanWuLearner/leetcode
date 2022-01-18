
/* Solution 1: A dp array which record the closest dist to the non-empty seats*/
class Solution1 {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();
        vector<int> dists(n, INT_MAX);
        //from left to right
        for(int i=0; i<n; i++){
            int now = (seats[i]==1)? 0 : (i==0 || dists[i-1]==INT_MAX)? INT_MAX : dists[i-1]+1;
            dists[i] = min(dists[i], now);
        }
        //from right to left
        int max_dist = 0;
        for(int i=n-1; i>=0 ; i--){
            int now = (seats[i]==1)? 0 : (i==n-1 || dists[i+1]==INT_MAX)? INT_MAX : dists[i+1]+1;
            dists[i] = min(dists[i], now);
            max_dist = max(max_dist, dists[i]);
        }
        return max_dist;
    }
};

/* Solution 2: no DP array, handle it in 3 cases
    During iterations, while seats[i] = 1,
        c1. no one seats on the left, max_dist on the left would be i.
        c2. someone seats on the left, max_dist on the left would be
            (i - prev_i) / 2
        c3. iteration reach end, no one seats on the right,
            max_dist here is (n-1 - prev_i)
 */
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int prev_i = -1, max_dist = 0;
        int dist;
        for(int i=0 ; i< seats.size() ; i++){
            if(seats[i] != 1) continue;

            if(prev_i == -1)
                dist = i;
            else
                dist = (i-prev_i) >> 1;
            max_dist = max(max_dist, dist);
            prev_i = i;
        }
        max_dist = max(max_dist, (int)(seats.size() - 1 - prev_i));
        return max_dist;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {1,0,0,0,1,0,1};
    exp = 2;
    EXPECT_EQ(s.maxDistToClosest(q), exp);

    q = {1,0,0,0};
    exp = 3;
    EXPECT_EQ(s.maxDistToClosest(q), exp);

    q = {0,1};
    exp = 1;
    EXPECT_EQ(s.maxDistToClosest(q), exp);
}