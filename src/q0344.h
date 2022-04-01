/* Solution 1: mine*/
class Solution1 {
public:
    void reverseString(vector<char>& s) {
        for(int i=0; i<s.size()/2 ; i++){
            int j=s.size()-1-i;
            swap(s[i], s[j]);
        }
    }
};

/* Solution 2: neater*/
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i=0, j=s.size()-1;
        while(i<j){
            swap(s[i++], s[j--]);
        }
    }
};

TEST(Solution, Test1){
    Solution s;
    vector<char> q, exp;

    q = {'h','e','l','l','o'};
    exp = {'o','l','l','e','h'};
    s.reverseString(q);
    EXPECT_EQ(exp, q);

    q = {'H','a','n','n','a','h'};
    exp = {'h','a','n','n','a','H'};
    s.reverseString(q);
    EXPECT_EQ(exp, q);
}