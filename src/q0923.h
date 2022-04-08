/*Solution 1: hash_map to count the occurance of 2sum.
    It takes too long while using unordered_map.
*/
class Solution1 {
public:
    long get(vector<long> &arr, int idx){
        return (idx<0 || idx>=arr.size())? 0 : arr[idx];
    }
    void inc(vector<long> &arr, int idx){
        if(idx>=0 && idx<arr.size())
            arr[idx]++;
    }

    int threeSumMulti(vector<int>& arr, int target) {
        vector<long> sum2(301);
        long res = 0;

        for(int i=0 ; i<arr.size() ; i++){
            res += get(sum2, target-arr[i]);

            for(int j=0; j<i; j++){
                inc(sum2, arr[i]+arr[j]);
            }
        }
        return res % 1000000007;
    }
};

/* Solution 2: Count with diff cases:
    C1. i!=j!=k
    C2. i==j!=k
    c3. i==j==k
*/
class Solution2 {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        unordered_map<int, long> cnts;
        for(int i:arr){
            if(cnts.find(i)==cnts.end())
                cnts[i]=1;
            else
                cnts[i]++;
        }

        long res=0;

        for(auto &&kv_i : cnts){
            for(auto &&kv_j : cnts){
                int i=kv_i.first, j=kv_j.first, k=target-i-j;
                if(cnts.find(k)==cnts.end())
                    continue;

                if(i==j && j==k)
                    res += cnts[i] * (cnts[i]-1) * (cnts[i]-2) / 6;
                else if(i==j && j!=k)
                    res += cnts[k] * (cnts[i]) * (cnts[i]-1) / 2;
                else if(i<j && j<k)
                    res += cnts[i] * cnts[j] * cnts[k];
            }
        }
        return res % 1000000007;
    }
};

/* Solution 3: 3sum method, but shift with considering duplication

1 1 1 1
 3 + 2 + 1 = 6

1 1 1 1
 4 + 3 + 2 + 1 = 10

so, while idx_j = idx_i+1, don't have to handle it additionally.
What about the case
    j==k, res += cnt(j)*(cnt(j)-1)/2
    j!=k, res += cnt(j)*cnt(k);

*/
class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int res=0;
        const int MOD = 1000000007;

        for(int i=0; i<arr.size()-2 ; i++){
            int sub_target = target-arr[i];
            if(sub_target < 0) continue;

            int j=i+1, k=arr.size()-1;
            while(j<k){
                int sum = arr[j] + arr[k];
                if(sum > sub_target)
                    k--;
                else if(sum < sub_target)
                    j++;
                // match target, and arr[j]!=arr[k]
                else if(arr[j]!=arr[k]){
                    int cnt_l = 1, cnt_r = 1;
                    for(; j+1<=k && arr[j+1]==arr[j] ; j++)
                        cnt_l++;
                    for(; k-1>=j && arr[k-1]==arr[k] ; k--)
                        cnt_r++;

                    res += cnt_l * cnt_r;
                    res %= MOD;
                    j++, k--;
                // match target, and arr[j]==arr[k]
                }else{
                    int num = k-j+1;
                    res += num * (num-1) / 2;
                    res %= MOD;
                    break;
                }
            }
        }

        return res;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int tar,exp;

    q = {1,1,2,2,3,3,4,4,5,5};
    tar = 8, exp =20;
    EXPECT_EQ(exp, s.threeSumMulti(q, tar));

    q = {1,1,2,2,2,2};
    tar = 5, exp =12;
    EXPECT_EQ(exp, s.threeSumMulti(q, tar));
}