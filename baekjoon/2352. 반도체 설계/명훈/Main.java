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
