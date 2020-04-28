#include <stdio.h>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;

int N;//수의 개수
int A[100];
int num_plus, num_minus, num_mul, num_div;
void combination();
vector<int> oper;
int max_sum=INT_MIN, min_sum=INT_MAX;
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d %d %d %d", &num_plus, &num_minus, &num_mul, &num_div);
    combination();
    printf("%d\n%d\n", max_sum, min_sum);

}

void combination() {
    int sum = 0;
    for (int i = 0; i < num_plus; i++)
        oper.push_back(1);
    for (int i = 0; i < num_minus; i++)
        oper.push_back(2);
    for (int i = 0; i < num_mul; i++)
        oper.push_back(3);
    for (int i = 0; i < num_div; i++)
        oper.push_back(4);

    sort(oper.begin(), oper.end());

    do {
        sum = A[0];
        for (int i = 0; i < oper.size(); i++) {
            switch (oper[i]) {
            case 1://+
                sum = sum + A[i + 1];
                break;
            case 2:
                sum = sum - A[i + 1];
                break;
            case 3:
                sum = sum * A[i + 1];
                break;
            case 4:
                sum = sum / A[i + 1];
                break;
            }
        }
        if (max_sum < sum)
            max_sum = sum;
        if (min_sum > sum)
            min_sum = sum;
    } while (next_permutation(oper.begin(), oper.end()));
}
