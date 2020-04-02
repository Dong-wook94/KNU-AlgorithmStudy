#include <string>
#include <iostream>
#include <ctype.h> //isupper사용할라고
#include <vector>
using namespace std;

bool isUsed[26];
string Sentence;
string answer = "";
int rule1(int start_index, char curAlphabet,char curRule2Alphabet) {//첫째 글자가 대문자 이후 소문자 대문자 반복
	answer += Sentence[start_index];
	curAlphabet = Sentence[start_index + 1];
	if (isupper(curAlphabet)) {//규칙1에서 2번째글자가 대문자인경우
		for (int i = 1; i < Sentence.size() - start_index; i++) {
			if (isupper(Sentence[start_index + i])) {//제대로 나온경우
				answer += Sentence[start_index + i];
			}
			else {
				return start_index + i - 1;
			}
		}
	}
	if (isUsed[curAlphabet - 'a']) {//썼던문자일때
		answer = "invalid";
		return 0;
	}
	isUsed[curAlphabet - 'a'] = true; //사용 처리
	int small_cnt = 0;
	for (int i = 1; i < Sentence.size() - start_index; i++) {
		if (i % 2 == 0) { //대문자나와야됨
			if (isupper(Sentence[start_index + i])) {//제대로 나온경우
				answer += Sentence[start_index + i];
			}
			else {//소문자 나올때
				if (isUsed[Sentence[start_index + i]-'a']) {//썼던게 나올때
					answer = "invalid";
					return 0;
				}
				return start_index + i - 1; //마지막 index 반환
			}
		}
		else {// 소문자 나와야됨 제대로 나오면 그냥 통과 
			if (isupper(Sentence[start_index + i])) {//대문자 또나온경우
				if (small_cnt == 1) {
					if (isupper(Sentence[start_index + i+1])) {
						isUsed[curAlphabet - 'a'] = false;
						answer.pop_back();
						return start_index;
					}
				}
				return start_index + i - 1;
			
			}
			else {
				if (Sentence[start_index + i] != curAlphabet) {//다른 기호가 갑자기 나온경우
					if (isUsed[Sentence[start_index + i]-'a']) {//썼던기호
						answer = "invalid";
						return 0;
					}
					else {
						if(small_cnt==1&&curRule2Alphabet==NULL){
							isUsed[curAlphabet - 'a'] = false;
							answer.pop_back();
							return start_index;
						}
						return start_index + i - 1;
					}
				}
				else {
					small_cnt++;
				}
			}
			
			
		}
	}
	return Sentence.size();
}
int rule2(int i, char curAlphabet) {//첫째 글자가 소문자면 쭉 대문자 나오다가 소문자
	i++;//다음 문자부터 확인해도되서
	int small_cnt = 1;
	for (; i < Sentence.size(); i++) {
		if (!isupper(Sentence[i])) {//소문자
			if (Sentence[i] != curAlphabet) { //다른소문자 나올때
				if (small_cnt != 1||answer.size()<=0) {
					answer = "invalid";
					return 0;
				}
				else {//규칙 2개 한번에 적용일수도 있다.
					if (!isUsed[Sentence[i]-'a']) {
						answer.pop_back();
						isUsed[curAlphabet - 'a'] = false;
						i = rule1(i-1, NULL,curAlphabet);
						if (Sentence[i + 1] == curAlphabet) {
							isUsed[curAlphabet - 'a'] = true;
							return i + 1;
						}
						else {
							answer = "invalid";
							return 0;
						}
					}
				}
					
			}
			else {
				return i-1;
			}
			
		}
		else {//대문자
			answer += Sentence[i];
		}
	}
}

string solution(string sentence) {
	for (int i = 0; i < 26; i++)
		isUsed[i] = false;
	Sentence = sentence;
	answer = "";
	if (sentence.find(" ") != string::npos) {
		answer = "invalid";
		return answer;
	}
	for (int i = 0; i < sentence.size(); i++) {
		if (isupper(sentence[i])) {//1이면 대문자 0이면소문자
			i = rule1(i,NULL,NULL);
			if (i==0) {
				return answer;
			}
		}
		else {//소문자
			int idx = sentence[i] - 'a';
			if (!isUsed[idx]) {
				isUsed[idx] = true;
				i=rule2(i,sentence[i]);
				if (i==0) {
					return answer;
				}
			}
		}
		if(answer.size()>0 && answer[answer.size()-1]!=' ')
			answer += " ";
	}
	if (answer.size() <= 0) {
		return "invalid";
	}
	while (answer[answer.size() - 1] == ' ') {
		answer.pop_back();
		if (answer.size() <= 0) {
			return "invalid";
		}
	}
		
	
	return answer;
}

int main() {
	vector<string> v;
	v.push_back("HaEaLaLaObWORLDb");
	v.push_back("SpIpGpOpNpGJqOqA");
	v.push_back("AxAxAxAoBoBoB");
	v.push_back("abHELLObaWORLD");
	v.push_back("HaEaLaLaOWaOaRaLaD");
	v.push_back("aHELLOWORLDa");
	v.push_back("HaEaLaLObWORLDb"); //
	v.push_back("aHbEbLbLbOacWdOdRdLdDc");
	v.push_back("aBcAadDeEdvAvlElmEEEEm");
	v.push_back("AcAcABaBaB");//답이 2개가 될수있다.
	v.push_back("AxAxAxABcBcBcB");
	v.push_back("AaABbBCcC");
	v.push_back("HELLOWORLD");
	v.push_back("AAAaBaAbBBBBbCcBdBdBdBcCeBfBeGgGGjGjGRvRvRvRvRvR");
	v.push_back("a");
	v.push_back("A");
	v.push_back("aA");
	v.push_back("Aa");
	v.push_back("bTxTxTaTxTbkABaCDk");
	v.push_back("TxTxTxbAb");
	v.push_back("HaEaLaLaObWORLDbSpIpGpOpNpGJqOqAdGcWcFcDdeGfWfLeoBBoAAAAxAxAxAA");
	v.push_back("AxAxAxA");
	v.push_back("AA");
	v.push_back("oBBoA");
	v.push_back("aGbWbFbDakGnWnLk");
	v.push_back("A B");
	for (int i = 0; i < v.size(); i++) {
		cout <<i<<" : '"+v[i]<< endl;
		cout << "' -> " << "'" + solution(v[i]) + "'" << endl;
	}

}