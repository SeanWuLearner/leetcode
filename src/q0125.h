/* solution 1, preprocess the string first */
class Solution_WithPreprocess {
private:
    string dropNonAlphaNum(string& s){
        string res;
        for(auto c : s){
            if((c>='0' && c<='9') || (c>='a' && c<= 'z'))
                res+= c;
        }
        return res;
    }
public:
    bool isPalindrome(string s) {
        //to lower case
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        s = dropNonAlphaNum(s);

        //check palindrome
        int l = 0, r = s.length()-1;
        while(l<r){
            if(s[l++]!=s[r--])
                return false;
        }
        return true;
    }
};
/* Solution2: without preprocess*/
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.length()-1;
        while(l<r){
            if(!isalnum(s[l]))
                l++;
            else if(!isalnum(s[r]))
                r--;
            else{
                if(tolower(s[l]) != tolower(s[r])) return false;
                l++; r--;
            }
        }
        return true;
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    bool exp;

    q = "A man, a plan, a canal: Panama";
    exp = true;
    EXPECT_EQ(exp, s.isPalindrome(q));

    q = "race a car";
    exp = false;
    EXPECT_EQ(exp, s.isPalindrome(q));

    q = " ";
    exp = true;
    EXPECT_EQ(exp, s.isPalindrome(q));
}