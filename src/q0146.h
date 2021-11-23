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

class LRUCache {
private:
    LRUQueue q;
    unordered_map<int, pair<int, DListNode*>> dict;
    int capacity;

public:
    LRUCache(int capacity) {
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