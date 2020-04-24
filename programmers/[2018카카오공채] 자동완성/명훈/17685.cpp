#include    <iostream>
#include    <string>
#include    <vector>
#include    <cstring>
#include    <algorithm>
using namespace std;

int answer = 0;

class Trie
{
private:
	bool finish;		// is finished?
	int child;			// child
	Trie* next[26];     // alphabet 26
public:
	Trie() : finish(false) {
		child = 0;
		memset(next, NULL, sizeof(next));
	}
	~Trie() {
		for (int i = 0; i < 26; i++)
			if (next[i])
				delete next[i];
	}
	void insert(const char* key) {
		if (*key == '\0') {
			if (child == 1)
				finish = true;
		}
		else {
			int curr = *key - 'a';
			if (next[curr] == NULL)
				next[curr] = new Trie();
			next[curr]->child += 1;
			next[curr]->finish = false;
			next[curr]->insert(key + 1);
		}
	}
	void countAnswer() {
		// if any child, need more text
		if (child > 0) {
			answer += child;
			if (child == 1) return;
		}
		if (finish) return; // if last node, return;
		for (int i = 0; i < 26; i++)
			if (next[i])
				next[i]->countAnswer();
	}
};

int solution(vector<string> words) {
	// init
	Trie* root = new Trie;
	answer = 0;

	// solution
	for (int i = 0; i < words.size(); i++) {
		root->insert(words[i].c_str());
	}
	root->countAnswer();

	// output
	return answer;
}

int main() {
	cout << solution({ "go", "gone", "guild" }) << "\n";
	cout << solution({ "abc", "def", "ghi", "jklm" }) << "\n";
	cout << solution({ "word", "war", "warrior", "world" }) << "\n";

	return 0;
}