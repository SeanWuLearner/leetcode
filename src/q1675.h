#include <queue>
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int> pq;
        int min_val=INT_MAX;
        for(int &i : nums){
            if(i%2==0){
                pq.push(i);
                min_val = min(min_val, i);
            }else{
                pq.push(i<<1);
                min_val = min(min_val, i<<1);
            }
        }

        int min_diff = pq.top() - min_val;
        while(pq.top()%2==0){
            int new_val = pq.top() >> 1;
            pq.pop();
            pq.push(new_val);
            min_val = min(min_val, new_val);
            min_diff = min(min_diff, pq.top() - min_val);
        }
        return min_diff;
    }
};

TEST(Solution, test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {1,2,3,4};
    exp = 1;
    EXPECT_EQ(exp, s.minimumDeviation(q));

    q = {4,1,5,20,3};
    exp =3;
    EXPECT_EQ(exp, s.minimumDeviation(q));

    q = {2,10,8};
    exp =3;
    EXPECT_EQ(exp, s.minimumDeviation(q));
}