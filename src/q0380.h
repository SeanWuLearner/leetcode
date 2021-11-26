#include <unordered_set>

/*
    I didn't managed to come out this solution by myself.
    The key to come out this solution would be :
    When remove() get called, how to maintain or modify your set to make it 
    still index-able between 0-n. --> That is, alway drop the back.
*/
class RandomizedSet {
    unordered_map<int, int> idx_map;
    vector<int> data;
public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        //it seems using find() would be faster?!
        if(idx_map.count(val) != 0) return false;
        idx_map[val] = data.size();
        data.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        //it seems using find() would be faster?!
        if(idx_map.count(val) == 0) return false;
        int idx = idx_map[val];
        int last_elem = data[data.size() - 1];
        data[idx] = last_elem;  //move last element to the element we want to remove;
        idx_map[last_elem] = idx;
        idx_map.erase(val);
        data.pop_back();
        return true;
    }
    
    int getRandom() {
        return data[rand() % data.size()];
    }
};


 TEST(TestSolution, test1) {
    RandomizedSet* obj = new RandomizedSet();
    
    EXPECT_EQ(obj->insert(1), true);
    EXPECT_EQ(obj->remove(2), false);
    EXPECT_EQ(obj->insert(2), true);
    int ran = obj->getRandom();
    EXPECT_EQ((ran==1 || ran==2), true);
    EXPECT_EQ(obj->remove(1), true);
    EXPECT_EQ(obj->insert(2), false);
    EXPECT_EQ(obj->getRandom(), 2);
}

 TEST(TestSolution, test2) {
    RandomizedSet* obj = new RandomizedSet();
    
    EXPECT_EQ(obj->remove(0), false);
    EXPECT_EQ(obj->remove(0), false);
    EXPECT_EQ(obj->insert(0), true);
    EXPECT_EQ(obj->getRandom(), 0);
    EXPECT_EQ(obj->remove(0), true);
    EXPECT_EQ(obj->insert(0), true);

}