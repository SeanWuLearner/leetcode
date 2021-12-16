#include "vector_util.h"
#include <unordered_map>
#include <map>

template<typename T1, typename T2>
void printPairs(vector<T1, T2>& v){
    for(auto&& p : v){
        cout << p.first << " : " << p.second << endl;
    }
    // cout << endl;
}

/*Solution1: Hashmap + priority queue
    runtime O(n + nlogk), space O(n+k)
*/
class Solution_heap {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for(auto i : nums){
            if(cnt.find(i) == cnt.end()){
                cnt[i] = 1;
            }else{
                cnt[i]++;
            }
        }

        multimap<int, int> pq;
        for(auto& kv : cnt){
            pq.insert({kv.second, kv.first});
            if(pq.size() > k)
                pq.erase(pq.begin());
        }
        vector<int> res;
        for(auto& kv : pq){
            res.push_back(kv.second);
        }
        return res;
    }
};
/*Solution2: bucket sort, O(n) run time */
class Solution_bucketSort{
public:
    vector<int> topKFrequent(vector<int>& nums, int k){
        unordered_map<int,int> cnt;
        for(auto i : nums){
            if(cnt.find(i) == cnt.end())
                cnt[i] = 1;
            else
                cnt[i]++;
        }

        vector<vector<int>> buckets(nums.size()+1);
        for(auto&& kv : cnt){
            buckets[kv.second].push_back(kv.first);
        }

        vector<int> res;
        for(auto b_it = buckets.rbegin() ; b_it != buckets.rend() ; b_it++){
            res.insert(res.end(), b_it->begin(), b_it->end());
            if(res.size()>=k) break;
        }
        return res;
    }
};

/*Solution2: Quickselect, O(n) run time
    The difference between it and quicksoft is, it only needs to recusive one side
    instead of both sides of pivot. That makes the run time from O(nlogn) to O(n)
*/
#include <algorithm>
class Solution{
private:
    vector<pair<int,int>> val_freqs;

    template<typename T>
    void swap(T&& t, int i1, int i2){
        iter_swap(t.begin()+i1, t.begin()+i2);
    }
    int partition(int l, int r, int pivot){
        swap(val_freqs, r, pivot);
        pivot = r;

        int insert_idx = 0;
        for(int i=0 ; i<r ; i++){
            if(val_freqs[pivot].second >= val_freqs[i].second){
                swap(val_freqs, insert_idx++, i);
            }
        }
        swap(val_freqs, insert_idx, pivot);
        return insert_idx;
    }
    void quickselect(int l, int r, int kthSmallest){
        if(l==r) return;
        int pivot = (l+r)/2;
        int idx = partition(l, r, pivot);
        if(idx == kthSmallest) return;
        if(idx > kthSmallest)
            quickselect(l, idx-1, kthSmallest);
        else
            quickselect(idx+1, r, kthSmallest);
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k){
        unordered_map<int,int> cnts;
        for(auto&& i : nums){
            if(cnts.find(i)==cnts.end()){
                cnts[i] = 1;
            }else{
                cnts[i]++;
            }
        }

        for(auto&& val_freq : cnts){
            int val = val_freq.first;
            int freq = val_freq.second;
            val_freqs.push_back({val, freq});
        }
        int n = val_freqs.size();
        quickselect(0, n-1, n-k);
        vector<int> res;
        for(int i = n-k ; i < n ; i++){
            res.push_back(val_freqs[i].first);
        }
        return res;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q, exp;

    q = {1,1,1,2,2,3};
    exp = {1,2};
    EXPECT_EQ(sortVec(exp), sortVec(s.topKFrequent(q,2)));
}
TEST(Solution, Test2){
    Solution s;
    vector<int> q, exp;

    q = {1};
    exp = {1};
    EXPECT_EQ(sortVec(exp), sortVec(s.topKFrequent(q,1)));
}

TEST(Solution, Test3){
    Solution s;
    vector<int> q, exp;

    q = {3,0,1,0};
    exp = {0};
    EXPECT_EQ(sortVec(exp), sortVec(s.topKFrequent(q,1)));
}
TEST(Solution, Test4){
    Solution s;
    vector<int> q, exp;

    q = {2,3,4,1,4,0,4,-1,-2,-1};
    exp = {4, -1 };
    EXPECT_EQ(sortVec(exp), sortVec(s.topKFrequent(q,2)));
}