// Problem : ONEZERO from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int par[25001];
char dig[25001];

void solve(){
	int n,i,v1,v2,end,cur;
	string res = "";
	cin>>n;
	for(i=0;i<=n;i++)par[i] = -1,dig[i] =  '0';
	par[1] = 1;

	queue<int> q;
	q.push(1);

	while(!q.empty()){
		cur = q.front();
		q.pop();

		v1 = (cur*10)%n;
		v2 = (v1+1)%n;

		if(par[v1] == -1){
			par[v1] = cur;
			dig[v1] = '0';
			q.push(v1);
		}

		if(par[v2] == -1){
			par[v2] = cur;
			dig[v2] = '1';
			q.push(v2);
		}
	}

	end = 0;
	while(par[end]!=end){
		res+=dig[end];
		end = par[end];
	}
	res+='1';
	reverse(res.begin(),res.end());
	cout<<res<<"\n";
	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}