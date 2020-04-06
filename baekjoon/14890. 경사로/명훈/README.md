# 경사로

## 문제 알고리즘

- 문제 구현 문제

## 풀이방법

1. 가로와 세로의 경우를 비교해서 문제를 풀었다.

2. 문제를 작은 경우로 나눠서 풀었다.

   * 다음 길의 높이가 현재의 길의 높이와 같은 경우, 길의 개수를 더해준다.

   * 다음 길의 높이가 현재의 길이와 2이상 차이나는 경우, 멈추고 이 길은 갈 수 없다고 판단한다.

   * 다음 길의 높이가 현재의 길이보다 1칸 높은 경우, 현재 높이가 지속된 갯수만큼 비교하고 L보다 작은 경우에는 멈추고 이 길은 갈 수 없다고 판단한다. 그 외의 경우에는 길의 개수를 1로 하고 넘어간다.

   * 다음 길의 높이가 현재의 길이보다 1칸 낮은 경우, 다음 길부터 L만큼의 거리를 비교해서 높이가 고정인지 확인하고 가능한 경우, 길의 갯수를 -L+1으로 하고 넘어간다.  이 경우가 아닌 경우는 멈춘다.

- 핵심 코드

```c++
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

```

## 문제 후 느낀점

- 문제 구현 문제.
- 생각보다 잘풀려서 기분이 좋았다.