
/* Two pointers solution
Example exercise :
ADOBECODEBANC

< My algo >
    ADOBEC, move right ptr
    BEC, move left ptr
    BECODEBA, move right ptr,
    BA , move left ptr
    BANC, move right ptr

    End cond of move right: every char satisfied.
    End cond of move left: before two char short. (one char short)

< refined algo from Solution, neater>
    ADOBEC, move right ptr
    DOBEC, move left ptr
    DOBECODEBA, move right ptr,
    ODEBA , move left ptr
    ODEBANC, move right ptr
    ANC, move left ptr  --> it will found BANC while moving left ptr.

    End cond of move right: desirabled chars satisfied.
    End cond of move left: desirabled chars not satisfied.
*/
class Solution_SlidingWindow_v1 {
private:
    int getDistance(int cur[128], int match[128]){
        int cnt=0;
        for(int i=0 ; i<128 ; i++){
            if(match[i] > cur[i])
                cnt += match[i] - cur[i];
        }
        return cnt;
    }
public:
    string minWindow(string s, string t) {
        if(t.length()==0) return "";
        int match[128]={0}, cur[128]={0};

        //form match pattern
        for(char c : t)
            match[c]++;

        int left = 0, right = 0;
        int min_l, min_r, min_len = INT_MAX;
        while(right < s.length()){
            //move right, stop until all chars appear.
            while(right < s.length() && getDistance(cur, match)!=0){
                cur[s[right]]++;
                right++;
            }
            if(getDistance(cur, match)!=0) break;

            //move left, stop until not satisfied
            while(left <= right && getDistance(cur, match) == 0){
                if(right - left < min_len){
                    min_len = right - left;
                    min_l = left, min_r = right;
                    if(min_len == t.length())
                        return s.substr(min_l, min_r - min_l);
                }
                cur[s[left]]--;
                left++;
            }
        }
        return (min_len==INT_MAX)? "" : s.substr(min_l, min_r - min_l);
    }
};

/* drop getDistance API*/
class Solution_SlidingWindow_v2 {
public:
    string minWindow(string s, string t) {
        if(t.length()==0) return "";
        unordered_map<char, int> match, cur;

        //form match pattern
        for(char c : t)
            match[c]++;
        int demand_cnt = match.size();

        int left = 0, formed = 0;
        int min_l, min_r, min_len = INT_MAX;
        for(int right = 0; right < s.length() ; right++){
            char c = s[right];
            cur[c]++;

            if(match.find(c) != match.end() && cur[c] == match[c])
                formed++;

            while(left <= right && formed == demand_cnt){
                if(right - left + 1 < min_len){
                    min_len = right - left + 1;
                    min_l = left, min_r = right;
                    // if(min_len == t.length())
                        // return s.substr(min_l, min_r - min_l + 1);
                }
                c = s[left];
                cur[c]--;
                if(match.find(c) != match.end() && cur[c] < match[c])
                    formed--;
                left++;
            }
        }
        return (min_len==INT_MAX)? "" : s.substr(min_l, min_r - min_l + 1);
    }
};

/* Super neat solution from discussion */
class Solution_NeatSlidingWindow {
public:
    string minWindow(string s, string t) {
        int match[128] = {0};
        for(char c : t)
            match[c]++;
        int demands = t.length();
        int res_len = INT_MAX, res_start = 0;
        int l=0, r=0;
        for(r = 0; r < s.length() ; r++){
            if(match[s[r]]-- > 0)
                demands--;

            while(demands==0){
                if(r - l + 1  < res_len){
                    res_start = l;
                    res_len = r - l + 1;
                }
                if(match[s[l]]++ == 0)
                    demands++;
                l++;
            }
        }
        return (res_len==INT_MAX)? "" : s.substr(res_start, res_len);
    }
};



TEST(Solution, Test1){
    Solution_NeatSlidingWindow s;

    EXPECT_EQ(s.minWindow("ADOBECODEBANC", "ABC"), "BANC");
    EXPECT_EQ(s.minWindow("a", "a"), "a");
    EXPECT_EQ(s.minWindow("a", "aa"), "");
    EXPECT_EQ(s.minWindow("ab", "b"), "b");
    EXPECT_EQ(s.minWindow("bba", "ab"), "ba");

}