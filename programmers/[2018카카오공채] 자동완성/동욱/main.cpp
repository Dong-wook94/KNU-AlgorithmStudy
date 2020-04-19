#include <string>
#include <vector>
#include <iostream>

using namespace std;

int answer=0;
class Trie{
private:
    int count;//자식 개수
    bool finish;
    Trie* next[26];
public:
    Trie() : finish(false){
        count =0;
        for(int i=0;i<26;i++){
            next[i]=NULL;
        }
    }
    ~Trie(){
        for(int i=0;i<26;i++){
            if(next[i])
                delete next[i];
        }
    }
    void insert(const char* key){
        if((*key)=='\0'){//문자 끝일때
            if(count==1){
                finish=true;
            }
            return;
        }
        
        int cur = (*key)-'a';
        if(!next[cur]){//다음이 NULL
            next[cur] = new Trie();
        }
        next[cur]->count +=1;
        next[cur]->finish =false;
        next[cur]->insert(key+1); //그다음 글자 insert
    }
    void countNum(){
        if(count>0){
            answer += count;
            if(count==1)
                return;
        }
        if(finish){//finish면 끝
            return;
        }
        for(int i=0;i<26;i++){
            if(next[i])
                next[i]->countNum();
        }
    }
};

int solution(vector<string> words) {
    
    Trie* trie = new Trie();
    for(int i=0;i<words.size();i++){
        trie->insert(words[i].c_str());
    }
    trie->countNum();
    
    return answer;
}

int main(void) {
    cout<<solution({ "go","gone","guild" })<<endl;
}
