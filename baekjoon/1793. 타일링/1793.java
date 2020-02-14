import java.util.Scanner;
import java.math.BigInteger;

public class Main {


    public static void main(String[] args){

        Scanner in = new Scanner(System.in);
        int tc;

        BigInteger[] D = new BigInteger[251];
        D[0]=new BigInteger("1");
        D[1]=new BigInteger("1");
        D[2]=new BigInteger("3");

        for(int i=3;i<=250;i++)
            D[i]=D[i-1].add(D[i-2].multiply(new BigInteger("2")));

        while(in.hasNextInt()){
            tc=in.nextInt();
            System.out.println(D[tc]);
        }

    }



}


