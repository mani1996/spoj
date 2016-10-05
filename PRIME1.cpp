// Problem: PRIME1 from SPOJ

#include <bits/stdc++.h>
using namespace std;

vector<int> primes;
bool isPrime[40001]; // use this to answer queries if n <= 40000

void sieve(){
	int i,j;

	for(i=1;i<=40000;i++)isPrime[i] = true;
	isPrime[1] = false;

	for(i=2;i<=200;i++){
		if(isPrime[i]){
			primes.push_back(i);
			for(j=2*i;j<=40000;j+=i)isPrime[j] = false;
		}
	}

	for(i=201;i<=40000;i++)if(isPrime[i])primes.push_back(i);

	return ;
}

void solve(){
	int m,n,i,c;
	cin>>m>>n;

	bool prime[n-m+1];
	for(i=0;i<n-m+1;i++)prime[i] = true;

	for(i=0;i<primes.size();i++){
		c = m%primes[i];
		if(c!=0)c = primes[i]-c;

		while(c<n-m+1){
			prime[c] = false;
			c+=primes[i];
		}
	}

	for(i=0;i<n-m+1;i++){
		if(m+i<=40000){
			if(isPrime[m+i])cout<<(m+i)<<"\n";
		}
		else{
			if(prime[i])cout<<(m+i)<<"\n";
		}
	}

	cout<<"\n";
	return ;
}

int main(){
	int t;
	cin>>t;

	sieve();

	while(t--){
		solve();
	}
}