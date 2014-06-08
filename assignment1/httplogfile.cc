#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

		int printtill(char log[],int i,char limit,int a)   //will print from the ith character till the limiter is reached
		{						   //will return the i reached after the required increment	
			while(log[i]!=limit && log[i]!='\0')
			{
			cout<<log[i++];
			}
		i=i+a;
		return i;
		}

	void decoder(char log[])				   //will delegate task to printtill function and put requred strings in between
	{
	int i=0;
	cout<<"\n\nClient Name(Ip/Hostname):  ";
	i=printtill(log,i,' ',1);
	cout<<"\nClient Identity:  ";
	i=printtill(log,i,' ',1);
	cout<<"\nUserid:  ";
	i=printtill(log,i,' ',2);
	cout<<"\nDate:  ";
	i=printtill(log,i,':',1);
	cout<<"\nTime(hr:min:sec):  ";
	i=printtill(log,i,' ',1);
	cout<<"\t\tTimeZone:  ";
	i=printtill(log,i,']',3);
	cout<<"\nMethod:  ";
	i=printtill(log,i,' ',1);
	cout<<"\nRequested Resource:  ";
	i=printtill(log,i,' ',1);
	cout<<"\nProtocol:  ";
	i=printtill(log,i,'"',2);
	cout<<"\nStatus Code:  ";
	i=printtill(log,i,' ',1);
	cout<<"\nSize of Object Returned:  ";
	i=printtill(log,i,' ',2);
	cout<<"\nReferer:  ";
	i=printtill(log,i,'"',3);
	cout<<"\nUserAgent:  ";
	i=printtill(log,i,'"',0);
	}
	

int main(int argc,char *argv[])
{
FILE *fp;		
char newch[1000];
int i;
int c=0;
char ch;
				if(argc!=2)
				{
				    cout<<"\nError in parameter format\n";
				    return 0;
				}
	cout<<"Log-File requested:"<<argv[1]<<"\n";
	fp = fopen(argv[1], "r");
	    if (fp == NULL)
    	    {
	        cout<<"\nFailed to open the file\n";
	        return 1;
	    }
	else
	{
	cout<<"\nReading Logs serially";		
		do 
		{
		i=0;
		c=0;
			while(1)
			{
			ch=fgetc(fp);	
			if(ch=='\n' || ch==EOF)
			break;
			newch[i++]=ch;
			}  
		newch[i]='\0';
			if(strlen(newch)>1)
			{
			decoder(newch);
			cout<<"\nPress any key for next log..";
			getchar();			
			}
		}while(ch!=EOF); 
	cout<<"\n";
	fclose(fp);
	}
return 0;
}
