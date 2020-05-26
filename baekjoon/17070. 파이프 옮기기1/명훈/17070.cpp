#include <iostream>

using namespace std;

#define MAX 16

int dx[3] = {1, 0, 1};
int dy[3] = {0, 1, 1};

int n, result = 0;
int arr[MAX][MAX];

void check(int x, int y, int pipe)
{
    if (x == n - 1 && y == n - 1)
    {
        result++;
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        // not possible that horizont <-> vertical
        if ((i == 0 && pipe == 1) || (i == 1 && pipe == 0))
            continue;

        int next_x = x + dx[i];
        int next_y = y + dy[i];

        // if next is out of range or wall, continue
        if (next_x >= n || next_y >= n || arr[next_y][next_x])
            continue;

        // if diagonal, check
        if (i == 2 && (arr[y + 1][x] || arr[y][x + 1]))
            continue;

        check(next_x, next_y, i);
    }
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    check(1, 0, 0);

    cout << result << "\n";

    return 0;
}