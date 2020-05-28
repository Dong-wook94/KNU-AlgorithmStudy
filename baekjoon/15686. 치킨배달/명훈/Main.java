import java.io.*;
import java.util.*;

public class Main {
    public static class Pos {
        int r;
        int c;

        Pos(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }

    private static final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    static int N, M;
    static int chickenLengthMin = Integer.MAX_VALUE;
    static int[] chickenLength;
    static int[] chickenShopIndexSet;
    static ArrayList<Pos> chickenShop, house;
    static boolean[] visited;
    static int HouseSize;

    public static void main(String[] args) throws IOException {
        init();
        solution();

        System.out.println(chickenLengthMin);
    }

    // init & input code
    public static void init() throws IOException {
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        chickenShopIndexSet = new int[M];

        chickenShop = new ArrayList<Pos>();
        house = new ArrayList<Pos>();

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < N; j++) {
                int key = Integer.parseInt(st.nextToken());
                if (key == 1) // add chicken house
                    house.add(new Pos(i, j));
                else if (key == 2) // add house
                    chickenShop.add(new Pos(i, j));
            }
        }

        HouseSize = house.size();
    }

    // solution codes
    public static void solution() {
        combination(chickenShopIndexSet, chickenShop.size(), M, 0, 0);
    }

    // combination, get combination index set
    static void combination(int[] chickenShopIndexSet, int n, int r, int index, int target) {
        if (r == 0) {
            int tempLength = getChickenLength(chickenShopIndexSet);
            if (chickenLengthMin > tempLength)
                chickenLengthMin = tempLength;
            return;
        }
        if (target == n)
            return;

        chickenShopIndexSet[index] = target;
        combination(chickenShopIndexSet, n, r - 1, index + 1, target + 1); // selected
        combination(chickenShopIndexSet, n, r, index, target + 1); // no selected
    }

    // get chicken Length from the point
    // int[] -> int
    static int getChickenLength(int[] chickenShopIndexSet) {
        chickenLength = new int[HouseSize];
        Arrays.fill(chickenLength, Integer.MAX_VALUE);

        // loop i..chickenShopIndexSet
        for (int i : chickenShopIndexSet) {
            // loop 0 .. house.size()
            for (int j = 0; j < HouseSize; j++) {
                chickenLength[j] = Math.min(chickenLength[j], Math.abs(chickenShop.get(i).r - house.get(j).r)
                        + Math.abs(chickenShop.get(i).c - house.get(j).c));
            }
        }

        // get sum minimum chicken length in chicken set
        int sum = 0;
        for (int i = 0; i < HouseSize; i++)
            sum += chickenLength[i];
        return sum;
    }

}
