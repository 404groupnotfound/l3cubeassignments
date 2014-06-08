#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define MAX 100

int main()
{

FILE *fp;
char path[30][200];
char dupli[20][300];
char command[1024];
int ch;
char file[MAX];
char temp[MAX];
int flag=0;
int counter[MAX];
int count=0;
int pcount=0;
int dcount=0;
int opt;
int i=0,j=0;
char reqpath[100];

printf("\nPlease enter the mountpoint of the harddisk:");
fgets (reqpath, 100, stdin);

for(i=0;i<=100;i++)
{
		if(reqpath[i]=='\n' || reqpath[i]=='\0')
		{
		reqpath[i]='/';		
		reqpath[i+1]='\0';		
		break;		
		}
	if(reqpath[i]==' ')
	{
		for(j=99;j>=i;j--)
		{
		reqpath[j+1]=reqpath[j];
		}
	reqpath[i]='\\';
	i++;	
	}
		
}


strcpy(command,"cd ");
strcat(command,reqpath);
strcat(command," && find -type f -printf '%f\n' | sort|uniq -c -d > /duplicates.txt");
system((char *)command);
   
fp= fopen("/duplicates.txt","r");
dcount=0;
opt=1;
flag=1;
pcount=0;
while(1)
{	
	
  ch=fgetc(fp);
			if(ch==EOF)
			{			
			break;
			}
	if(opt!=0)
	{	
	printf("Sr.No.)  Count   |   filename \n");
	count=0;
	opt=0;
	}
	
	if(flag==1)
	printf("%d)",++count);
				

	flag++;
		if(flag==9)
		printf(" | ");		
		printf("%c",ch);	
	if(flag>9)
	{
	dupli[count-1][pcount++]=ch;	
	}	
	if(ch=='\n')
	{	
	dupli[count-1][pcount-1]='\0';	
	pcount=0;	
	dcount++;
	flag=1;	
	}	
		if(dcount==20)
		{		
			pcount=0;		
			printf("\nPress 0 to stop seeing Duplicate entries or 1 to see next duplicates:");
			scanf("%d",&opt);
			dcount=0;
			flag=1;
			if(opt==0)
			break;  		
		}
}
fclose(fp);

printf("\nEnter the correct serial number of the filename:- \n");
scanf("%d",&opt);
while(opt>count || opt<=0)
{
printf("\nPlease enter a valid Serial Number:");
scanf("%d",&opt);
}
strcpy(file,dupli[opt-1]);

while(1)
{
sprintf(command, "cd %s  && find -type f -name %s >/path.txt",reqpath,file);
system((char *)command);
count=0;
fp=fopen("/path.txt","r");
ch=fgetc(fp);
pcount=0;
while(ch != EOF)
{
  while(ch != '\n')
  {
   path[pcount][count++]=ch;
   ch=fgetc(fp);
  }
   path[pcount][count]='\0';
 count=0;
 pcount++;
 ch=fgetc(fp);
}
fclose(fp);
printf("\nMultiple paths where %s is located:-\n",file);
for(count=0;count<pcount;count++)
{
  printf("%d) %s \n",count+1,path[count]);
}

printf("Enter the path choice for %s to be deleted or 0 to terminate deletion Process:-",file);
scanf("%d",&ch);
while(ch>pcount || ch<0)
{
printf("Enter the Correct path choice for %s to be deleted or 0 to terminate deletion Process:-",file);
scanf("%d",&ch);
}

if(ch==0)
break;

for(i=0;i<=200;i++)
{
		if(path[ch-1][i]=='\n' || path[ch-1][i]=='\0')
		{
		path[ch-1][i]='\0';		
		break;		
		}
	if(path[ch-1][i]==' ')
	{
		for(j=199;j>=i;j--)
		{
		path[ch-1][j+1]=path[ch-1][j];
		}
	path[ch-1][i]='\\';
	i++;	
	}
		
}
sprintf(command, "cd %s && rm %s",reqpath,path[ch-1]);
system((char *)command);
printf("\nThe Specified file has been deleted");
pcount--;

if(pcount==0)
break;

}
return 0;
}
