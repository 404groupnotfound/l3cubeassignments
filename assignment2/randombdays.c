#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#define MAX 366

int cdate,cmonth;
int dates[MAX];
int months[MAX];    
int brandom(int temp)
{
  int k;
  
  cmonth=1+(rand()%(int)(12-1+1));
  
  if(cmonth==2)
  {
    cdate=1+(rand()%(int)(28-1+1));
  }
  else if(cmonth==4 || cmonth==6 || cmonth==9 || cmonth==11)
  {
     cdate=1+(rand()%(int)(30-1+1)); 
  }
  else
  {
     cdate=1+(rand()%(int)(31-1+1)); 
  }
  
  dates[temp]=cdate;
  months[temp]=cmonth;
  for(k=0;k<temp;k++)
  {
    if(dates[k]==cdate && months[k]==cmonth)
    {
      return 1;
    }
  }
  return 0;
} 

int main()
{
  time_t t;
  int i,j,bcount;
  int pr=0;
  float z=40000;
 // float t;
  int flag=0;
  srand((unsigned)time(&t)); //initialize random nos generator
  printf("Enter the number of people:-");
  scanf("%d",&bcount);

  for(i=0;i<40000;i++)
  {
    for(j=0;j<bcount;j++)
    {
      if(brandom(j)) 
      {
        pr=pr++;
        break;
      }
    }
  
  }
    

  
 printf("Probability of people with same bday:-%f\n",(float)pr/z);  
  return 0;
}
