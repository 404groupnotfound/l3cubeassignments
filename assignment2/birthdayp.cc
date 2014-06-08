#include<iostream>
using namespace std;

int main()
{
int N=1;
int a;
double ans;
double temp;
temp=365;
while(N!=0)
{
ans=1;
cout<<"\nEnter N:";
cin>>N;
int i;
int j=364;
for(i=1;i<N;i++)
{
    j=j-1;
    ans=(ans*(double)j)/temp;
}
cout<<"\t"<<(1-ans);
}
return 0;
}
