#include <unordered_map>

/* my solution */
struct DListNode{
    int val;
    DListNode *prev;
    DListNode *next;
    DListNode(int val): val(val){}
};

class LRUQueue{
    DListNode *front, *back;
public:
    LRUQueue(){
        front = back = nullptr;
    }

    void push(DListNode *node){
        if(back==nullptr){
            front = back = node;
        }else{
            back->next = node;
            node->prev = back;
            back = node;
        }
    }
    DListNode* pop(){
        DListNode *node = front;
        if(front == nullptr){
            return nullptr;
        }else if(front == back){
            front = back = nullptr;
        }else{
            front->next->prev = nullptr;
            front = front->next;
        }
        return node;
    }
    void touch(DListNode *node){
        if(node == back)
            return;
        if(node == front){
            DListNode* node = pop();
            push(node);
        }else{
            node->prev->next = node->next;
            node->next->prev = node->prev;
            push(node);
        }
    }

    void dump(){
        DListNode *cur = front;
        while(true){
            if(cur == nullptr){
                printf("null");
                break;
            }
            printf("%d -> ", cur->val);
            if(cur == back)
                break;
            cur = cur->next;
        }
        printf("\n");
    }
};

class LRUCache_My {
private:
    LRUQueue q;
    unordered_map<int, pair<int, DListNode*>> dict;
    int capacity;

public:
    LRUCache_My(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto it = dict.find(key);
        if(it == dict.end())
            return -1;
        else{
            q.touch(it->second.second);
            return it->second.first;
        }
    }

    void put(int key, int value) {
        auto it = dict.find(key);
        if(it == dict.end()){
            DListNode *node = new DListNode(key);
            dict[key] = make_pair(value, node);
            q.push(node);
        }else{
            it->second.first = value;
            q.touch(it->second.second);
        }

        if(dict.size() > capacity){
            DListNode *node = q.pop();
            dict.erase(node->val);
            delete node;
        }
    }
};

/* clear and precise ans from discussion */
#include <list>
using LI = list<int>; //key
using MII = unordered_map<int, int>; //map key to value
using MILI = unordered_map<int, LI::iterator>; // map key to iter

class LRUCache {
private:
    LI lru;
    MII val_dict;
    MILI iter_dict;
    int cap;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if(val_dict.count(key)==0)
            return -1;
        updateLRU(key);
        return val_dict[key];
    }

    void put(int key, int value) {
        if(lru.size() == cap && val_dict.count(key)==0)
            evict();
        updateLRU(key);
        val_dict[key] = value;
    }
private:
    void updateLRU(int key){
        if(iter_dict.count(key)!= 0)
            lru.erase(iter_dict[key]);
        lru.push_front(key);
        iter_dict[key] = lru.begin();
    }
    void evict(){
        int key = lru.back();
        iter_dict.erase(key);
        val_dict.erase(key);
        lru.pop_back();
    }
};

TEST(TestSolution, test1) {

    LRUCache obj(2);
    obj.put(1,1);
    obj.put(2,2);
    EXPECT_EQ(obj.get(1), 1);
    obj.put(3,3);
    EXPECT_EQ(obj.get(2), -1);
    obj.put(4,4);
    EXPECT_EQ(obj.get(1), -1);
    EXPECT_EQ(obj.get(3), 3);
    EXPECT_EQ(obj.get(4), 4);
}