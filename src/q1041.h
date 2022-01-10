/* Solution 1: vector like approach?
Ex1.
    GGLLG

    0,0 -> 0,2 -> 0,1 head north(i,e 180)
    0,1 -> 0,-1, -> 0,0 : found loop.

Ex2.
    GGRG
    0,0 -> 1,2 head R
    1,2 -> 3,1 head

Algorithm:
    L -> +1 , R -> -1 , while the end of instructions, if the robot head north and offset is not
    0, then it doesn't have a bound.

    G : y+1 while go north : 0
        x-1 while go west: 1
        y-1 while go south : 2
        x+1 while go east : 3

    the dir always need to be round up to positive int.
*/
class Solution1 {
public:
    bool isRobotBounded(string instructions) {
        int x=0, y=0, dir=0;

        for(char c : instructions){
            if(c=='G'){
                switch(dir){
                    case 0:
                        y++;
                        break;
                    case 1:
                        x--;
                        break;
                    case 2:
                        y--;
                        break;
                    case 3:
                        x++;
                }
            }else{
                dir += (c=='L')? 1:-1;
                if(dir < 0) dir+=4;
                if(dir == 4) dir=0;
            }
        }
        if(dir==0 && x+y != 0)
            return false;
        else
            return true;
    }
};
/* Solution 2: same idea, concise code */
class Solution{
public:
    bool isRobotBounded(string instructions) {
        int dir=0, coord[2]={0,0};
        const int ofs[][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}};
        for(char c : instructions){
            if(c=='G'){
                coord[0] += ofs[dir][0];
                coord[1] += ofs[dir][1];
            }else{
                dir += (c=='L')? 1: 3;
                dir %= 4;
            }
        }
        return (dir==0 && (coord[0]+coord[1]) != 0)? false : true;
    }
};

TEST(Solution, Test1){
    Solution s;
    EXPECT_EQ(s.isRobotBounded("GGLLGG"), true);
    EXPECT_EQ(s.isRobotBounded("GG"), false);
    EXPECT_EQ(s.isRobotBounded("GLRLLGLL"), true);
}
