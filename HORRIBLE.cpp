// Problem : HORRIBLE from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ll long long

void pUpd(ll bit[], int idx, ll v, int n){
	for(;idx<=n;idx+=(idx&(-idx)))bit[idx]+=v;
}

ll pQuery(ll bit[], int idx){
	ll ans = 0;	
	for(;idx>0;idx-=(idx&(-idx)))ans+=bit[idx];
	return ans;
}

void rUpd(ll bit[], ll offset[], int l, int r, int v, int n){
	pUpd(bit,l,v,n);
	pUpd(bit,r+1,-v,n);
	ll val = v;   // Integer overflow sucks :(
	pUpd(offset,l,val*(l-1),n);
	pUpd(offset,r+1,-val*r,n);
}

ll rQuery(ll bit[], ll offset[], int l, int r){
	ll v1 = pQuery(bit,l) * l - pQuery(offset,l);
	ll v2 = pQuery(bit,r) * r - pQuery(offset,r);
	return v2-v1;
}

void solve(){
	int n,c,p,q,v,i,type;
	cin>>n>>c;

	ll bit[n+1],offset[n+1];
	for(i=1;i<=n;i++)bit[i] = offset[i] = 0;

	while(c--){
		cin>>type;

		if(type==0){
			cin>>p>>q>>v;
			rUpd(bit,offset,p,q,v,n);
		}
		else{
			cin>>p>>q;
			cout<<max(rQuery(bit,offset,p-1,q),(ll)0)<<"\n";
		}
	}

	return ;
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}