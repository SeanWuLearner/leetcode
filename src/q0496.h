#include <stack>
#include <unordered_map>

class MySolution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        stack<int> stk;
        unordered_map<int,int> nge; //next great element

        //fill NGE table
        for(int n : nums2){
            while(stk.empty()!=true && stk.top() < n){
                nge[stk.top()] = n;
                stk.pop();
            }
            stk.push(n);
        }

        //fill ans
        for(int n : nums1){
            auto it = nge.find(n);
            if(it==nge.end())
                ans.push_back(-1);
            else
                ans.push_back(it->second);
        }
        return ans;
    }
};


using ::testing::ElementsAre;

/*faster while doing it reversely.*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        stack<int> stk;
        unordered_map<int,int> nge; //next great element

        //fill NGE table
        for(auto it = nums2.rbegin(); it!=nums2.rend(); it++){
            while(stk.size()!=0 && stk.top() <= *it)
                stk.pop();
            if(stk.empty()!=true)
                nge[*it] = stk.top();
            stk.push(*it);
        }

        //fill ans
        for(int n : nums1){
            auto it = nge.find(n);
            if(it==nge.end())
                ans.push_back(-1);
            else
                ans.push_back(it->second);
        }
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> nums1, nums2;

    nums1 = {4,1,2};
    nums2 = {1,3,4,2};
    ASSERT_THAT(s.nextGreaterElement(nums1, nums2), ElementsAre(-1,3,-1));

    nums1 = {2,4};
    nums2 = {1,2,3,4};
    ASSERT_THAT(s.nextGreaterElement(nums1, nums2), ElementsAre(3,-1));
}