import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;



public class Main{

    static List<Integer> list = new ArrayList<>();


    static String operation;
    static int maxValue=Integer.MIN_VALUE;

    public static void main(String args[]) throws IOException {

        init();
        dfs(0);
        System.out.println(maxValue);

    }

    public static void init() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n= Integer.parseInt(br.readLine());
        operation=br.readLine();
    }


    public static void dfs(int cnt) {

        int value;

        if (cnt == operation.length() / 2) {
            value = calculate();
            maxValue = Math.max(value, maxValue);
            return;
        }


        for (int index = 0; index <= 1; index++) {
            list.add(index);
            dfs(cnt + 1);
            list.remove(list.size() - 1);
        }

    }

    public static boolean checkNum(int object){
        if(object=='*' || object=='+' || object=='-'){
            return false;
        }
        else
            return true;
    }

    public static int calculate() {

        ArrayList<Integer> cur = new ArrayList<>();
        ArrayList<Integer> operArr;

        int num;

        for (int i = 0; i < list.size(); i++)
            cur.add(list.get(i));


        operArr=bracketOperate(cur); // 괄호계산을 정리하여 OperArr에 넣는다.
        operArr=product(operArr); // 곱셈 우선순위로 정리하여서 OperArr에 넣는다.
        num=lastOperate(operArr); // 마지막 정리한 식을 전부 더한다.

        return num;
    }

    public static ArrayList<Integer> bracketOperate(ArrayList<Integer> cur){

        ArrayList<Integer> operArr=new ArrayList<>();
        int position=0;
        int operateNum;

        cur.add(0); // 맨 끝의 피연산자는 어차피 괄호계산을 못하기 때문에 0을 집어넣는다.

        for(int index=0;index<cur.size();){
            if(checkNum(operation.charAt(position)) && cur.get(index)==1){ // 괄호가 있을때 피연산자1 연산 피연산자2를 계산하여 insert.
                operateNum=operate(operation.charAt(position)-48,operation.charAt(position+1),operation.charAt(position+2)-48);
                operArr.add(operateNum);
                position+=3;
                index+=2;
            }
            else if(checkNum(operation.charAt(position)) && cur.get(index)==0){ // 괄호없는 계산일 때는 그냥 숫자 추가
                operArr.add(operation.charAt(position)-48);
                position++;
                index++;
            }
            else if(!checkNum(operation.charAt(position))){ // 연산자면 그냥 추가해준다.
                operArr.add((int)operation.charAt(position));
                position++;
            }
        }

        return operArr;
    }

    public static int lastOperate(ArrayList<Integer> operArr){

        int startNum=operArr.get(0);
        for(int index=1;index<operArr.size();index=index+2){
            startNum=operate(startNum,operArr.get(index),operArr.get(index+1)); // 연산을 따라서 계속해서 계산해준다.
        }

        return startNum;
    }

    public static ArrayList<Integer> product(ArrayList<Integer> operArr){

        ArrayList<Integer> returnList = new ArrayList<>();
        boolean[] numArr = new boolean[operArr.size()]; // 들어가는 값이 연산자이면 false, 피연산자이면 true 체크
        int previousNum=0;

        returnList.add(operArr.get(0)); // 처음 숫자 insert
        numArr[0]=true; // 숫자이니깐 true.
        previousNum=operArr.get(0); // previousNum => 곱셈을 하기 전의 첫번째 피연산자

        for(int index=1;index<operArr.size();){ // OperArr 탐색
            if(numArr[returnList.size()-1]==true && operArr.get(index)=='*'){ // 곱하기연산일때 연산하여 previousNum과 계산하여 insert
                returnList.remove(returnList.size()-1); // previousNum이 들어있는것을 지우고
                previousNum=operate(previousNum,operArr.get(index),operArr.get(index+1)); // *연산을 실행 후
                returnList.add(previousNum); // *연산을 실행한 숫자를 insert
                numArr[returnList.size()-1]=true; // 숫자를 insert했기 때문에 true처리
                index+=2;
            }
            else if(numArr[returnList.size()-1]==false){ // 숫자일때
                returnList.add(operArr.get(index));
                previousNum=operArr.get(index); // 연산을하지않고 그냥 숫자 insert
                numArr[returnList.size()-1]=true;
                index++;
            }
            else if(numArr[returnList.size()-1]== true){ // *가 아닌 다른 연산일 때
                returnList.add(operArr.get(index)); // 연산추가
                index++;
            }
        }
        return returnList;
    }



    public static int operate(int num1,int oper,int num2){
        if(oper=='+')
            return num1+num2;
        else if(oper=='*')
            return num1*num2;
        else if(oper=='-')
            return num1-num2;

        return -1;
    }
}