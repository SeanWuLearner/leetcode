#include <map>

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        map<int, int> m;//<val, index> , closet index will overwrite older one.
        vector<bool> dp_odd(n), dp_even(n); //reachable

        int cnt = 1;
        dp_odd[n-1] = dp_even[n-1] = true;
        m[arr[n-1]] = n-1;

        for(int i = n-2 ; i>=0 ; i--){
            //odd
            auto it = m.lower_bound(arr[i]);
            if(it != m.end())
                dp_odd[i] = dp_even[it->second];

            //even
            it = m.upper_bound(arr[i]);
            if(it != m.begin())
                dp_even[i] = dp_odd[(--it)->second];

            //update m and count up result.
            m[arr[i]] = i;
            if(dp_odd[i])
                cnt++;
        }
        return cnt;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> q;

    q = {1,2,3,2,1,4,4,5};
    EXPECT_EQ(6, s.oddEvenJumps(q));

    q = {10,13,12,14,15};
    EXPECT_EQ(2, s.oddEvenJumps(q));

    q = {2,3,1,1,4};
    EXPECT_EQ(3, s.oddEvenJumps(q));

}