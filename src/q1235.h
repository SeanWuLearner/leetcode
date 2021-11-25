class MySolution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        multimap<int, int> endtime_idx; //endtime : idx in array in increasing order
        map<int, int> maxprofit; //endtime : max_profit
        maxprofit[0] = 0;
        int ans = 0;
        int ans_end = 0;

        for(int i=0 ; i< endTime.size(); i++)
            endtime_idx.insert(make_pair(endTime[i], i));

        for(auto it = endtime_idx.begin(); it != endtime_idx.end(); it++){
            int end = it->first, idx = it->second;
            auto prev_profit = maxprofit.lower_bound(startTime[idx]);
            if(prev_profit == maxprofit.end() || prev_profit->first > startTime[idx])
                prev_profit--;
            int cur_profit = prev_profit->second + profit[idx];
            if(cur_profit > ans){
                ans = cur_profit;
                ans_end = end;
                maxprofit[end] = cur_profit;
            }

        }
        return ans;
    }
};

/* same idea, cleaner solution from discussion : sort the endTime, dp bottom-up */
class Solution_bottomUp {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;

        for(int i = 0 ; i<n ; i++)
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        sort(jobs.begin(), jobs.end());

        map<int, int> dp = {{0,0}};  //end, profit
        for(auto& job : jobs){
            int prev_profit = prev(dp.upper_bound(job[1]))->second;
            int cur_profit = prev_profit + job[2];
            if(cur_profit > dp.rbegin()->second){
                dp[job[0]] = cur_profit;
            }
        }
        return dp.rbegin()->second;
    }
};

/* dp top-bottom solution, sort it by startTime
    dp[cur] can be either of 1. cur_profit + dfs[next]
                             2. dfs[cur+1]
*/
class Solution {
private:
    map<int, int> dp;

    int dfs(int cur, vector<vector<int>>& jobs){
        if(cur == jobs.size())
            return 0;
        if(dp.count(cur)!=0)
            return dp[cur];

        int next = get_next_job(cur, jobs);
        dp[cur] = max(dfs(cur+1, jobs),
                      jobs[cur][2] + ((next==-1)? 0 : dfs(next, jobs))
                     );
        return dp[cur];

    }
    int get_next_job(int cur, vector<vector<int>>& jobs){
        int l = cur+1, r = jobs.size();
        int end = jobs[cur][1];
        while(l<r){
            int m = (l+r) / 2;
            if(jobs[m][0] < end)
                l = m + 1;
            else
                r = m;
        }
        return (l >= jobs.size())? -1 : l;
    }
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;

        for(int i = 0 ; i<n ; i++)
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        sort(jobs.begin(), jobs.end());

        return dfs(0, jobs);
    }
};



TEST(TestSolution, test1) {
    Solution s;
    vector<int> start, end, profit;

    start = {1,2,3,3};
    end = {3,4,5,6};
    profit = {50,10,40,70};
    EXPECT_EQ(s.jobScheduling(start, end, profit), 120);
}

TEST(TestSolution, test2) {
    Solution s;
    vector<int> start, end, profit;

    start = {1,2,3,4,6};
    end = {3,5,10,6,9};
    profit = {20,20,100,70,60};
    EXPECT_EQ(s.jobScheduling(start, end, profit), 150);
}

TEST(TestSolution, test3) {
    Solution s;
    vector<int> start, end, profit;

    start = {4,2,4,8,2};
    end = {5,5,5,10,8};
    profit = {1,2,8,10,4};
    EXPECT_EQ(s.jobScheduling(start, end, profit), 18);

}