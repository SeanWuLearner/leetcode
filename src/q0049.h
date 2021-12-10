/* Solution: using string as hash key */
class Solution_StrHash {
private:
    string getHashKey(string& str){
        vector<int> cnts(26);
        for(char c : str)
            cnts[c-'a']++;

        string res;
        for(int cnt : cnts)
            res += to_string(cnt) + ",";
        return res;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, int> idx_map;
        for(auto&& str : strs){
            string key = getHashKey(str);
            auto it = idx_map.find(key);
            if(it == idx_map.end()){
                idx_map[key] = res.size();
                res.push_back({str});
            }else{
                res[it->second].push_back(str);
            }
        }
        return res;
    }
};

/* Solution: using prime num as hash key, will overflow while longer string */
class Solution_PrimeHash {
private:
    const vector<int> primes{2, 3, 5, 7, 11 ,13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 107};
    int getHashKey(string& str){

        int prod = 1;
        for(char c : str)
            prod *= primes[c-'a'];
        return prod;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<int, int> idx_map;
        for(auto&& str : strs){
            int key = getHashKey(str);
            cout << str << ": " << key <<endl ;
            auto it = idx_map.find(key);
            if(it == idx_map.end()){
                idx_map[key] = res.size();
                res.push_back({str});
            }else{
                res[it->second].push_back(str);
            }
        }
        return res;
    }
};

/* Solution: generate random num for each letter, use the sum (ulong) as key */
using ulong = unsigned long;

static unsigned long xorshf96(void) {    /* A George Marsaglia generator, period 2^96-1 */
	static unsigned long x=123456789, y=362436069, z=521288629;
	unsigned long t;

	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;

	z = t ^ x ^ y;
	return z;
}
class Solution {
private:
    vector<ulong> weights;
    void initWeights(){
        weights.resize(26);
        for(auto&& w : weights)
            w = xorshf96();
    }
    ulong getHashKey(string& str){
        ulong res = 0;
        for(auto c : str)
            res += weights[c-'a'];
        return res;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<ulong, int> idx_map;
        initWeights();
        for(auto&& str : strs){
            ulong key = getHashKey(str);
            // cout << str << ": " << key <<endl ;
            auto it = idx_map.find(key);
            if(it == idx_map.end()){
                idx_map[key] = res.size();
                res.push_back({str});
            }else{
                res[it->second].push_back(str);
            }
        }
        return res;
    }
};

#include "vector_util.h"

TEST(Solution, Test1){
    Solution s;
    vector<string> q;
    vector<vector<string>> exp, test1;

    q = {"eat","tea","tan","ate","nat","bat"};
    exp = {{"bat"},{"nat","tan"},{"ate","eat","tea"}};
    EXPECT_EQ(sortVec(s.groupAnagrams(q)), sortVec(exp));

    q = {""};
    exp = {{""}};
    EXPECT_EQ(sortVec(s.groupAnagrams(q)), sortVec(exp));

    q = {"a"};
    exp = {{"a"}};
    EXPECT_EQ(sortVec(s.groupAnagrams(q)), sortVec(exp));

}
