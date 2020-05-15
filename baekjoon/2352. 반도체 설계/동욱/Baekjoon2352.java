import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Baekjoon2352 {

    static int numPort;
    static List<Integer> port;

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        numPort = scan.nextInt();
        port = new ArrayList<Integer>();
        port.add(0);
        for(int i=0;i<numPort;i++){
            int temp = scan.nextInt();
            if(port.get(port.size()-1) < temp) //끝값 보다 클
                port.add(temp);
            else {
                int idx = 0;
                for (int j = 0; j < numPort; j++) {
                    if (temp <= port.get(j)) {
                        idx = j;
                        break;
                    }

                }
                port.set(idx, temp);
            }
        }
        System.out.println(port.size()-1);
    }
}
