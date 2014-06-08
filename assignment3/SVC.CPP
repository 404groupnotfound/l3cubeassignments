#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

int main(int argc,char *argv[])
{
    FILE *fp;
    fstream fp1;
    char rfile[20][10],line[100];
    int i=0,vno;
    if(argc!=2)
    {
	   cout<<"\n\n\tPass the required file only !!";
	   exit(0);                                                  //only one file can be passed as a parameter
    }
    else
    {
        if(strstr(argv[1],"."))
	{
	    for(i=0;i<20;i++)
	       rfile[i][0] = '\0';
        i=0;
        cout<<"File is "<<argv[1];
        try
        {
	    fp1.open(argv[1],ios::in);
	    while(!fp1.eof())
	    {
	        //line[0] = '\0';
	        if(i==20)
	        {
	            cout<<"\n\tFile has more than 20 lines !!";
	            exit(0);
	        }
		    fp1.getline(line,100);             //if passed parameter is a file
		    if(strlen(line)>=10)
		    {
		        cout<<"line "<<i+1<<" has more than 10 characters !!";
		        exit(0);
		    }
            strcpy(rfile[i],line);
		    strcat(rfile[i++],"\n");
	    }
        }
	     catch (std::ifstream::failure e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }
	    fp = fopen("sample.bin","ab");
	    if(fp==NULL)
	    {
	        cout<<"\n\n\tError opening file !!";
	        exit(0);
	    }
	    fwrite(&rfile,sizeof(rfile),1,fp);
	    fclose(fp);
	}
	else
	{
	    vno = atoi(argv[1]);
	    i=0;
	    fp = fopen("sample.bin","rb");
	    if(fp==NULL)
	    {
	        cout<<"\n\n\tError opening file !!";
	        exit(0);
	    }
        while (feof(fp) == 0)
        {
            fread(&rfile,sizeof(rfile), 1, fp);
            if (feof(fp) == 0)
            {
                i++;
            }
        }
	    if(vno >=i)
	    {
	        cout<<"\n\nVersion not available !!";
	        exit(0);
	    }
	    fseek(fp,sizeof(rfile)*vno,SEEK_SET);  //if we want to display a version
        fread(&rfile,sizeof(rfile),1,fp);
        cout<<"VERSION : "<<vno<<"\n\n";
        for(i=0;i<20;i++)
        {
            cout<<rfile[i];
        }
    }
    }
    return 0;
}
