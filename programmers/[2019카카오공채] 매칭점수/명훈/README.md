# 매칭점수

## 문제 알고리즘

- 문제 구현 문제, 미칠듯한 파싱

## 풀이방법

- 문제에서 요구하는 대로 겁나 파싱했다.
- head와 body로 나누고, head에서는 원래의 링크를 얻고, 바디에서는 매칭 점수랑 외부  링크를 얻었다.
- 그 후, 요청하는 값을 구해서 풀었다.
- 나머지는 문제 요구사항에 맞춰서 풀었다.
- 핵심 코드

```c++
#include    <iostream>
#include    <string>
#include    <vector>
#include    <cctype>
#include    <sstream>
#include    <algorithm>
using namespace std;

struct webpage{
    int primary_score;
    string original_link;
    int external_link;
    float matching_score;
    vector<string> external_site;
};

// 특정 문자열 갯수 확인, 기본 점수 구하기
int getPrimaryScore(string str, string word){
    // lower_html는 소문자 html, key는 소문자 word
    size_t start_pos = 0;
    int res = 0;
    string lower_html(str);
    
    transform(lower_html.begin(), lower_html.end(), lower_html.begin(), ::tolower);
    while((start_pos = lower_html.find(word, start_pos)) != string::npos){
        // 앞뒤가 영어가 아닌 완벽한 단어인 경우에만 가능하게 더해준다.
        if(!(lower_html[start_pos + word.length()] >= 'a' && lower_html[start_pos + word.length()] <= 'z'))
            if(!(lower_html[start_pos - 1] >= 'a' && lower_html[start_pos - 1] <= 'z'))
                res++;
        start_pos += 1;
    }
    return res;
}

// 문자열 자르기
vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string temp;
    
    while (getline(ss, temp, delimiter)) {
        internal.push_back(temp);
    }
    return internal;
}

// 해당태그 내의 string 받기
string getDiv(string str, string word){
    string ans = "";
    int div_start = 0, div_end = 0;
    div_start = (int)str.find(word) + (int)word.length();
    div_end = (int)str.find(word, div_start);
    
    if(div_end != div_start)
        ans = str.substr(div_start, div_end - div_start);
    return ans;
}

int solution(string word, vector<string> pages) {
    int answer = 0;                         // answer
    int pages_num = (int)pages.size();      // pages 수
    vector<webpage> WebPages(pages_num);    // Web page 정보들
    
    // init
    for(int i=0; i<pages.size(); i++)
        WebPages[i] = {0, "", 0, 0};
    
    // Web Pages - set head_link, primary_score, external site
    string lower_word(word);
    transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
    for(int i=0; i<pages.size(); i++){
        // head 내용 받기 -> head link 얻어오기
        string head_content = getDiv(pages[i], "head>");
        size_t head_link_start = head_content.find("content=\"");
        string head_link = split(head_content.substr(head_link_start), '"')[1];
        head_link.erase(remove(head_link.begin(), head_link.end(), ' '), head_link.end());
        WebPages[i].original_link = head_link;
        
        // primary score 입력
        string body_content = getDiv(pages[i], "body>");
        WebPages[i].primary_score = getPrimaryScore(body_content, lower_word);
        
        // external site 입력
        int st = 0, et;
        while((st = (int)body_content.find("<a href=", st)) != string::npos){
            st += 9;
            et = (int)body_content.find(">", st);
            string one_external_site = body_content.substr(st, et - st - 1);
            one_external_site.erase(remove(one_external_site.begin(), one_external_site.end(), ' '), one_external_site.end());
            WebPages[i].external_site.push_back(one_external_site);
        }
        // check code
//        cout << WebPages[i].primary_score << " " << WebPages[i].original_link << "\n";
//        for(int j=0; j<WebPages[i].external_site.size(); j++)
//            cout << WebPages[i].external_site[j] << " ";
//        cout << "\n";
    }
    
    // exterenal link 갯수 구하기
    for(int i=0; i<pages.size(); i++){
        for(int j=0; j<WebPages[i].external_site.size(); j++){
            for(int k = 0; k<pages.size(); k++){
                if(i == k)  //  외부링크만 신경쓰자
                    continue;
                else{
                    // 외부에서 들어오는 link수 개산
                    if(WebPages[i].external_site[j].compare(WebPages[k].original_link) == 0){
                        WebPages[k].external_link++;
                        WebPages[k].matching_score += ((float)WebPages[i].primary_score / WebPages[i].external_site.size());
                    }
                }
            }
        }
    }
    
    // link score
    float answer_score = -1;
    for(int i=0; i<pages.size(); i++){
        if(WebPages[i].primary_score + WebPages[i].matching_score > answer_score){
            answer = i;
            answer_score = WebPages[i].primary_score + WebPages[i].matching_score;
        }
    }
    
    
//    for(int i=0; i<pages.size(); i++)
//        cout << WebPages[i].primary_score << " " << WebPages[i].original_link << " " << WebPages[i].external_link << " " << WebPages[i].matching_score << "\n";
    
    
    return answer;
}

int main(int argc, const char * argv[]) {
    string WORD;
    vector<string> PAGES;
    
    WORD = "blind";
    PAGES = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"};
    cout << solution(WORD, PAGES) << "\n";
    
    WORD = "Muzi";
    PAGES = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"};
    cout << solution(WORD, PAGES) << "\n";
    
    return 0;
}

```

## 문제 후 느낀점

- 이해보다도 파싱이 너무 더럽게 많다.
- 현재 **90** 점 코드인데, 차마 수정은 못하겠다.