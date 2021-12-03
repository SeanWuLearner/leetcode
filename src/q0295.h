class MedianFinder {
private:
    multiset<int> greater;
    multiset<int, std::greater<int>> lesser;
    int n;
public:
    MedianFinder() {
        n = 0;
    }

    void addNum(int num) {
        /*
            lesser.size() = k, greater.size() = k
                1. lesser.size() = k+1 , greater.size() = k  ==> let's cool
                2. lesser.size() = k, greater.size() = k+1 ==> we need to move one elem to lesser.
            lesser.size() = k+1, greater.size() = k
                1. lesser.sizer() = k+2 , greater.size() = k ==> we need to move one elem to greater
                2. lesser.size() = k+1, greater.size() = k+1 ==> we are cool.
        */
        if(lesser.empty()==true || (lesser.empty()!= true && num < *lesser.begin() )){
            lesser.insert(num);
            if(lesser.size() > greater.size()+1){
                greater.insert(*lesser.begin());
                lesser.erase(lesser.begin());
            }
        }else{
            greater.insert(num);
            if(greater.size() > lesser.size()){
                lesser.insert(*greater.begin());
                greater.erase(greater.begin());
            }
        }
        n++;
    }

    double findMedian() {
        if(n%2 != 0)
            return *lesser.begin();
        else
            return (*lesser.begin() + *greater.begin()) / 2.0;
    }
};

TEST(Solution, Test1){
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    EXPECT_EQ(mf.findMedian(), 1.5);
    mf.addNum(3);
    EXPECT_EQ(mf.findMedian(), 2.0);
}

