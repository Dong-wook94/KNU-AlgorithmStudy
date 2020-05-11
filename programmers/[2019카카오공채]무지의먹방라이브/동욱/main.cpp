#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
typedef struct Food {
    int num;
    int times;
    Food() {}
    Food(int n, int t) {
        num = n;
        times = t;
    }
}Food;
using namespace std;

bool cmp_t(Food f1, Food f2) {
    return f1.times < f2.times;
}
bool cmp_n(Food f1, Food f2) {
    return f1.num < f2.num;
}
int same_cnt(vector<Food> ft) {
    int times = ft[0].times;
    for (int i = 1; i < ft.size(); i++) {
        if (times != ft[i].times)
            return i;
    }
    return ft.size();
}


int solution(vector<int> food_times, long long k) {
    int answer = 0;
    vector<Food> ft;
    for (int i = 1; i <=food_times.size(); i++) {
        ft.push_back(Food(i, food_times[i-1]));
    }
    sort(ft.begin(), ft.end(), cmp_t);
    int accumulate = 0;
    for (int i = 0,n=ft.size();i<ft.size();i++,n--) {
        long long spend = (long long)(ft[i].times - accumulate)*n;
        
        if (spend == 0) {
            //ft.erase(ft.begin());
            continue;
        }
        if (spend <= k) {
            k -= spend;
            accumulate = ft[i].times;
            //ft.erase(ft.begin());
        }
        else {
            k %= n;
            sort(ft.begin()+i, ft.end(), cmp_n);
            return ft[i+k].num;
        }
        
    }
    return -1;
}

int main() {
    vector<int> input = { 3,5,1,6,5,3 };
    printf("%d\n", solution(input, 20));
}
