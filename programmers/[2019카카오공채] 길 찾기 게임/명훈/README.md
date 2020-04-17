# [2019 카카오 공채] 길찾기 게임

## 문제 알고리즘

- 트리

## 풀이방법

- 이진 트리를 만들어서 preorder와 postorder 출력하기



- 핵심 코드

~~~c++
#include	<iostream>
#include	<string>
#include	<vector>
#include	<algorithm>
using namespace std;

vector<int> pre_vector;
vector<int> post_vector;

class TreeNode {
	friend class Tree;
private:
	TreeNode* leftChild;
	TreeNode* rightChild;
	int x;
	int num;
public:
	TreeNode(int tx, int tnum) { x = tx; num = tnum; leftChild = NULL; rightChild = NULL; }
};

class Tree {
private:
	TreeNode* root;
public:
	Tree() : root(NULL) {};
	~Tree() {};
	TreeNode* getRoot() { return root; }
	void insertNode(int x, int num) {
		TreeNode* temp = new TreeNode(x, num);
		if (root == NULL) {
			root = temp;
			return;
		}
		for (TreeNode* cur = root;;) {
			if (temp->x < cur->x) {
				if (cur->leftChild != NULL)
					cur = cur->leftChild;
				else {
					cur->leftChild = temp;
					return;
				}
			}
			else {
				if (cur->rightChild != NULL)
					cur = cur->rightChild;
				else {
					cur->rightChild = temp;
					return;
				}
			}
		}
	}
	void preorder(TreeNode* cur) {
		if (cur) {
			pre_vector.push_back(cur->num);
			preorder(cur->leftChild);
			preorder(cur->rightChild);
		}
	}
	void postorder(TreeNode* cur) {
		if (cur) {
			postorder(cur->leftChild);
			postorder(cur->rightChild);
			post_vector.push_back(cur->num);
		}
	}
};

bool cmp(vector<int> a, vector<int> b) {
	return a[1] > b[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;

	for (int i = 0; i < nodeinfo.size(); i++)
		nodeinfo[i].push_back(i + 1);
	sort(nodeinfo.begin(), nodeinfo.end(), cmp);

	Tree* b_tree = new Tree();
	for (int i = 0; i < nodeinfo.size(); i++)
		b_tree->insertNode(nodeinfo[i][0], nodeinfo[i][2]);

	b_tree->preorder(b_tree->getRoot());
	b_tree->postorder(b_tree->getRoot());
	answer.push_back(pre_vector);
	answer.push_back(post_vector);

	return answer;
}

int main() {
	vector<vector<int>> res = solution({ {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} });

	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++)
			cout << res[i][j] << " ";
		cout << "\n";
	}

	return 0;
}
~~~

## 문제 후 느낀점

- 트리가 약해서 트리 열심히 공부하기