#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char user_programname[50],file_programname[50],record[50],start_address[50],eaddr[10];
int recordpointer=0,pointer=0;
FILE *iptr,*optr;

void writeop();

int main()
{


    iptr = fopen("absinput.txt","r");
    optr = fopen("absop.txt","w");

    recordpointer=2;
    fgets(record,sizeof(record),iptr);
    while(record[recordpointer]!='^')
    {
        file_programname[pointer]=record[recordpointer];
        recordpointer++;
        pointer++;
    }

    printf("\nEnter the file name: ");
    scanf("%s",user_programname);

    if(strcmp(file_programname,user_programname)!=0)
    {
        printf("Error");
        return 1;
    }
    fgets(record,sizeof(record),iptr);
    while(record[0]!='E')
    {
        if(record[0]=='T')
        {
            strncpy(start_address,record+(2),6);
            start_address[6]='\0';
            recordpointer=12;
            writeop();

        }
        fgets(record,sizeof(record),iptr);
    }
    strncpy(eaddr,record+(2),6);
    printf("Address: %s",eaddr);
}

void writeop()
{
    char object[50];
    int address=strtol(start_address,NULL,16);
    while(record[recordpointer]!='\0')
    {
        fprintf(optr,"%x\t",address);
        strncpy(object,record+(recordpointer),6);
        object[6]='\0';
        fprintf(optr,"%s\n",object);
        address+=3;
        recordpointer+=7;
        if(record[recordpointer]=='^')
        {
            recordpointer++;
        }
    }
}
