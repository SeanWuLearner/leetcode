/*
  0 -> +1
  1 -> -1
  for nums.size() = n, the level can vary from -n to +n, for a 2n+1 sized array, the ofs would be
  n
*/

/*Solution1, array*/
// class Solution {
// public:
//     int findMaxLength(vector<int>& nums) {
//         int n = nums.size();
//         vector<int> indices(n*2 + 1, -2);
//         int degree = n, max_len=0;
//         indices[degree] = -1;
//         for(int i=0 ; i < n ; i++){
//             degree += (nums[i]==0)? +1 : -1;
//             if(indices[degree] == -2){
//                 indices[degree] = i;
//                 continue;
//             }
//             max_len = max(max_len, i - indices[degree]);
//         }
//         return max_len;
//     }
// };

/*Solution2, hashmap*/
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> dict;
        int deg = 0, max_len = 0;
        dict[0] = -1;
        for(int i=0 ; i<nums.size() ; i++){
            deg += (nums[i]==0)? +1 : -1;
            auto it = dict.find(deg);
            if(it==dict.end()){
                dict[deg] = i;
                continue;
            }
            max_len = max(max_len, i - it->second);
        }
        return max_len;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {0,1};
    exp = 2;
    EXPECT_EQ(exp, s.findMaxLength(q));

    q = {0,1,0};
    exp = 2;
    EXPECT_EQ(exp, s.findMaxLength(q));

    q = {0,1,1,0,0};
    exp = 4;
    EXPECT_EQ(exp, s.findMaxLength(q));
}