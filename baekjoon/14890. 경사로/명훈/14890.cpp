#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

int N, L;
int board[MAX][MAX];
int answer = 0;


int main(int argc, const char * argv[]) {
    // input
    cin >> N >> L;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%d", &board[i][j]);
    
    // solution
    for(int i=0; i<N; i++){ // row
        int board_height = board[i][0];
        int cnt = 0;
        bool flag = false;
        for(int j=0; j<N; j++){
            if(board[i][j] == board_height){
                // if height is same, continue;
                cnt++;
                continue;
            }
            else if(board[i][j] >= board_height + 2 || board[i][j] <= board_height - 2){
                // if height's difference is over 2, break. this is fail road.
                flag = true;
                break;
            }
            else if(board[i][j] == board_height + 1){
                // if board[i][j] = board_height + 1,
                board_height = board[i][j];
                if(cnt < L){
                    flag = true;
                    break;
                }
                cnt = 1;
            }
            else if(board[i][j] == board_height - 1){
                // if board[i][j] = board_height - 1,
                board_height = board[i][j];
                for(int k=j; k<j+L; k++){
                    if(k >= N){
                        flag = true;
                        break;
                    }
                    if(board[i][k] != board_height){
                        flag = true;
                        break;
                    }
                }
                if(flag)
                    break;
                cnt = (-1) * L + 1;
            }
        }
        if(!flag)
            answer++;
    }

    for(int j=0; j<N; j++){ // col
        int board_height = board[0][j];
        int cnt = 0;
        bool flag = false;
        for(int i=0; i<N; i++){
            if(board[i][j] == board_height){
                // if height is same, continue;
                cnt++;
                continue;
            }
            else if(board[i][j] >= board_height + 2 || board[i][j] <= board_height - 2){
                // if height's difference is over 2, break. this is fail road.
                flag = true;
                break;
            }
            else if(board[i][j] == board_height + 1){
                // if board[i][j] = board_height + 1,
                board_height = board[i][j];
                if(cnt < L){
                    flag = true;
                    break;
                }
                cnt = 1;
            }
            else if(board[i][j] == board_height - 1){
                // if board[i][j] = board_height - 1,
                board_height = board[i][j];
                for(int k=i; k<i+L; k++){
                    if(k >= N){
                        flag = true;
                        break;
                    }
                    if(board[k][j] != board_height){
                        flag = true;
                        break;
                    }
                }
                if(flag)
                    break;
                cnt = (-1) * L + 1;
            }
        }
        if(!flag)
            answer++;
    }
    
    // output
    cout << answer << "\n";
    
    return 0;
}
