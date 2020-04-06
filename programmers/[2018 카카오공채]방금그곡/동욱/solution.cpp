#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> string_tokenize(string str, char delimeter) {
	vector<string> result;
	string token;
	stringstream ss(str);

	while (getline(ss, token, delimeter)) {
		result.push_back(token);
	}
	return result;
}


string replaceSharp(string str) {
	size_t pos=0;
	size_t offset=0;

	while ((pos = str.find("#", offset)) != string::npos) {
		pos--;
		char note = str[pos] - ('A'-'a');
		string replace = "";
		replace += note;
		str.replace(pos, 2,replace);
		offset = pos + 1;
	}

	return str;
}

int timeToSecond(string times) {
	vector<string> time_info = string_tokenize(times, ':');
	return stoi(time_info[0]) * 60 + stoi(time_info[1]);
}


string solution(string m, vector<string> musicinfos) {
	string answer = "";
	
	string melody = replaceSharp(m);

	for (int i = 0; i < musicinfos.size(); i++) {
		vector<string> infos = string_tokenize(musicinfos[i],',');
		int start_time = timeToSecond(infos[0]);
		int end_time = timeToSecond(infos[1]);
		int play_time = end_time - start_time;
		string music = replaceSharp(infos[3]);
		string music_title = infos[2];
		int music_runtime = music.length();
		int n_playmusic = play_time / music_runtime;
		int add_play_time = play_time % music_runtime;

		string played_music = "";
		for (int i = 0; i < n_playmusic; i++)
			played_music += music;
		played_music += music.substr(0, add_play_time);

		cout << played_music << endl;


	}



	return answer;
}

int main() {
	string ans = "";
	//ans = solution("ABCDEFG", { "12:00,12:14,HELLO,CDEFGAB", "13:00,13:05,WORLD,ABCDEF" });
	//cout << ans << endl;

	ans = solution("CC#BCC#BCC#BCC#B", { "03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B" });
	cout << ans << endl;

	ans = solution("ABC", { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" });
	cout << ans << endl;
}