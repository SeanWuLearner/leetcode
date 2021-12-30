struct Node{
    Node():isEnd(false){
        fill(begin(next), end(next), nullptr);
    }

    Node *next[26];
    bool isEnd;
};

class WordDictionary {
private:
    Node *head;
public:
    WordDictionary() {
        head = new Node();
    }

    void addWord(string word) {
        Node *cur = head;
        for(auto c : word){
            int idx = c - 'a';
            if(cur->next[idx]==nullptr)
                cur->next[idx] = new Node();
            cur = cur->next[idx];
        }
        cur->isEnd = true;
    }

    bool search(string word) {
        return searchHelper(head, word, 0);
    }

    bool searchHelper(Node *cur, string& s, int start){
        for(int i=start ; i<s.length() ; i++){
            auto c = s[i];
            if(c == '.'){
                for(int j=0 ; j<26 ; j++){
                    if(cur->next[j] == nullptr) continue;
                    if(searchHelper(cur->next[j], s, i+1))
                        return true;
                }
                return false;
            }else{
                int c_idx = s[i] - 'a';
                if(cur->next[c_idx]==nullptr) return false;
                cur = cur->next[c_idx];
            }
        }
        return cur->isEnd;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

TEST(Solution, Test1){
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    EXPECT_EQ(dict.search("pad"), false);
    EXPECT_EQ(dict.search("bad"), true);
    EXPECT_EQ(dict.search(".ad"), true);
    EXPECT_EQ(dict.search("b.."), true);
}
