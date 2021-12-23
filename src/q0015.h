
/* Solution 1: sort nums first, then fix first num, the other two nums will both
   move from outside to the center.
 */
using VI = vector<int>;
using VVI = vector<VI>;
class Solution_TwoPointers {
private:
    void moveLeft(VI& nums, int &l, int const r){
        do{
            l++;
        }while(l<r && nums[l]==nums[l-1]);
    }
    void moveRight(VI& nums, int const l, int &r){
        do{
            r--;
        }while(l<r && nums[r]==nums[r+1]);
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        VVI res;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-2 ; i++){
            if(i>0 && nums[i] == nums[i-1]) continue;
            int l = i+1, r = n-1;
            while(l<r){
                int sum = nums[l] + nums[r] + nums[i];
                if(sum == 0){
                    res.push_back({nums[i], nums[l], nums[r]});
                    moveLeft(nums, l, r);
                    moveRight(nums, l, r);
                }else if(sum > 0){
                    moveRight(nums, l, r);
                }else{
                    moveLeft(nums, l, r);
                }
            }
        }
        return res;
    }
};

/* Solution 2:
    fix the 1st num, then use hash_set to handle the rest two nums as two sum.

{Graceful way to handle duplicates}:
    Fast-forward ONLY when there is a match.
*/
#include <unordered_set>
class Solution_HashSet {
private:
    VVI twoSum(VI& nums, int idx, int target){
        VVI res;
        unordered_set<int> memo;
        for(int i = idx ; i < nums.size() ; i++){
            int diff = target - nums[i];
            if(memo.find(diff) != memo.end()){
                res.push_back({diff, nums[i]});
                while(i+1 < nums.size() && nums[i+1] == nums[i])
                    i++;
            }
            memo.insert(nums[i]);
        }
        return res;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        VVI res;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0 ; i < n-2 ; i++){
            if(i>0 && nums[i] == nums[i-1]) continue;
            VVI sub_res = twoSum(nums, i+1, -nums[i]);
            for(auto v : sub_res)
                res.push_back({nums[i], v[0], v[1]});
        }
        return res;
    }
};

/*Solution 3: No sort, use hash(vector<int>) to avoid duplicates
*/
#include <unordered_set>
struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

using VecSet = std::unordered_set<std::vector<int>, VectorHash>;

class Solution {
private:
    VVI twoSum(VI& nums, int idx, int target){
        VVI res;
        unordered_set<int> memo;
        for(int i = idx ; i < nums.size() ; i++){
            int diff = target - nums[i];
            if(memo.find(diff) != memo.end()){
                res.push_back({diff, nums[i]});
            }
            memo.insert(nums[i]);
        }
        return res;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        VecSet vec_set;
        unordered_set<int> dup;
        int n = nums.size();
        for(int i = 0 ; i < n-2 ; i++){
            if(dup.find(nums[i])!= dup.end()) continue;
            dup.insert(nums[i]);

            VVI sub_res = twoSum(nums, i+1, -nums[i]);
            for(auto v : sub_res){
                vector<int> triplet{nums[i], v[0], v[1]};
                sort(triplet.begin(), triplet.end());
                vec_set.insert(triplet);
            }
        }
        VVI res;
        for(auto&& v : vec_set)
            res.push_back(v);
        return res;
    }
};

#include "vector_util.h"
TEST(Solution, Test1){
    Solution s;
    VI q;
    VVI exp;

    q = {-1,0,1,2,-1,-4};
    exp = {{-1,-1,2},{-1,0,1}};
    EXPECT_EQ(sortVec(s.threeSum(q)), sortVec(exp));

    q = {};
    exp = {};
    EXPECT_EQ(s.threeSum(q), exp);

    q = {0};
    exp = {};
    EXPECT_EQ(s.threeSum(q), exp);

    q = {0,0,0};
    exp = {{0,0,0}};
    EXPECT_EQ(sortVec(s.threeSum(q)), sortVec(exp));
}