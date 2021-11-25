/*DP solution*/
class DpSolution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> max_l(n), max_r(n);
        int ans = 0;

        //compute max_l
        int maxheight = 0;
        for(int i=0 ; i<n ; i++){
            max_l[i] = maxheight;
            maxheight = max(maxheight, height[i]);
        }

        //compute max_r
        maxheight = 0;
        for(int i=n-1 ; i>=0 ; i--){
            max_r[i] = maxheight;
            maxheight = max(maxheight, height[i]);
        }

        //accumulate water volume
        for(int i=0 ; i<n ; i++){
            int wall_height = min(max_r[i], max_l[i]);
            if(wall_height > height[i])
                ans += wall_height - height[i];
        }
        return ans;
    }
};

/*two pointer solution*/
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size()-1;
        int ans = 0;
        int max_l = 0, max_r = 0;
        while(left < right){
            if(height[left] < height[right]){
                if(height[left] > max_l)
                    max_l = height[left];
                else
                    ans += max_l - height[left];
                left++;
            }else{
                if(height[right] > max_r)
                    max_r = height[right];
                else
                    ans += max_r - height[right];
                right--;
            }
        }
        return ans;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> h;

    h = {0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(s.trap(h), 6);

    h = {4,2,0,3,2,5};
    EXPECT_EQ(s.trap(h), 9);


}