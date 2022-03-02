#include <queue>
/* Solution 1. priority queue
    1. only max - min distance matters.
    2. preprocessing: try to maxmize all the elements as possible.
    3. put all elements into priority queue (max on top.)
    3. A loop continuously,
        a. checks if cur max-min can obtain a better result.
        b. if the top() elemement is even, then divide it by two and repeat the loop.
            if the top() element is odd, then exit the loop.
*/
class Solution1 {
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

/* Solution 2. sort all possble cases + sliding window
    1. for each element, put all possible values of the element together.
        we keep the (value, index) pair here.
    2. sort all (value, index) pairs by its value.
    3. sliding window thru the pairs vector, try to find the minimum window that can conver all elements.
        - init a var 'included' to count the num of included elements in the window.
        - init a vector 'cnts' that count the occurance of each element in sliding window. This will help us to update the var 'included'
*/
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        vector<pair<int,int>> cases;

        for(int i=0 ; i<nums.size() ; i++){
            int num = nums[i];
            if(num%2!=0){
                cases.push_back({num, i});
                cases.push_back({num*2, i});
            }else{
                cases.push_back({num, i});
                while(num%2==0){
                    num/=2;
                    cases.push_back({num, i});
                }
            }
        }

        sort(cases.begin(), cases.end());

        vector<int> cnts(nums.size());
        int l=0, r=0, included=0, min_diff = INT_MAX;
        while(r<cases.size()){
            auto &&vi_r = cases[r];
            if(cnts[vi_r.second]++==0)
                included++;
            r++;

            while(included == nums.size()){
                auto vi_l = cases[l];
                min_diff = min(min_diff, vi_r.first - vi_l.first);
                if(cnts[vi_l.second]--==1)
                    included--;
                l++;
            }
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