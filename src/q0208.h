
class Trie {
    struct TNode{
        TNode *next[26] = {0};
        bool isEnd = false;
    };
private:
    TNode *head;
public:
    Trie() {
        head = new TNode();
    }
    ~Trie(){
        delete head;
    }

    void insert(string word) {
        TNode *node = head;
        for(auto&& c : word){
            auto&& next = node->next[c - 'a'];
            if(next == nullptr)
                next = new TNode();
            node = next;
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TNode *node = head;
        for(auto&& c : word){
            auto&& next = node->next[c - 'a'];
            if(next == nullptr)
                return false;
            node = next;
        }
        return node->isEnd;
    }

    bool startsWith(string prefix) {
        TNode *node = head;
        for(auto&& c : prefix){
            auto&& next = node->next[c - 'a'];
            if(next == nullptr)
                return false;
            node = next;
        }
        return true;
    }
};


 TEST(TestSolution, test1) {
    Trie t;
    t.insert("apple");
    EXPECT_EQ(t.search("apple"), true);
    EXPECT_EQ(t.search("app"), false);
    EXPECT_EQ(t.startsWith("app"), true);
    t.insert("app");
    EXPECT_EQ(t.search("app"), true);
}