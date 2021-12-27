/* Solution 1: my naive one.
data struct
    vector<int> wordlen // wordlen accumulate to that given level
        ex, dir/123/456 , wordlen[] = {3,7,11};

logic:
    1. initially, find first '\n' or end of s, extract and determine it's dir or file
    update wordlen array (init level = 0).
    2. after that, count the num of following '\t' = level
    find '\n' or end of s ==> extract dirname or filename and put the acc strlen to wordlen
    array.
*/
class Solution_myMemo {
public:
    int lengthLongestPath(string input) {
        vector<int> acc;
        int i = 0, j;
        int level = 0;
        int max_len = 0;
        while(i<input.length()){
            bool isfile = false;
            for(j=i ; j<input.length() && input[j]!='\n' ; j++){
                if(input[j] == '.')
                    isfile = true;
            }
            int prev_len = (level==0)? 0 : acc[level-1];
            int acc_len = prev_len + (j-i) + ((level==0)? 0 : 1);
            if(acc.size() < level+1)
                acc.push_back(acc_len);
            else
                acc[level] = acc_len;
            if(isfile)
                max_len = max(max_len, acc_len);
            i = j+1;
            //find next level
            if(i>= input.length()) break;
            level = 0;
            while(input[i]=='\t'){
                level++;
                i++;
            }
        }
        return max_len;
    }
};

/* Solution 2: same idea, but more concise, modulized */
#include <sstream>
class Solution {
private:
    int get_level(string& s){
        int tabnum = 0;
        for(auto&& c : s){
            if(c!= '\t')
                break;
            tabnum++;
        }
        return tabnum;
    }
    bool isfile(string& s, int startIdx){
        for(int i=startIdx ; i<s.length(); i++)
            if(s[i]=='.') return true;
        return false;
    }
public:
    int lengthLongestPath(string input) {
        istringstream iss(input);
        string line;
        int level;
        int maxlen = 0;
        vector<int> pathlen(1);  // the root path would be at pathlen[1]
        while(getline(iss, line, '\n')){
            level = get_level(line);
            if(isfile(line, level)){
                int acclen = pathlen[level] +  line.size() - level;
                maxlen = max(maxlen, acclen);
            }else{
                int acclen = pathlen[level] +  1 + line.size() - level;
                if(pathlen.size() <= level+1)
                    pathlen.push_back(acclen);
                else
                    pathlen[level+1] = acclen;
            }
        }
        return maxlen;
    }
};

TEST(Solution, Test1){
    Solution s;
    string q;
    int exp;

    q = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
    exp = 20;
    EXPECT_EQ(s.lengthLongestPath(q), exp);


    q = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
    exp = 32;
    EXPECT_EQ(s.lengthLongestPath(q), exp);

    q = "a";
    exp = 0;
    EXPECT_EQ(s.lengthLongestPath(q), exp);
}