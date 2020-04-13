#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class Node {
	int data;
	int num;
	Node* leftChild, rightChild;
};
Node* root;
bool cmp(vector<int> a, vector<int> b) {
	return a[1] > b[1];
}
vector<int> prevector;
vector<int> postvector;
void preorder(Node* ptr) {
	if (ptr) {
		//printf("%d ", ptr->data);
		prevector.push_back(ptr->num);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
void postorder(Node* ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		postvector.push_back(ptr->num);
	}
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	Node* temp;
	root = (node*)malloc(sizeof(node));
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodeinfo[i].push_back(i+1);
		//cout << nodeinfo[i][2] << endl;
	}
	sort(nodeinfo.begin(), nodeinfo.end(), cmp);
	root->data = nodeinfo[0][0];
	root->num = nodeinfo[0][2];
	root->rightChild = NULL;
	root->leftChild = NULL;
	for (int i = 1; i < nodeinfo.size(); i++) {
		cout << nodeinfo[i][2] << endl;
		temp = (node*)malloc(sizeof(node));
		temp->data = nodeinfo[i][0];
		temp->num = nodeinfo[i][2];
		temp->rightChild = NULL;
		temp->leftChild = NULL;
		for (Node* cur = root; ;) {
			if (temp->data < cur->data) {
				if (cur->leftChild) {
					cur = cur->leftChild;
				}
				else {
					cur->leftChild = temp;
					break;
				}

			}
			else {
				if (cur->rightChild) {
					cur = cur->rightChild;
				}
				else {
					cur->rightChild = temp;
					break;
				}

			}
		}
	}
	preorder(root);
	postorder(root);
	answer.push_back(prevector);
	answer.push_back(postvector);


	return answer;
}
int main() {
	vector<vector<int>> input = { {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} };

	solution(input);
}