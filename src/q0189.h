/* Solution1: extra array... cheating. */
class Solution_ExtraArray {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> tmp(n);
        for(int i = 0 ; i < n ; i++){
            int j = (i+k) % n;
            tmp[j] = nums[i];
        }
        nums = tmp;
    }
};

/* Solution 2. shift one by a time. Time Limit Exceeded */
class Solution_ShiftOneEachtime {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        for(int cnt=0 ; cnt<k ; cnt++){
            int tmp = nums[n-1];
            for(int i = 0 ; i < n ; i++){
                swap(nums[i], tmp);
            }
        }
    }
};

/* Solution 3: cyclic replacement */
class Solution_CyclicReplacement {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 1;
        for(int i = 0 ; count<n ; i++){
            int cur = i;
            int prev = nums[i];
            do{
                int next = (cur+k) % n;
                int temp = nums[next];
                nums[next] = prev;
                prev = temp;
                cur = next;
                count ++;
            }while(cur != i);
            // print2d(nums);
        }
    }
};

/* Solution4. by reversing it
first, reverse whole array, then split array into two by index k, reverse those two array separately.
    1,2,3,4,5,6,7
s1. 7,6,5,4,3,2,1
s2. 5,6,7,1,2,3,4
*/
class Solution_Reverse {
private:
    void reverse(vector<int>& nums, int start, int end){
        int n = (end - start + 1) / 2;
        for(int i=0 ; i<n ; i++)
            swap(nums[start+i], nums[end-i]);
    }
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums, 0, n-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, n-1);
    }
};

TEST(Solution, Test){
    Solution_Reverse s;
    vector<int> v;

    v = {1,2,3,4,5,6,7};
    s.rotate(v, 3);
    EXPECT_EQ(v, vector<int>({5,6,7,1,2,3,4}));

    v = {-1,-100,3,99};
    s.rotate(v, 2);
    EXPECT_EQ(v, vector<int>({3,99,-1,-100}));
}

