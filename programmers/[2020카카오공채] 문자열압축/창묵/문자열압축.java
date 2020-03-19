public class Main{

    static String s="xababcdcdababcdcd";

    public static void main(String args[]){

        System.out.println(solution(s));
    }

    public static int solution(String s){

        int answer=0;
        answer=calculate(s);

        return answer;

    }

    public static int calculate(String s){

        int index=0;
        int start=0;
        int stack=0;
        int min=1001;

        String temp,scanString,result;

        for(int wordLength=1;wordLength<=s.length();wordLength++){

            result="";
            index=0;
            stack=0;
            start=0;

            while(index<s.length()){

                temp=substring(s,start,wordLength);
                scanString=substring(s,index,wordLength);

                if(temp.equals(scanString)){
                    stack++;
                    index+=wordLength;

                    if(index>=s.length()){
                        result=makeString(result,stack,temp);
                    }
                }
                else{
                    result=makeString(result,stack,temp);
                    start+=wordLength*stack;
                    stack=0;
                }

            }
            min=Math.min(min,result.length());
        }

        return min;
    }

    public static String makeString(String result,int stack,String temp){
        if(stack==1) {
            result+=temp;
        }
        else
            result=result+stack+temp;

        return result;
    }

    public static String substring(String s,int start,int wordCount){

        if(start+wordCount>=s.length())
        return s.substring(start,s.length());
        else
        return s.substring(start,start+wordCount);
    }
}