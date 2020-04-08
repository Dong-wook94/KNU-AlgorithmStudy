#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <map>
#include <sstream>
using namespace std;
typedef struct WebPage {
	double score;
	vector<string> external_link;
	double link_score;
	double matching_score;
	WebPage() {}
	WebPage(int s, double l) {
		score = s;
		link_score = l;
	}
}WebPage;

vector<WebPage> web;
map<string, int> urlToWebIndexMap;



string replaceAllUpperToLowerCase(string str) {
	//cout << str << endl;
	for (int i = 0; i < str.size(); i++) {
		if (isupper(str[i])) {
			str[i] = tolower(str[i]);
		}
	}
	//cout << str << endl;
	return str;
}

vector<string> string_tokenize(string str, string delimiter) {
	vector<string> token;
	vector<int> del_pos;
	//token.push_back(str.substr(0, str.find(" ")));
	del_pos.push_back(0);
	for (int i = 0; i < str.size(); i++) {
		if (str.find(delimiter, i) != std::string::npos) {
			int index = str.find(delimiter, i);
			del_pos.push_back(index + 1);
			i = index + 1;
		}
		else {
			del_pos.push_back(str.size() + 1);
			break;
		}

	}
	for (int i = 0; i < del_pos.size() - 1; i++) {
		token.push_back(str.substr(del_pos[i], del_pos[i + 1] - del_pos[i] - 1));
	}
	return token;
}
vector<string> parseTagsContent(string html,string startTag,string endTag) {
	vector<string> result;
	vector<string> token;
	token = string_tokenize(html, startTag);
	for (int i = 1; i < token.size(); i++) {
		int end_pos = token[i].find(endTag);
		string temp = token[i].substr(0, end_pos);
		result.push_back(temp);
	}
	return result;
}

string parseTagContent(string html, string startTag, string endTag) {
	int startTagIdx = html.find(startTag) + startTag.length() + 1;
	int endTagIdx = html.find(endTag);
	return html.substr(startTagIdx, endTagIdx - startTagIdx);
}

string getWebUrl(string html) {
	string url;

	vector<string> metatags = parseTagsContent(html,"<meta",">");

	for (int i = 0; i < metatags.size(); i++) {
		int start_pos;
		if ((start_pos = metatags[i].find("https://"))!=string::npos) {
			int url_length = metatags[i].substr(start_pos).find("\"");
			url = metatags[i].substr(start_pos, url_length);
			return url;
		}
	}
	return "";
}

int getScore(string bodyContent,string word) {
	double score=0;
	int offset=0;
	int word_pos;
	word_pos = bodyContent.find(word, offset);
	while (word_pos != string::npos) {
		int before_pos = word_pos-1;
		int after_pos = word_pos + word.length();
		offset = after_pos;
		word_pos = bodyContent.find(word, offset);
		if (before_pos>=0&&islower(bodyContent[before_pos]))
			continue;
		if (after_pos < bodyContent.size()&& islower(bodyContent[after_pos]))
			continue;
		
		score++;
	}
	return score;
}

vector<string> getExternalLinks(string bodyContent) {
	vector<string> externalLinks = parseTagsContent(bodyContent,"<a href",">");
	for (int i = 0; i < externalLinks.size(); i++) {
		int start_pos = externalLinks[i].find("https://");
		externalLinks[i] = externalLinks[i].substr(start_pos);
		externalLinks[i] = externalLinks[i].substr(0, externalLinks[i].find("\""));
	}
	return externalLinks;
}
void updateLinkScore() {
	for (int i = 0; i < web.size(); i++) {
		for (int j = 0; j < web[i].external_link.size(); j++) {
			string url = web[i].external_link[j];
			
			if (urlToWebIndexMap.find(url) != urlToWebIndexMap.end()) {
				int idx = urlToWebIndexMap[url];
				web[idx].link_score += web[i].score /web[i].external_link.size();
			}
			
		}
	}
}

int getMaxMatchingScoreIndex() {
	double max_score=0;
	int max_index = 0;
	for (int i = 0; i < web.size(); i++) {
		web[i].matching_score = web[i].score + web[i].link_score;
		if (web[i].matching_score > max_score) {
			max_score = web[i].matching_score;
			max_index = i;
		}
	}
	return max_index;
}

int solution(string word, vector<string> pages) {
	int answer = 0;

	int n_pages = pages.size();
	for (int i = 0; i < n_pages; i++) {
		pages[i] = replaceAllUpperToLowerCase(pages[i]);
	}
	word = replaceAllUpperToLowerCase(word);
	web.assign(n_pages, WebPage(0, 0));
	for (int i = 0; i < n_pages; i++) {
		string html = pages[i];
		string headContent = parseTagContent(html, "<head>", "</head>");
		string url = getWebUrl(html);
		urlToWebIndexMap[url] = i; //map¿¡ url°ú webindex¸ÊÇÎ
		string bodyContent = parseTagContent(html, "<body>", "</body>");
		web[i].score = getScore(bodyContent,word);
		web[i].external_link = getExternalLinks(bodyContent);

	}
	updateLinkScore();
	answer = getMaxMatchingScoreIndex();


	return answer;
}

int main() {
	//string word = "blind";
	//vector<string> pages = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"};
	string word = "Muzi";
	vector<string> pages = { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" };
	cout << solution(word, pages) << endl;


}