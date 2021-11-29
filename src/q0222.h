#include "tree_node.h"

class Solution {
public:
    int getHeight(TreeNode* root){
        int height = 0;
        while(root != nullptr){
            height++;
            root = root->left;
        }
        return height;
    }
    bool exists(int height, int idx, TreeNode* root){
        const int n = pow(2,height-1);
        int l=0, r=n-1;
        while(height-1!=0){
            int mid = (l+r) / 2;
            if(idx > mid){
                l = mid+1;
                root = root->right;
            }else{
                r = mid;
                root = root->left;
            }
            height--;
        }
        return root!=nullptr;
    }
    int countNodes(TreeNode* root) {
        int h = getHeight(root);
        // cout << "h=" << h << endl;
        const int n = pow(2, h-1);
        int l=0, r=n-1;
        while(l<r){
            int mid = (l+r+1)/2;
            // printf("l=%d, r=%d, mid=%d\n", l, r, mid);
            // printf("exist(h,mid,root)= %d\n", exists(h, mid, root));
            if(exists(h, mid, root))
                l = mid;
            else
                r = mid-1;
        }
        return pow(2, h-1) -1 + l + 1;
    }
};

TEST(TestSolution, test1) {
    Solution s;

    TreeNode t{{1,2,3,4,5,6}};
    EXPECT_EQ(s.countNodes(&t), 6);

    EXPECT_EQ(s.countNodes(nullptr), 0);

    t = {{1}};
    EXPECT_EQ(s.countNodes(&t), 1);

}