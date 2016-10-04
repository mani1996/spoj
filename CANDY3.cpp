#include <iostream>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	long long int t;
	cin>>t;
	long long int r,n,n1,s;
	
	while(t--)
	{
		s = 0;
		cin>>n;
		n1 = n;
		while(n1--)
		{
			cin>>r;
			s+=r;
			s%=n;
		}
		
		if(s%n==0)
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
		
	}
	return 0;
}

