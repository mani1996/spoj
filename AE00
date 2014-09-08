#include<iostream>
#include<cmath>
using namespace std;

int divisor(int n)
{
  int i;
  int ans = 0;
  for(i=1;i<=sqrt(n);i++)
  {
      if(n%i==0)ans++;
  }
  return ans;
}

int fn(int n)
{
   int a[10001];
   a[1] = 1;
   a[2] = 2;
   a[3] = 3;
   
   int i;
   
   for(i=4;i<=n;i++)
   a[i] = a[i-1] + divisor(i);
   
   
   return a[n];
}


int main()
{
  int n;
  cin>>n;
  cout<<fn(n);
  return 0;
}
