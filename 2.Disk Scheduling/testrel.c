#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char bitmask[15];
char bit[65]={0};

void convert(char ch[]);

int main()
{
    FILE *ip,*op;
    int RelocBase,addr,h_addr,h_len,tlen,actual_addr,opcode,operand;
    char label[50],input[50];

    ip = fopen("RLIN.txt","r");
    op = fopen("ROUT.txt","w");

    printf("\nEnter the relocation base: ");
    scanf("%x",&RelocBase);

    while(fscanf(ip,"%s",input)==1 && strcmp(input,"E")!=0)
    {
        if(strcmp(input,"H")==0)
        {
            fscanf(ip,"%s",label);
            fscanf(ip,"%x",&h_addr);
            fscanf(ip,"%x",&h_len);
            fscanf(ip,"%s",input);
        }
        if(strcmp(input,"T")==0)
        {
            fscanf(ip,"%x",&addr);
            fscanf(ip,"%x",&tlen);
            fscanf(ip,"%s",bitmask);

            int Load_addr=addr+RelocBase;

            convert(bitmask);

            int num_instr=tlen/3;

            for(int i=0;i<num_instr;i++)
            {
                if(fscanf(ip,"%x",&opcode)!=1)
                    break;
                if(fscanf(ip,"%x",&operand)!=1)
                    break;

                if(bit[i]=='1')
                {
                    actual_addr=operand+RelocBase;
                }
                else
                    actual_addr=operand;
                fprintf(op,"%x\t%x%x\n",Load_addr,opcode,actual_addr);
                Load_addr+=3;

            }
        }

    }
    fclose(ip);
    fclose(op);

}

void convert(char ch[])
{
    strcpy(bit,"");
    int leng = strlen(ch);
    for(int i=0;i<leng;i++)
    {
        switch(ch[i])
        {
            case '0': strcat(bit,"0000"); break;
            case '1': strcat(bit,"0001"); break;
            case '2': strcat(bit,"0010"); break;
            case '3': strcat(bit,"0011"); break;
            case '4': strcat(bit,"0100"); break;
            case '5': strcat(bit,"0101"); break;
            case '6': strcat(bit,"0110"); break;
            case '7': strcat(bit,"0111"); break;
            case '8': strcat(bit,"1000"); break;
            case '9': strcat(bit,"1001"); break;
            case 'a': case 'A': strcat(bit,"1010"); break;
            case 'b': case 'B': strcat(bit,"1011"); break;
            case 'c': case 'C': strcat(bit,"1100"); break;
            case 'd': case 'D': strcat(bit,"1101"); break;
            case 'e': case 'E': strcat(bit,"1110"); break;
            case 'f': case 'F': strcat(bit,"1111"); break;

        }
    }
}
