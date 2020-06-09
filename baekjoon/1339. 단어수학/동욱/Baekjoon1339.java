import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Baekjoon1339 {

    static Map<Character, Integer> indexMap;
    static List<Alphabet> alphabetList;
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int N;
    static int cntAlphabet;
    public static void main(String[] args) throws IOException {
        inputData();
        Collections.sort(alphabetList);
        int num=9;
        int result = 0;
        for(int i=0;i<alphabetList.size();i++){
            Alphabet a = alphabetList.get(i);
            //System.out.println(a.alphabet+" : "+a.coefficient);
            result += (a.coefficient*num);
            num--;
        }
        System.out.println(result);
    }

    public static void inputData() throws IOException {
        N = Integer.parseInt(br.readLine());
        alphabetList = new ArrayList<Alphabet>();
        indexMap = new HashMap<>();
        cntAlphabet = 0;
        for(int i=0;i<N;i++) {
            String input = br.readLine();
            addCoefficient(input);
        }


    }

    private static void addCoefficient(String input) {
        int one =1;
        for(int i=input.length()-1;i>=0;i--){
            char c = input.charAt(i);
            if(indexMap.containsKey(c)){
                int idx = indexMap.get(c);
                int temp = alphabetList.get(idx).getCoefficient();
                temp +=one;
                alphabetList.get(idx).setCoefficient(temp);
            }
            else{
                alphabetList.add(new Alphabet(c,one));
                indexMap.put(c,alphabetList.size()-1);
            }
            one*=10;
        }
    }

    static class Alphabet implements Comparable<Alphabet>{
        char alphabet;
        int coefficient;

        public Alphabet(char alphabet, int coefficient) {
            this.alphabet = alphabet;
            this.coefficient = coefficient;
        }

        public void setCoefficient(int coefficient) {
            this.coefficient = coefficient;
        }

        public int getCoefficient() {
            return coefficient;
        }

        @Override
        public int compareTo(Alphabet o) {
            return o.coefficient - coefficient;
        }
    }
}
