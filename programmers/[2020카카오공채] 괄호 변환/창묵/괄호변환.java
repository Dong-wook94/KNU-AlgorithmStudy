
public class Main{

    public static void main(String argv[]){

        String p=")(";
        System.out.println(solution(p));
    }

    public static String solution(String p){

        return divide(p);
    }

    public static String divide(String curString){

        String u,v;
        int scanIndex=0;
        int left=0;
        int right=0;

        for(scanIndex=0;scanIndex<curString.length();scanIndex++) {
            if (curString.charAt(scanIndex) == '(')
                left++;
            else if (curString.charAt(scanIndex) == ')')
                right++;

            if (left == right) {
                u = curString.substring(0, scanIndex + 1);
                v = curString.substring(scanIndex + 1, curString.length());

                if(!v.equals("")){ // v is not null
                    v=divide(v);
                }

                if(!checkString(u)){
                    u=convertString(u,v);
                    return u;
                }
                else
                    return u+v;
            }

        }

        return "";
    }

    public static boolean checkString(String scanString){

        int cnt=0;

        for(int scanIndex=0;scanIndex<scanString.length();scanIndex++){

            if(scanString.charAt(scanIndex)==')'){
                if(cnt==0)
                    return false;
                else
                    cnt--;
            }
            else if(scanString.charAt(scanIndex)=='('){
                cnt++;
            }
        }

        if(cnt==0)
            return true;
        else
            return false;
    }

    public static String convertString(String u,String v){
        String temp="("+v+")";

        for(int i=1;i<u.length()-1;i++){
            if(u.charAt(i)=='(')
                temp+=')';
            else if(u.charAt(i)==')')
                temp+='(';
        }
        return temp;
    }

}