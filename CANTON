#include<iostream>
using namespace std;

int main()
{
  long int t;
  cin>>t;
  
  long int i;
  long int n;
  long int q;
  
  for(i=0;i<t;i++)
  {
    cin>>q;
    
    n=1;
    
    while((n*(n+1)/2)<q)n++;
    
    long int sum = n+1;
    long int term = (n*(n+1)/2) - q + 1; 
    
    if(n%2!=0)
    {
    	 cout<<"TERM "<<q<<" IS "<<term<<"/"<<sum-term<<"\n";
    }
    else
    {
    	 cout<<"TERM "<<q<<" IS "<<sum-term<<"/"<<term<<"\n";
    }
    
  }
  return 0;
} 
    
       

