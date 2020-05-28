# 2616 소형기관차

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83150768-a4002400-a136-11ea-830c-e09f42339cdb.png)

## 문제 알고리즘

- 브루트포스

## 풀이방법

1. combination으로 치킨집을 M개 고른다.

2. 순서가 없는 치킨집 M개를 선택하여, 가게에서 치킨집까지의 최소거리를 구한다.

3. 치킨집 set 마다 최소거리를 업데이트 해준다.

- 핵심 코드

```java
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

```

## 문제 후 느낀점

- java에서는 combination을 구할려면 직접 짜야하는 부분이 까다롭다.
