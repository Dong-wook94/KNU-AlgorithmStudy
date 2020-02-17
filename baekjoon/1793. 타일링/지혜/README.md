# 1793 타일링

🤔 놀랍게 계산이 int 범위 넘어감

꿀 빠는 줄 알았는데 아니었음



1. 숫자 string으로 바꿔서 계산해주는거 내가 짜야했음 (혼절)

~~~C++
string bigNumAdd(string a , string b){
    vector<int> newA,newB,result;
    
    for(int i=0; i<a.length(); i++){
        newA.push_back(a.at(i) - '0');
    }
    
    for(int i=0; i<b.length(); i++){
        newB.push_back(b.at(i) - '0');
    }
    
    int nnA,nnB;
    int carry=0;
    while(!newA.empty() && !newB.empty()){
        nnA = newA.back();
        newA.pop_back();
        nnB = newB.back();
        newB.pop_back();
        result.push_back((nnA+nnB+carry)%10);
        carry = (nnA+nnB+carry)/10;
    }
    
    if(newA.empty()){
        while(!newB.empty()){
            nnB = newB.back();
            newB.pop_back();
            
            result.push_back((nnB + carry)%10);
            carry = (nnB + carry) / 10;
        }
    }else{
        while(!newA.empty()){
            nnA = newA.back();
            newA.pop_back();
            
            result.push_back((nnA + carry)%10);
            carry = (nnA + carry) / 10;
        }
    }
    
    if(carry) result.push_back(1);
    
    string real_result;
    for(int i=(int)result.size()-1; i>=0; i--){
        real_result += to_string(result[i]);
    }
    
    return real_result;
}
~~~



2. 그러고나서는 계산하기...

~~~C++
 tile2[0]= 1+'0';
    tile2[1] = 1+'0';
    tile2[2] = 3+'0';
    
    for(int i=3; i<=250; i++){
        tile2[i] = bigNumAdd(tile2[i-1],mult2(tile2[i-2]));
    }
~~~

