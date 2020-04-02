# 브라이언의 고민

시간은 역대급으로 정말 많이썼다.

일단은 모든걸 고친것도 아니지만 

~~~c++
int main() {
	vector<string> v;
	v.push_back("HaEaLaLaObWORLDb");
	v.push_back("SpIpGpOpNpGJqOqA");
	v.push_back("AxAxAxAoBoBoB");
	v.push_back("abHELLObaWORLD");
	v.push_back("HaEaLaLaOWaOaRaLaD");
	v.push_back("aHELLOWORLDa");
	v.push_back("HaEaLaLObWORLDb"); //
	v.push_back("aHbEbLbLbOacWdOdRdLdDc");
	v.push_back("aBcAadDeEdvAvlElmEEEEm");
	v.push_back("AcAcABaBaB");//답이 2개가 될수있다.
	v.push_back("AxAxAxABcBcBcB");
	v.push_back("AaABbBCcC");
	v.push_back("HELLOWORLD");
	v.push_back("AAAaBaAbBBBBbCcBdBdBdBcCeBfBeGgGGjGjGRvRvRvRvRvR");//답이 2개가 될수있다.
	v.push_back("a");
	v.push_back("A");
	v.push_back("aA");
	v.push_back("Aa"); //이거안됨
	v.push_back("bTxTxTaTxTbkABaCDk");
	v.push_back("TxTxTxbAb");
	v.push_back("HaEaLaLaObWORLDbSpIpGpOpNpGJqOqAdGcWcFcDdeGfWfLeoBBoAAAAxAxAxAA");
	v.push_back("AxAxAxA");
	v.push_back("AA");
	v.push_back("oBBoA");
	v.push_back("aGbWbFbDakGnWnLk");
	v.push_back("A B");
	for (int i = 0; i < v.size(); i++) {
		cout <<i<<" : '"+v[i]<< endl;
		cout << "' -> " << "'" + solution(v[i]) + "'" << endl;
	}

}
~~~

메인을 이렇게 만들어서 테스트 해보았는데

중복으로 답이 생성되는 경우가 있다.

AcAcABaBaB 이경우에는 

1. A A A B B B인 경우랑
2. AAA BBB인 경우로 

2가지 경우가 생긴다.

너무 시간 오래썼다. 아무리 봐도 모르겠다...

엥간한 경우 다따졌는데.. 

Aa 경우에는 답아닌거 아는데 이미 신뢰가 안간다 이문제에...