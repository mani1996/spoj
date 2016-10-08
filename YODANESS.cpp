// Problem : YODANESS from SPOJ

#include <bits/stdc++.h>
using namespace std;

void update(int BIT[], int v, int n){
	for(;v<=n;v+=(v&(-v)))BIT[v]++;
}

int query(int BIT[], int v){
	int ans = 0;
	for(;v>0;v-=(v&(-v)))ans+=BIT[v];
	return ans;
}

void solve(){
	int n,i;
	string s;
	unordered_map<string,int> Hash;
	cin>>n;
	int a[n];

	for(i=0;i<n;i++){
		cin>>s;
		Hash[s] = i+1;
	}

	for(i=0;i<n;i++){
		cin>>s;
		a[i] = Hash[s];
	}

	int BIT[n+1],res;
	for(i=1;i<=n;i++)BIT[i] = 0;

	res = 0;

	for(i=0;i<n;i++){
		res+=(a[i]-1-query(BIT,a[i]-1));
		update(BIT,a[i],n);
	}

	cout<<res<<"\n";
	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
}