
/* excercise:
0: false
1: 1 true
2: 1->1 false
3: 1->1->1 true
4: 4 true
5: 4, lose, 1-->4 lose,  false
6: 4->1->1: win, 1,1,4, 1,4,1 true
7: 4,1,1,1 lose, 1,4,1,1 lose.false
8: 4,4 lose, 1,4,1,1,1 win, true
9: win true
10: 9, lose, 4, win, 1, lose

* It's a dp problem, however, in order to play it optimally,
    Alice expect dp[i] = true to WIN the game,
    Bob expect dp[i] = false to WIN the game.
* The possible way Alice win the game would be
    1. n - anyNumSquare = 0, no moves for Bob.
    2. dp[n - anyNumSquare] = false
    Two cases could be the same while we use DP array appropriately.
* like a backtracking problem.
in each recursion, we will iterate all possible num of removing, it anyone would lead to WINNING,
then it's a WIN.
*/

/*Solution 1: bottom-up dp.*/
class Solution1 {
public:
    bool winnerSquareGame(int n) {
        vector<bool> canWin(n+1);
        for(int i=0 ; i<=n ; i++){
            int seq=1;
            while(true){
                int draw = seq*seq;
                if(draw > i) break;
                if(canWin[i-draw]==false){
                    canWin[i] = true;
                    break;
                }
                seq++;
            }
        }
        return canWin[n];
    }
};

class Solution {
private:
    enum class MStat{
        NOT_SET, WIN, LOSE
    };
    bool canWin(int n, vector<MStat>& memo){
        if(n==0) return false;
        if(memo[n]!=MStat::NOT_SET) return memo[n]==MStat::WIN;

        memo[n] = MStat::LOSE;
        for(int i=1 ; i*i <= n ; i++){
            if(canWin(n-i*i, memo) == false){
                memo[n] = MStat::WIN;
                break;
            }
        }
        return memo[n]==MStat::WIN;
    }
public:
    bool winnerSquareGame(int n) {
        vector<MStat> memo(n+1, MStat::NOT_SET);
        return canWin(n, memo);
    }
};

TEST(Solution, test1){
    Solution s;

    EXPECT_EQ(s.winnerSquareGame(1), true);
    EXPECT_EQ(s.winnerSquareGame(2), false);
    EXPECT_EQ(s.winnerSquareGame(4), true);

}