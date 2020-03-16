#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
int TARGET = 123456789;
typedef struct
{
    int y;
    int x;   
}Dir;

Dir moveDir[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main(void)
{
    int start = 0; //시작할 때 순열
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int num;
            cin >> num;
            //빈 칸을 9로 표시
            if (num == 0)
                num = 9;
            start = start * 10 + num;
        }
    queue<int> q;
    map<int, int> visited;
    q.push(start);
    visited[start] = 0;
    while (!q.empty()) //BFS 
    {
        int cur = q.front();
        string s = to_string(cur);
        q.pop();
        if (cur == TARGET)
            break;
        int z = s.find('9'); //9의 위치가 비어있는 칸
        //9의 좌표 저장
        int y = z / 3;
        int x = z % 3;
        for (int i = 0; i < 4; i++)
        {
            int nextY = y + moveDir[i].y;
            int nextX = x + moveDir[i].x;

            if (0 <= nextY && nextY < 3 && 0 <= nextX && nextX < 3)
            {
                string temp = s;
                swap(temp[y * 3 + x], temp[nextY * 3 + nextX]);
                int next = stoi(temp);
                if (!visited.count(next))
                {
                    visited[next] = visited[cur] + 1;
                    q.push(next);
                }
            }
        }
    }
    if (!visited.count(TARGET))
        cout << -1 << "\n";
    else
        cout << visited[TARGET] << "\n";
    return 0;
}