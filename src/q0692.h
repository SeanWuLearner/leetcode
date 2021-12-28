#include "vector_util.h"
#include <queue>
/* Solution1: hashmap + priority queue */
using PIS = pair<int,string>;
class Solution_PQ {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freqs;
        for(auto&& s : words)
            freqs[s]++;

        auto cmp = [](PIS& a, PIS& b){
            if(a.first == b.first)
                return a.second < b.second;
            else
                return a.first > b.first;
        };
        priority_queue<PIS, vector<PIS>, decltype(cmp)> pq(cmp);
        for(auto&& freq : freqs ){
            pq.push({freq.second, freq.first});
            if(pq.size()>k)
                pq.pop();
        }
        vector<string> res;
        while(!pq.empty()){
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/* Solution2: hashmap + quickselect
    it's a bit jank .... quickselect here did return most k freq elements,
    but it's not guarantee those k elements are in descending order.....
    so you still have to manually sort them before returning them.
*/
using PSI = pair<string, int>;

class Solution {
    bool greater(PSI &a, PSI &b){
        if(a.second == b.second)
            return a.first < b.first;
        return a.second > b.second;
    }
    void quickselect(vector<PSI>& arr, int l, int r, int k){
        if(l>=r) return;
        int pivot_idx = (l+r)/2;
        swap(arr[r], arr[pivot_idx]);
        auto&& pivot = arr[r];

        int insert_idx = l;
        for(int i=l; i<r ; i++){
            if(greater(arr[i], pivot)){
                swap(arr[i], arr[insert_idx++]);
            }
        }
        swap(arr[r], arr[insert_idx]);
        if(insert_idx == k)
            return;
        else if(insert_idx > k)
            quickselect(arr, l, insert_idx-1, k);
        else
            quickselect(arr, insert_idx+1, r, k);
    }
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freqs;
        for(auto&& s : words)
            freqs[s]++;

        vector<PSI> arr(freqs.begin(), freqs.end());


        quickselect(arr, 0, arr.size()-1, k);
        sort(arr.begin(), arr.begin()+k, [](PSI &a, PSI &b){
            if(a.second == b.second)
                return a.first < b.first;
            return a.second > b.second;
        });

        vector<string> res;
        for(auto it = arr.begin() ; it != arr.begin()+k ; it++)
            res.push_back(it->first);
        return res;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<string> q, exp;
    int k;

    q = {"i","love","leetcode","i","love","coding"};
    k = 2;
    exp = {"i","love"};
    EXPECT_EQ(exp, s.topKFrequent(q, k));

    q = {"the","day","is","sunny","the","the","the","sunny","is","is"};
    k = 4;
    exp = {"the","is","sunny","day"};
    EXPECT_EQ(exp, s.topKFrequent(q, k));

    q = {"i","love","leetcode","i","love","coding"};
    k = 1;
    exp = {"i"};
    EXPECT_EQ(exp, s.topKFrequent(q, k));
}