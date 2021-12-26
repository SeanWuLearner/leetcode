/*Solution 1: priority queue*/
#include <queue>
class Solution_PQ {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        auto comp = [](const vector<int>& a, const vector<int>& b){
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        for(auto&& point : points){
            pq.push(point);
            if(pq.size()>k)
                pq.pop();
        }
        vector<vector<int>> res;
        while(!pq.empty()){
            res.push_back(move(pq.top()));
            pq.pop();
        }
        return res;
    }
};


/*Solution 2: quicksort*/
class Solution {
private:
    bool closer(vector<int>& a, vector<int>& b){
        return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
    }
    void quicksort(vector<vector<int>>& points, int l, int r, int target){
        if(l>=r) return;
        int pivot_idx = (l+r)/2;
        swap(points[pivot_idx], points[r]);
        auto&& pivot = points[r];

        int new_idx = l;
        for(int i=l ; i<=r-1 ; i++){
            if(closer(points[i], pivot)){
                swap(points[i], points[new_idx++]);
            }
        }
        swap(points[r], points[new_idx]);
        if(new_idx==target)
            return;
        else if(new_idx > target)
            quicksort(points, l, new_idx-1, target);
        else
            quicksort(points, new_idx+1, r, target);
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        quicksort(points, 0, points.size()-1, k-1);
        return vector<vector<int>>(points.begin(), points.begin()+k);
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<vector<int>> q, exp;
    int k;

    q = {{1,3},{-2,2}};
    k = 1;
    exp = {{-2,2}};
    EXPECT_EQ(s.kClosest(q, k), exp);

    q = {{3,3},{5,-1},{-2,4}};
    k = 2;
    exp = {{3,3},{-2,4}};
    EXPECT_EQ(s.kClosest(q, k), exp);
}