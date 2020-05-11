#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int n_inning;
int Select[10];
int score[51][10];
int order[10];
vector<int> perm;
int base[5];
int total_score=0;
int max_score = -1;

void advance();
void Game();
void permutation(int cnt);
int main() {

    //freopen("input.txt", "r", stdin);
    scanf("%d", &n_inning);
    for (int i = 1; i <=n_inning; i++) {
        for (int j = 1; j <=9; j++) {
            scanf("%d", &score[i][j]);
        }
    }
    Select[4] = 1;
    order[4] = 1;
    permutation(2);
    printf("%d\n", max_score);
    
}
void advance() {
    for (int i = 3; i >= 0; i--) {
        base[i + 1] = base[i];
    }
    if (base[4] == 1) {
        base[4] = 0;
        total_score++;
    }
    base[0] = 0;
}
void Game() {
    int inning = 1;
    int out_cnt = 0;
    int play_order = 1;
    memset(base, 0, sizeof(base));
    while (1) {
        //printf("%3d이닝 %3d 아웃 현재점수(%3d) %3d번타자 (등번호%3d):",inning,out_cnt,total_score, play_order, order[play_order], score[inning][order[play_order]]);
        if (inning > n_inning) {
            //종료조건
        //    printf("score : %d\n", total_score);
            return;
        }
        int player_score = score[inning][order[play_order]];
        if (player_score == 0) {
        //    printf("아웃\n");
            out_cnt++;

        }
        else {
        //    printf("%d루타\n", score[inning][order[play_order]]);
            base[0] = 1;//베이스에 사람한명세우기
            for (int i = 0; i < player_score; i++) {
                advance();//진루
            }
            //base[score[inning][order[play_order]]] = 1;
        }
        if (out_cnt == 3) {//삼진아웃.
            out_cnt = 0;
            inning++;
            memset(base, 0, sizeof(base));
        }
        play_order = play_order % 9 + 1;//다음선수

    }

}
void permutation(int cnt) {
    if (cnt == 10) {
        total_score = 0;
        Game();
        max_score = max(max_score, total_score);
        return;
    }
    for (int i = 1; i < 10; i++) {
        if (Select[i] == 1)
            continue;
        Select[i] = 1;
        order[i] = cnt;
        permutation(cnt + 1);
        Select[i] = 0;
    }
}
