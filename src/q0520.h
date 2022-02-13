/* Solution1 : determine case at the beginning.*/
class Solution1 {
public:
    bool detectCapitalUse(string word) {
        if(word.length() <=1 ) return true;
        /* state = 0 : all little letters
                  1 : First letter is Capital
                  2 : All Capital
        */
        int state=(word[0]>= 'a')? 0 : (word[1]>='a')? 1 : 2 ;
        for(int i=1 ; i<word.length(); i++){
            if(word[i]>='a'){
                if(state==2){
                    return false;
                }
            }else{
                if(state==0 || state==1){
                    return false;
                }
            }
        }
        return true;
    }
};

/* Solution2 : cnt the num of upper letters, and a bool to indicate whether it
               contains little case letter.*/
class Solution {
public:
    bool detectCapitalUse(string word) {
        bool met_little = false;
        int cnt_upper = 0;
        for(auto &&c : word){
            if(c >= 'a'){
                met_little = true;
            }else{
                cnt_upper++;
                if(met_little)
                    return false;
            }
        }
                //all upper cases    || all lower case || Cap the first letter
        return (met_little == false) || cnt_upper==0 || cnt_upper==1;
    }
};


TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(true, s.detectCapitalUse("USA"));
    EXPECT_EQ(false, s.detectCapitalUse("FlaG"));
    EXPECT_EQ(true, s.detectCapitalUse("Google"));
    EXPECT_EQ(true, s.detectCapitalUse("google"));
    EXPECT_EQ(false, s.detectCapitalUse("gooGle"));
    EXPECT_EQ(false, s.detectCapitalUse("GOogle"));
}