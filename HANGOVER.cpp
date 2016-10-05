// Problem : HANGOVER from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ld long double

ld dp[1001];

void compute(){
	dp[0] = 0.0;
	int i;
	for(i=1;i<=1000;i++){
		dp[i] = dp[i-1] + (1/ (ld) (i+1));
	}

	return ;
}

int main(){
	compute();
	ld x;
	scanf("%Lf", &x);

	while(x!=0.0){
		printf("%ld card(s)\n",lower_bound(dp,dp+1001,x)-dp);
		scanf("%Lf", &x);
	}
}