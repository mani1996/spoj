#include <iostream>
using namespace std;

unsigned long long gcd(unsigned long long a,unsigned long long b)
{
	if(a==0)
	{
		return b;
	}
	else if(b==0)
	{
		return a;
	}
	else if(a%b==0)
	{
		return b;
	}
	else if(b%a==0)
	{
		return a;
	}
	else if(a>b)
	{
		return gcd(a%b,b);
	}
	else
	{
		return gcd(a,b%a);
	}
}

int main() 
{
	long t;
	cin>>t;
	unsigned long long n,v,num,den,g;
	while(t--)
	{
		cin>>n;
		
		if(n%2==0)
		{
			cout<<"1/"<<4*n<<"\n";
		}
		else
		{
			v = (n/2)+1;
			num = 6*v*v - 6*v + 2;
			den = 6*n*n*n;

			g = gcd(num,den);
			
			num = num/g;
			den = den/g;
			cout<<num<<"/"<<den<<"\n";
		}
		
	}
	return 0;
}
