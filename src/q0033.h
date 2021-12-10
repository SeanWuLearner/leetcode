/* Solution1: find min element first */
/* cases:
l<m<r, min = l
l<m>r, min is between m and r
l>m<r, min is between l and m
l>m>r, impossible.
*/
class Solution_2passes {
private:
    int findMinIndex(vector<int>& nums){
        int l = 0, r = nums.size() - 1;
        while(l<r){
            int m = (l+r) /2;
            if(nums[l] <= nums[m])
                if(nums[m] < nums[r])
                    return l;
                else
                    l = m+1;
            else
                r = m;
        }
        return l;
    }
public:
    int search(vector<int>& nums, int target) {
        int base = findMinIndex(nums);

        int n = nums.size();
        int l = 0, r = n-1;
        while(l <= r){
            int m = (l+r) / 2;
            int base_l = (l+base) % n;
            int base_r = (r+base) % n;
            int base_m = (m+base) % n;
            if(nums[base_m]==target)
                return base_m;
            else if(nums[base_m] < target)
                l = m+1;
            else
                r = m-1;
        }
        return -1;
    }
};

/* Solution 2: one pass binary search
    - nums[mid] == target, return mid;
    - nums[mid] < target
        if nums[mid] < nums[right], right part is sorted
                if(nums[right] > target), target is in right.
                    left = mid+1
                else
                    right = mid -1

        if nums[mid] > nums[right], right part is not sorted, still need to find right.
            left = mid+1

    - nums[mid] > target
        if nums[mid] > nums[left], left part is sorted
            if nums[left] < target, target in left part, search left
                right = mid-1
            else
                left = mid+1
        if nums[mid] <  nums[left], min on the left, find left
            right = mid -1
*/
class Solution_OnePass{
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l <= r){
            int m = (l+r) / 2;
            if(nums[m] == target)
                return m;
            else if(nums[m] < target){ //need to find greater
                if(nums[m] >= nums[l]) //left part is sorted
                    l = m+1;
                else{ //left part is not sorted
                    if(nums[r] >= target)
                        l = m+1;
                    else
                        r = m-1;
                }
            }else{ // need to find lesser
                if(nums[m] <= nums[r]) // right part is sorted
                    r = m-1;
                else{ //right part is not sorted, but left part is
                    if( target >= nums[l])
                        r = m-1;
                    else
                        l = m+1;
                }

            }
        }
        return -1;
    }
};
/* Solution2 : one pass still, refine the logic */
class Solution{
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l <= r){
            int m = (l+r) / 2;
            if(nums[m] == target)
                return m;
            if(nums[m] >= nums[l]){ // left part is sorted
                if(nums[m] > target && nums[l] <= target )
                    r = m-1;
                else
                    l = m+1;
            }else{ //right part is sorted
                if(nums[m] < target && nums[r] >= target)
                    l = m+1;
                else
                    r = m-1;
            }
        }
        return -1;
    }
};


TEST(Solution, Test1){
    Solution s;
    vector<int> q;

    q = {4,5,6,7,0,1,2};
    EXPECT_EQ(s.search(q, 0), 4);
    EXPECT_EQ(s.search(q, 3), -1);

    q = {1};
    EXPECT_EQ(s.search(q, 0), -1);
}