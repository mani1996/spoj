// Problem : DALTSUM from SPOJ

#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define MOD 1000000007

ll power(ll n){
	ll res = 1,temp = 2;
	while(n){
		if(n%2)res*=temp;
		n/=2;
		temp*=temp;
		if(res>=MOD)res%=MOD;
		if(temp>=MOD)temp%=MOD;
	}
	return res;
}

int main(){
	int n,i;
	cin>>n;
	ll v,x;
	for(i=0;i<n;i++){
		cin>>x;
		if(i==0){
			v = x;
		}
		else{
			v = max(v,x);
		}
	}
	v = ((v%MOD)+MOD)%MOD;
	cout<<(v*power(n-1))%MOD;
	return 0;
}