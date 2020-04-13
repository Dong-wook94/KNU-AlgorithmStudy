#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Tree;

class TreeNode {
	friend class Tree;
private:
	TreeNode* leftChild;
	TreeNode* rightChild;
	int data;
	int num;
public:
	TreeNode(int d,int n) {
		data = d;
		num = n;
		leftChild = NULL;
		rightChild = NULL;
	}
};
vector<int> prevector;
vector<int> postvector;

class Tree {
private:
	TreeNode* root;
public:
	Tree() : root(NULL) {};
	~Tree() {};
	void insertNode(int data,int num) {
		TreeNode* node = new TreeNode(data,num);
		//NULL이 아니면 중복된 값이 입력되는거임
		if (root == NULL) {
			root = node;
			return;
		}
		if (search(root, node->data) == NULL) {
			TreeNode* parent = NULL;
			for (TreeNode* cur = root;;) {
				if (node->data < cur->data) {
					if (cur->leftChild!=NULL) {
						cur = cur->leftChild;
					}
					else {
						cur->leftChild = node;
						break;
					}
				}
				else {
					if (cur->rightChild !=NULL) {
						cur = cur->rightChild;
					}
					else {
						cur->rightChild = node;
						break;
					}
				}
			}
		}

	}

	TreeNode* search(TreeNode* current, int data) {
		if (current == NULL) 
			return NULL; //없을때
		if (data == current->data) {
			return current;
		}
		else if (data < current->data) {
			search(current->leftChild, data);
		}
		else {
			search(current->rightChild, data);
		}
	}

	void preorder(TreeNode* ptr){
		if (ptr) {
			//printf("%d ", ptr->data);
			prevector.push_back(ptr->num);
			preorder(ptr->leftChild);
			preorder(ptr->rightChild);
		}
	}
	void postorder(TreeNode* ptr) {
		if (ptr) {
			postorder(ptr->leftChild);
			postorder(ptr->rightChild);
			postvector.push_back(ptr->num);
		}
	}
	TreeNode* getRoot() {
		return root;
	}
	
};

bool cmp(vector<int> a, vector<int> b) { //내림차순 y축기준
	return a[1] > b[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodeinfo[i].push_back(i + 1);//node value 추가
	}
	sort(nodeinfo.begin(), nodeinfo.end(), cmp);
	Tree* bst = new Tree();

	for (int i = 0; i < nodeinfo.size(); i++) {
		bst->insertNode(nodeinfo[i][0],nodeinfo[i][2]);
	}

	bst->preorder(bst->getRoot());
	answer.push_back(prevector);
	bst->postorder(bst->getRoot());
	answer.push_back(postvector);
	return answer;
}

int main() {
	vector<vector<int>> input = { {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} };

	solution(input);
}