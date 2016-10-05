// Problem: UPDATEIT from SPOJ

#include <bits/stdc++.h>
using namespace std;

void solve(){
	int n,u,i,l,r,v,idx;
	cin>>n>>u;

	int a[n];
	for(i=0;i<n;i++)a[i] = 0;

	while(u--){
		cin>>l>>r>>v;
		a[l]+=v;
		if(r+1<n)a[r+1]-=v;
	}

	for(i=1;i<n;i++){
		a[i]+=a[i-1];
	}

	cin>>u;

	while(u--){
		cin>>idx;
		cout<<a[idx]<<"\n";
	}

	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
}