# 17144 미세먼지 안녕!

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83346208-73e29c00-a355-11ea-8d29-cfbfc3c5688a.png)

## 문제 알고리즘

- 시뮬레이션

## 풀이방법

1. 문제에서 요구하는 대로 spread() 단계와 cleanup() 단계로 두 단계로 나눠 문제를 해결한다.

- 핵심 코드

```c++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAX = 50 + 1;
const int dy[] = {0, -1, 0, 1};
const int dx[] = {1, 0, -1, 0};

int R, C, T;
int airPurifierY, airPurifierX;
int board[MAX][MAX];

// check it is in board
// (y, x) => boolean
bool isInBoard(int y, int x)
{
    if (board[y][x] == -1)
        return false;
    if (y < 0 || y >= R || x < 0 || x >= C)
        return false;
    return true;
}

// spread fine dust
void spread()
{
    int cpyBoard[MAX][MAX] = {};

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (board[i][j] > 0)
            {
                // if any fine dust is in board[i][j]
                // spread this fine dust
                int cnt = 0;
                for (int dir = 0; dir < 4; dir++)
                {
                    int nextY = i + dy[dir];
                    int nextX = j + dx[dir];
                    if (isInBoard(nextY, nextX))
                    {
                        cpyBoard[nextY][nextX] += board[i][j] / 5;
                        cnt++;
                    }
                }
                board[i][j] -= cnt * (board[i][j] / 5);
            }

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            board[i][j] += cpyBoard[i][j];
}

// clean up
void cleanUp()
{
    // air purifier is in (y-1, x), (y, x)
    board[airPurifierY - 1][airPurifierX] = 0;
    board[airPurifierY][airPurifierX] = 0;

    // move counter clockwise
    for (int i = airPurifierY - 2; i >= 1; i--) // down
        board[i][0] = board[i - 1][0];
    for (int j = 0; j < C - 1; j++) // left
        board[0][j] = board[0][j + 1];
    for (int i = 0; i < airPurifierY - 1; i++) // up
        board[i][C - 1] = board[i + 1][C - 1];
    for (int j = C - 1; j >= 1; j--) // right
        board[airPurifierY - 1][j] = board[airPurifierY - 1][j - 1];
    board[airPurifierY - 1][1] = 0;

    // move clockwise
    for (int i = airPurifierY + 1; i < R - 1; i++) // up
        board[i][0] = board[i + 1][0];
    for (int j = 0; j < C - 1; j++) // left
        board[R - 1][j] = board[R - 1][j + 1];
    for (int i = R - 1; i > airPurifierY; i--) // down
        board[i][C - 1] = board[i - 1][C - 1];
    for (int j = C - 1; j >= 1; j--) // right
        board[airPurifierY][j] = board[airPurifierY][j - 1];
    board[airPurifierY][1] = 0;
}

int main(int argc, const char *argv[])
{
    // input
    scanf("%d %d %d", &R, &C, &T);
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == -1)
            {
                airPurifierY = i;
                airPurifierX = j;
            }
        }
    }

    // solution
    while (T--)
    {
        spread();
        cleanUp();
    }
    int sum = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            sum += board[i][j];

    // output
    cout << sum << "\n";

    return 0;
}
```

## 문제 후 느낀점

- 옛날에 풀었던 문제 재정리했음
