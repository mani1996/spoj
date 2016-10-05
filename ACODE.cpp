// Problem : ACODE from SPOJ

#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(string s){
	int l = s.length(),i,code;
	ll dp[l][2];

	for(i=0;i<l;i++){
		if(i==0){
			dp[i][0] = ((s[i]!='0')?1:0);
			dp[i][1] = 0;
		}
		else{
			code = (s[i-1]-'0')*10 + s[i]-'0';

			if(s[i]=='0'){
				dp[i][0] = 0;
			}
			else{
				dp[i][0] = dp[i-1][0] + dp[i-1][1];
			}

			if(code>=10 && code<=26){
				if(i==1){
					dp[i][1] = 1;
				}
				else{
					dp[i][1] = dp[i-2][0] + dp[i-2][1];
				}
			}
			else{
				dp[i][1] = 0;
			}
		}
	}

	cout<<(dp[l-1][0] + dp[l-1][1])<<"\n";
	return ;
}

int main(){
	string s;
	cin>>s;

	while(s!="0"){
		solve(s);
		cin>>s;
	}

	return 0;
}