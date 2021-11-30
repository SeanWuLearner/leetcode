
class MySolution {
public:
    vector<int> partitionLabels(string s) {
        int memo[26]={0};
        for(int i=0 ; i<s.length(); i++){
            memo[s[i] - 'a'] = i;
        }
        vector<int> parts;
        for(int i=0 ; i<s.length(); ){
            int end_idx = memo[s[i] - 'a'];
            for(int j=i+1 ; j<end_idx ; j++){
                end_idx = max(end_idx, memo[s[j] - 'a']);
            }
            parts.push_back(end_idx-i+1);
            i = end_idx + 1;
        }
        return parts;
    }
};

/* neater solution from discussion */
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int memo[26]={0};
        for(int i=0 ; i<s.length(); i++){
            memo[s[i] - 'a'] = i;
        }
        vector<int> parts;
        int start_idx = 0, end_idx = 0;
        for(int i=0 ; i<s.length(); i++){
            end_idx = max(end_idx, memo[s[i] - 'a']) ;
            if(i == end_idx){
                parts.push_back(i-start_idx+1);
                start_idx = i + 1;
            }
        }
        return parts;
    }
};

TEST(TestSolution, test1) {
    Solution s;

    EXPECT_EQ(s.partitionLabels("ababcbacadefegdehijhklij"), vector<int>({9,7,8}));
    EXPECT_EQ(s.partitionLabels("eccbbbbdec"), vector<int>({10}));

}