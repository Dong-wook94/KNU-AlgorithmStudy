# 2352 반도체 설계

![image](https://user-images.githubusercontent.com/42582516/81906764-b55b1380-9601-11ea-8461-0d41bd86aeee.png)



## 문제 알고리즘

- LIS



## 풀이방법

* LIS 풀이대로 풀었다.
* 가장 긴 오름차순 부분 수열을 찾으면 된다.



- 핵심 코드

~~~java
import java.io.*;
import java.util.*;

public class Main {
	static final int MAX = 40000;

	static int N;
	static int Port[];
	static Vector<Integer> PortV;

	public static void main(String[] args) throws NumberFormatException, IOException {
		init();
		solution();
	}

	public static void init() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		Port = new int[N];
		for (int i = 0; i < N; i++)
			Port[i] = Integer.parseInt(st.nextToken());
		PortV = new Vector<Integer>();
	}

	public static void solution() {
		PortV.add(Port[0]);
		// i번째 port가 연결된다고 가정한 후
		for (int i = 1; i < N; i++) {
			// 수의 크기가 점점 증가하는 형태의 부분 수열 중 가장 긴 것을 선택
			if (Port[i] > PortV.lastElement()) {
				PortV.add(Port[i]);
			} else {
				int j = 0;
				for (j = 0; j < PortV.size(); j++) {
					if (Port[i] > PortV.get(j))
						continue;
					else
						break;
				}
				PortV.remove(j);
				PortV.add(j, Port[i]);
			}
		}

		System.out.println(PortV.size());
	}

}

~~~



## 문제 후 느낀점

- LIS 문제
