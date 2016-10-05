// Problem: AGGRCOW from SPOJ

#include <bits/stdc++.h>
using namespace std;

int allotCows(int stall[], int n, int dist){
	int i = 0, cur = -dist-1;
	int cow = 0;

	for(i=0;i<n;i++){
		if(stall[i] >= cur+dist){
			cow++;
			cur = stall[i];
		}
	}

	return cow;
}


void solve(){
	int n,c,i;
	cin>>n>>c;

	int stall[n];
	for(i=0;i<n;i++)cin>>stall[i];
	sort(stall,stall+n);

	int low = 0,high = stall[n-1]-stall[0],mid;
	mid = (low+high)/2;

	while(low<high-1){
		if(allotCows(stall,n,mid)>=c){
			low = mid;
		}
		else{
			high = mid-1;
		}
		mid = (low+high)/2;
	}

	cout<<((allotCows(stall,n,high)>=c)?high:low)<<"\n";
}

int main(){
	int t;
	cin>>t;
	while(t--)solve();
}