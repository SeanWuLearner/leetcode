/*My Solution: put all start and end time together and sort them, start++, end-- */
class MySolution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        multimap<int, bool> times; //true = startTime, false = endTime
        for(auto& intv: intervals){
            times.insert({intv[0], true});
            times.insert({intv[1], false});
        }
        int max_rooms = 0, cur_rooms = 0;
        for(auto it = times.begin() ; it != times.end() ;){
            int proc_time = it->first;
            while(it!= times.end() && it->first == proc_time){
                cur_rooms += (it->second)? 1 : -1;
                it++;
            }
            max_rooms = max(max_rooms, cur_rooms);
        }
        return max_rooms;
    }
};

/* Brilliant solution:
    start < end:
        room++
        start_idx ++
    end < start:
        end_idx ++  // one meeting is over
        start_idx ++ // one meeting is started, so no change on room number.
*/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> starts, ends;
        for(auto& intv: intervals){
            starts.push_back(intv[0]);
            ends.push_back(intv[1]);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int rooms = 0, end_idx = 0;
        for(int start : starts){
            if(start < ends[end_idx])
                rooms++;
            else
                end_idx++;
        }
        return rooms;
    }
};




TEST(TestSolution, test1) {
    Solution s;
    vector<vector<int>> q;

    q = {{0,30},{5,10},{15,20}};
    EXPECT_EQ(s.minMeetingRooms(q), 2);
    q = {{7,10},{2,4}};
    EXPECT_EQ(s.minMeetingRooms(q), 1);

}