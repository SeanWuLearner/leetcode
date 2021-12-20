/*Solution 1: sort and 1 pass */
class Solution_sort {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> res;
        int min_diff = INT_MAX;
        for(int i=0 ; i<arr.size()-1 ; i++){
            int l = arr[i], r = arr[i+1], diff = r - l;
            if(diff > min_diff)
                continue;
            if(diff < min_diff){
                min_diff = diff;
                res.clear();
            }
            res.push_back({l, r});
        }
        return res;
    }
};

/*Solution 2: counting sort
    use large mem to avoid sorting, doubt if it's faster..?
*/
class Solution{
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr){
        int min_val = INT_MAX, max_val = INT_MIN;
        for(auto&& i : arr){
            min_val = min(min_val, i);
            max_val = max(max_val, i);
        }
        vector<bool> buckets(max_val - min_val + 1);
        int shift = -min_val;
        for(auto&& i : arr){
            buckets[i + shift] = true;
        }

        vector<vector<int>> res;
        int prev = -1000001, min_diff = INT_MAX;
        for(int i=0 ; i<buckets.size() ; i++){
            if(buckets[i] == false)
                continue;
            int diff = i - prev;
            if(diff > min_diff){
                prev = i;
                continue;
            }
            if(diff < min_diff ){
                min_diff = diff;
                res.clear();
            }
            res.push_back({prev-shift, i-shift});
            prev = i;
        }
        return res;
    }
};

TEST(Soluiton, Test1){
    Solution s;
    vector<int> q;
    vector<vector<int>> exp;

    q = {4,2,1,3};
    exp = {{1,2},{2,3},{3,4}};
    EXPECT_EQ(s.minimumAbsDifference(q), exp);

    q = {1,3,6,10,15};
    exp = {{1,3}};
    EXPECT_EQ(s.minimumAbsDifference(q), exp);

    q = {3,8,-10,23,19,-4,-14,27};
    exp = {{-14,-10},{19,23},{23,27}};
    EXPECT_EQ(s.minimumAbsDifference(q), exp);
}