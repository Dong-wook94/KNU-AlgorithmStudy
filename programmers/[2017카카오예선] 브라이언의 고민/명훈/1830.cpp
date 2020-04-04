#include	<iostream>
#include	<string>
#include	<string.h>
#include	<set>
using namespace std;

bool visited[26];
set<string> ans;

void dfs(string sentence, int cnt) {
	// end state, 
	if (cnt == 0) {
		//cout << sentence << "\n";
		ans.insert(sentence);
		return;
	}
	
	for (int i = 0; i < 26; i++) {
		// 소문자 알파벳(광고문자)가 있는 경우
		if (visited[i]) {
			string res = "";
			char ad_key = 'a' + i;
			int ad_key_start = sentence.find(ad_key);
			
			int t_count = 0;
			for (int j = ad_key_start; j < sentence.length(); j++) {
				// 광고키 갯수 확인
				if (sentence[j] == ad_key)
					t_count++;
			}

			// 같은 광고키가 2개가 아니면 무조건 광고패턴 1
			int ad_pattern = 0;
			if (t_count != 2)
				ad_pattern = 1;
			else
				ad_pattern = 2;		// 2개인 경우 무조건 광고패턴 2로 보자.
			// 붙어 있는 경우는 없다.

			if (ad_pattern == 1) {
				// 광고 패턴 1번의 경우
				if (ad_key_start != 1) {
					// 시작이 1의 위치가 아닌 경우에는 앞에 빈칸을 넣어야한다 필요는 없다.
					res += sentence.substr(0, ad_key_start - 2);	//
					if(sentence[ad_key_start - 2] != ' ')
						res += " ";
				}
				// 첫번째 더 해주고
				res += sentence[ad_key_start - 1];
				// 그 뒤로 나오는 애들 광고단어 빼고 더 해주기.
				int j;
				for (j = ad_key_start; j < sentence.length(); j+= 2) {
					if (sentence[j] == ad_key)
						res += sentence[j + 1];
					else
						break;
				}
				// 현재 j의 위치부터 끝까지 더해주기.
				if (j != sentence.length()) {
					if(sentence[j] != ' ')
						res += " ";
					res += sentence.substr(j);
				}
			}
			else {
				// 광고 패턴 2번의 경우
				if (ad_key_start != 0) {
					// 시작 위치가 0이 아닌 경우, 앞의 얘들을 다 더해준다.
					res += sentence.substr(0, ad_key_start);
					if(sentence[ad_key_start - 1] != ' ')
						res += " ";
				}
				int j;
				for (j = ad_key_start + 1; j < sentence.length(); j++) {
					if (sentence[j] != ad_key)	// 광고키가 아니면 끝
						res += sentence[j];
					else						// 광고키가 나오면 스탑
						break;
				}
				// j가 끝이 아닌 경우
				if (j != sentence.length() - 1) {
					if(sentence[j+1] != ' ')
						res += " ";
					res += sentence.substr(j + 1);
				}
			}
			
			// check
			//cout << ad_pattern << " " << res << "\n";

			visited[i] = false;
			dfs(res, cnt - 1);
			visited[i] = true;
		}
	}
}

string solution(string sentence) {
    // initialize
	int ad_count = 0;
	ans.clear();
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < sentence.length(); i++){
		if (sentence[i] >= 'a' && sentence[i] <= 'z')
			visited[(sentence[i] - 'a')] = true;
		if (sentence[i] == ' ')	// 잘못된 input
			return "invalid";
	}
		
	for (int i = 0; i < 26; i++)
		if (visited[i])
			ad_count++;

	// solution
	dfs(sentence, ad_count);

	// output
	if (ans.size() != 1)
		return "invalid";
	else {
		string ans_str = *(ans.begin());
		if (ans_str.find("  ") != string::npos)
			return "invalid";
		return ans_str;
	}
}

int main() {
	cout << solution("HaEaLaLaObWORLDb") << "\n";
	cout << solution("SpIpGpOpNpGJqOqA") << "\n";
	cout << solution("AxAxAxAoBoBoB") << "\n";
}