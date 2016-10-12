// Problem : PARADOX from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(int src, int next[], bool val[], int realVal[], bool& paradox, set<int>& nodes){
	nodes.insert(src);
	if(realVal[next[src]]!=-1){
		// Paradox can occur only when the DAG has a cycle
		if(nodes.find(next[src])!=nodes.end() && 
			realVal[next[src]] == realVal[src] ^ val[src])paradox = true;
	}
	else{
		realVal[next[src]] = !(realVal[src] ^ val[src]);
		dfs(next[src], next, val, realVal, paradox, nodes);
	}
}

void solve(int n){
	int next[n],i;
	bool val[n];
	string s;
	int realVal[n];
	for(i=0;i<n;i++){
		cin>>next[i]>>s;
		val[i] = ((s=="true")?true:false);
		next[i]--;
		realVal[i] = -1;
	}

	bool paradox = false,compParadox = false;
	set<int> nodes;

	for(i=0;i<n;i++){
		if(realVal[i] == -1){
			realVal[i] = 1;
			compParadox = false;
			nodes.clear();
			dfs(i,next,val,realVal,compParadox,nodes);
			paradox = paradox || compParadox;		
		}
	}
	
	cout<<((paradox)?"PARADOX":"NOT PARADOX");
	return ;
}

int main(){
	int t;
	cin>>t;
	while(t){
		solve(t);
		cin>>t;
		if(t)cout<<"\n";
	}
	return 0;
}