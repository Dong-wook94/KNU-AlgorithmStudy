#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 999

using namespace std;

struct edge {
	int to;
	int weight;
};
bool Comp(edge x, edge y);
void relax(int from, int to);
void bellmanFord();
int Lday;
vector <edge> t;
int d[17] = { 0, };

int main() {
	edge temp;

	cin >> Lday;
	temp.to = 0;
	temp.weight = 0;
	t.push_back(temp);
	for (int i = 0; i < Lday; i++) {
		cin >> temp.to;
		cin >> temp.weight;
		t.push_back(temp);
	}
	temp.to = 0;
	temp.weight = 0;
	t.push_back(temp);
	bellmanFord();
	cout << d[Lday+1];
}
bool Comp(edge x, edge y) {
	return x.to < y.to;
}
void relax(int from, int to) {
	if (d[to] < d[from] + t[from].weight) {
		d[to] = d[from] + t[from].weight;
	}
}
void bellmanFord() {

	for (int i = 0; i <= Lday+1; i++) {
		for (int j = i + 1; j <= Lday+1; j++) {
			if ((i + t[i].to) <= j) {
				relax(i, j);
			}
		}
	}
}