# 문자열압축

# 풀이방법

특정 알고리즘을 사용하지 않았다.
그냥 맨앞에서부터 자르면서 반복되는 단어가 있으면 계속 탐색하고, 반복되지않는다면 이때까지 반복된 단어를 붙인다.

단어길이 1부터 string길이까지 반복해서 탐색을한다.

 for(int wordLength=1;wordLength<=s.length();wordLength++){ // 단어길이를 1부터 탐색한다.

            result="";
            index=0;
            stack=0;
            start=0;

            while(index<s.length()){

                temp=substring(s,start,wordLength); // abcdefg 중에서 wordlength가 2라면, "ab" 가됨
                scanString=substring(s,index,wordLength); // 처음에는 "ab"가 되지만, 그 다음 while문에서는 "cd"가 된다.

                if(temp.equals(scanString)){
                    stack++;
                    index+=wordLength;

                    if(index>=s.length()){
                        result=makeString(result,stack,temp); // 문자열의 마지막보다 넘어가는것을 방지하기 위함
                    }
                }
                else{
                    result=makeString(result,stack,temp); // 다르다면 이때까지 반복된 문자열을 붙임
                    start+=wordLength*stack; // temp를 다시설정하기위해 start위치를 이동한다.
                    stack=0;
                }

            }
            min=Math.min(min,result.length());
        }



# 느낀점

단어의길이가 엄청 길다면 탐색시간이 오래걸릴 것 같은 코드이다.
좀 더 효율적인 코드를 짤수있게 문자열 관련해서 공부를 해야할 것 같다.