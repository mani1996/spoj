#include<iostream>
using namespace std;

int main()
{
   int n,i;
   cin>>n;
   long int sum,ans,avg;
   
   while(n!=-1)
   {
     int array[n];
     sum = 0;
     ans = 0;
     for(i=0;i<n;i++)
     {
       cin>>array[i];
       sum+=array[i];
     }
     
     
     if(sum%n!=0)
     {
       cout<<-1<<"\n";
     }
     else
     {
       avg = sum/n;
       for(i=0;i<n;i++)
       {
         if(array[i]< avg)
         {
           ans+=avg-array[i];
         }
       }
       cout<<ans<<"\n";
     }
     
     cin>>n;
  }
  return 0;
}
     
