/* Solution 1: prefix with hashmap */
#include <unordered_set>
class Solution_hashset{
public:
    int findMaximumXOR(vector<int>& nums) {
        int max_val = 0;
        int mask=0;
        for(int i=30 ; i>=0 ; i--){
            unordered_set<int> s;

            mask |= (0x1 << i); //gen 0x100...0, 0x110...0, 0x111...0 and so on.
            for(auto num : nums){
                s.insert(num & mask);
            }

            int greedy = max_val | (0x1<<i); //try if we can set this bit on
            for(auto prefix : s){
                if(s.find(greedy ^ prefix) != s.end()){
                    max_val |= greedy;
                    break;
                }
            }
        }
        return max_val;
    }
};

/* Solution 2:  with trie
    while add num into trie, fire another trasversal in trie and try to visit the opposite bit
    (compare to added num) as much as possible. And form the max candidate.
*/
struct Trie{
    Trie *kids[2];
    Trie(){kids[0] = kids[1] = nullptr;}
};
class Solution{
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie head, *cur;

        for(auto num : nums){
            cur = &head;
            int mask = 0x1 << 30;
            for(int i=30 ; i>=0 ; i--, mask>>=1){
                Trie *&next = (mask & num)? cur->kids[1] : cur->kids[0];
                if(next == nullptr)
                    next = new Trie();
                cur = next;
            }
        }

        int max_val = 0;

        for(auto num :nums){
            cur = &head;
            int mask = 0x1 << 30;
            int val = 0;
            for(int i=30 ; i>=0 ; i--, mask>>=1){
                int ofs = (mask & num)? 0 : 1;
                if(cur->kids[ofs] != nullptr){
                    val |= mask;
                    cur = cur->kids[ofs];
                }else
                    cur = cur->kids[(ofs==0)? 1 : 0];
            }
            max_val = max(max_val, val);
        }
        return max_val;
    }
};


/* Solution brute force just for observation the ans pair. */
class Solution_forObservation {
public:
    int findMaximumXOR(vector<int>& nums) {
        int max_i, max_j;
        int max_val = 0;
        for(int i=0; i<nums.size()-1 ; i++){
            for(int j=i+1 ; j<nums.size() ; j++){
                int res = nums[i] ^ nums[j];
                if(res > max_val){
                    max_val = res;
                    max_i = i, max_j = j;
                }
            }
        }
        printf("max_val=%d, by %d xor %d\n", max_val, nums[max_i], nums[max_j]);
        return max_val;
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<int> q;
    int exp;

    q = {3,10,5,25,2,8};
    exp = 28;
    EXPECT_EQ(exp, s.findMaximumXOR(q));

    // q = {14,70,53,83,49,91,36,80,92,51,66,70};
    // exp = 127;
    // EXPECT_EQ(exp, s.findMaximumXOR(q));

    // q = {0,8};
    // exp = 8;
    // EXPECT_EQ(exp, s.findMaximumXOR(q));
}