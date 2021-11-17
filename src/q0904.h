class MyNaiveSolution {
public:
    int totalFruit(vector<int>& fruits) {
        int types[2]={-1,-1};
        int starts[2]={100001, 100001};
        int seg_starts[2];
        int max_num = 0, prev = -1;
        bool in_init;
        int op_idx;
        int i=0;
        for(i=0 ; i<fruits.size() ; i++){
            if(prev != fruits[i]){
                if(fruits[i]==types[0]){
                    seg_starts[0] = i;
                }else if(fruits[i]==types[1]){
                    seg_starts[1] = i;
                }else{
                    //neither match
                    // init case
                    in_init = false;
                    if(types[0] < 0)
                    {
                        in_init = true;
                        op_idx = 0;
                    }else if(types[1] < 0){
                        in_init = true;
                        op_idx = 1;
                    }else{
                        op_idx = (fruits[i-1]==types[0])? 1 : 0;
                    }

                    if(in_init == false){
                        int stay_idx = (op_idx==0)? 1:0;
                        max_num = max(max_num, i-min(starts[0], starts[1]));
                        starts[stay_idx] = seg_starts[stay_idx];
                    }
                    types[op_idx] = fruits[i];
                    seg_starts[op_idx] = starts[op_idx] = i;
                }
            }
            prev = fruits[i];
        }
        max_num = max(max_num, i-min(starts[0], starts[1]));
        return max_num;
    }
};

/* Very neat solution from discussion
    1. Keep track the previous fruit and the cnt when the transistion happens.
    2. Use two variables last and sec_last to work like a queue which discards
       oldest fruit gracefully.
*/
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int last = -1, sec_last = -1;
        int max_cnt = 0, cur_cnt = 0;
        int last_cnt = 0;
        for(auto f : fruits){
            if(f == last){
                cur_cnt++; last_cnt++;
            }else{
                if(f == sec_last){
                    cur_cnt++;
                    last_cnt = 1;
                }else{
                    cur_cnt = last_cnt + 1;
                    last_cnt = 1;
                }
                sec_last = last;
                last = f;
            }
            max_cnt = max(max_cnt, cur_cnt);
        }
        return max_cnt;
    }
};

TEST(TestSolution, test1) {
    Solution s;
    vector<int> fruits{1,2,1};
    EXPECT_EQ(s.totalFruit(fruits), 3);

    fruits = {0,1,2,2};
    EXPECT_EQ(s.totalFruit(fruits), 3);

    fruits = {1,2,3,2,2};
    EXPECT_EQ(s.totalFruit(fruits), 4);

    fruits = {3,3,3,1,2,1,1,2,3,3,4};
    EXPECT_EQ(s.totalFruit(fruits), 5);
}
