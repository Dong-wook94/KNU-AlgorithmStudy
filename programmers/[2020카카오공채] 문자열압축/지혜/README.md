# [2020카카오공채] 문자열 압축
저 더럽게짠거같아요...

string 길이 1인거 넣으면 안걸러져서...예외로..처리한거부터 살짝 눈물남ㅠ

substr 처음알았읍니다...string 너는 다 생각이 있구나?

~~~C++
int solution(string s) {
    int answer = 99999;
    int zipLength = 1;
    int stringLength = (int)s.length();

    if(stringLength == 1){
        answer = 1;
        return answer;
    }
    while(1){
        if(zipLength >= stringLength ) break;
        string zipS;
        string check = s.substr(0 ,zipLength);
        int start = zipLength;
        int count = 1;
        while(1){
            if(start >= stringLength ){
                if(count == 1) zipS+=check;
                else{
                    zipS+=to_string(count);
                    zipS+=check;
                }
                break;
            }
            string cmp = s.substr(start, zipLength);
            if(check.compare(cmp) == 0 ){
                count+=1;
            }else{
                if(count == 1){
                    zipS+=check;
                }else{
                    zipS+=to_string(count);
                    zipS+=check;
                }
                check.clear();
                check = cmp;
                count = 1;
            }
            start += zipLength;
        }
        if(answer > zipS.length()) answer = (int)zipS.length();
        zipLength += 1;
    }
    
    return answer;
}
~~~

