# 17135 캐슬디펜스

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83347508-6848a280-a360-11ea-85ca-f7b27358931f.png)

## 문제 알고리즘

- 시뮬레이션

## 풀이방법

1. 궁수의 위치를 `next_permuation` 을 이용하여 combination을 구한다.

2. 적군을 죽이는 단계인 `kill()` 단계와 적군이 움직이는 `move()` 단계로 나누어서 문제를 푼다.

- 핵심 코드

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 15;

int N, M, D;
int board[MAX][MAX];
int cpyBoard[MAX][MAX];
int killEnemey, cnt, answer;
vector<int> ind;

// check is in board
bool isInBoard(int y, int x)
{
    if (y < 0 || y >= N || x < 0 || x >= M)
        return false;
    return true;
}

// kill enemy
int kill(vector<int> archer)
{
    // deadList is enemy who is killed by archer
    int deadList[3] = {-1, -1, -1};
    // index is archer's number
    for (int index = 0; index < 3; index++)
    {
        for (int len = 0; len < D; len++)
        { //  d is length
            bool flag = false;
            // 왼쪽부터 탐색
            for (int dx = -1 * len; dx <= len; dx++)
            {
                int dy = len - abs(dx);
                int nY = (N - 1) - dy;
                int nX = archer[index] + dx;
                if (isInBoard(nY, nX) && cpyBoard[nY][nX] == 1)
                {
                    deadList[index] = nY * 100 + nX;
                    flag = true;
                    break;
                }
            }
            if (flag == true)
                break;
        }
    }

    // check dead enemy
    int cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (deadList[i] == -1) // no kill
            continue;
        int curY = deadList[i] / 100;
        int curX = deadList[i] % 100;
        if (cpyBoard[curY][curX] == 1)
        {
            cpyBoard[curY][curX] = 0;
            cnt++;
        }
    }
    return cnt;
}

// move
void move()
{
    for (int i = N - 1; i >= 1; i--)
    {
        for (int j = 0; j < M; j++)
            cpyBoard[i][j] = cpyBoard[i - 1][j];
    }
    for (int j = 0; j < M; j++)
        cpyBoard[0][j] = 0;
}

int main(int argc, const char *argv[])
{
    // input
    scanf("%d %d %d", &N, &M, &D);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &board[i][j]);

    for (int i = 0; i < M - 3; i++)
        ind.push_back(0);
    for (int i = 0; i < 3; i++)
        ind.push_back(1);

    // solution
    do
    {
        // cnt : kill enemy
        cnt = 0;
        // make archer commbination
        vector<int> archer;
        for (int i = 0; i < ind.size(); i++)
            if (ind[i] == 1)
                archer.push_back(i);

        // copy board -> cpyBoard
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cpyBoard[i][j] = board[i][j];

        // (kill -> move)
        for (int i = 0; i < N; i++)
        {
            cnt += kill(archer); // kill enemy
            move();              // move
        }

        if (answer < cnt)
            answer = cnt;

    } while (next_permutation(ind.begin(), ind.end()));

    // output
    cout << answer << "\n";

    return 0;
}
```

## 문제 후 느낀점

- 중간에 적 제거 logic을 잘못 이해해서 정답률이 내려갔다.
