#include <unordered_set>

class MySolution {
public:
    int numUniqueEmails(vector<string>& emails) {
        size_t at_idx;
        string strbuf;
        unordered_set<string> sets;

        for(auto&& email: emails){
            strbuf.clear();
            at_idx = email.find("@");
            for(int i=0; i<at_idx; i++){
                if(email[i]=='.') continue;
                if(email[i]=='+') break;
                strbuf += email[i];
            }
            strbuf += email.substr(at_idx, email.length() - at_idx);
            sets.insert(strbuf);
        }
        return sets.size();
    }
};

/* 4ms solution*/
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> sets;

        for(auto&& email: emails){
            string strbuf;
            for(char c: email){
                if(c=='.') continue;
                if(c=='+' || c=='@') break;
                strbuf += c;
            }
            strbuf += email.substr(email.find("@"));
            sets.insert(strbuf);
        }
        return sets.size();
    }
};


TEST(TestSolution, test1) {
    Solution s;
    vector<string> mails{"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
    EXPECT_EQ(s.numUniqueEmails(mails), 2);

    mails = {"a@leetcode.com","b@leetcode.com","c@leetcode.com"};
    EXPECT_EQ(s.numUniqueEmails(mails), 3);
}
