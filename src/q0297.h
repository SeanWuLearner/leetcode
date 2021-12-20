#include "tree_node.h"
#include <sstream>

class Codec {
public:

    void serHelper(stringstream &ss, TreeNode* root){
        if(root == nullptr){
            ss << "N ";
            return;
        }
        ss << root->val << " ";
        serHelper(ss, root->left);
        serHelper(ss, root->right);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream ss;
        serHelper(ss, root);
        return ss.str();
    }

    TreeNode* desHelper(stringstream &ss){
        string data;
        ss >> data;
        if(data == "N")
            return nullptr;
        TreeNode *cur = new TreeNode(stoi(data));
        cur->left = desHelper(ss);
        cur->right = desHelper(ss);
        return cur;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss{data};
        return desHelper(ss);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
TEST(Solution, Test1){
    Codec codec;
    TreeNode root1{{1,2,3,NULL_TNODE,NULL_TNODE,4,5}};
    EXPECT_EQ(*codec.deserialize(codec.serialize(&root1)), root1);
}

TEST(Solution, Test2){
    Codec codec;
    EXPECT_EQ(codec.deserialize(codec.serialize(nullptr)), nullptr);
}

TEST(Solution, Test3){
    Codec codec;
    TreeNode root1{{1}};
    EXPECT_EQ(*codec.deserialize(codec.serialize(&root1)), root1);
}

TEST(Solution, Test4){
    Codec codec;
    TreeNode root1{{1,2}};
    EXPECT_EQ(*codec.deserialize(codec.serialize(&root1)), root1);
}