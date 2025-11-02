#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDuplicate(char l[])
{
    FILE *sym;
    char slabel[50];
    int address;

    sym = fopen("symtab.txt","r");
    if(sym==NULL)
    {
        return 0;
    }

    while(fscanf(sym,"%s%x",slabel,&address)!=EOF)
    {
        if(strcmp(slabel,l)==0)
        {
            fclose(sym);
            return 1;
        }
    }
    fclose(sym);
    return 0;
}

int isValidOp(char l[])
{
    FILE *op;
    char sopcode[50], value[10];
    op = fopen("optab.txt","r");

    if (op == NULL) {
        printf("Error: Cannot open opcode.txt\n");
        return 0;
    }

    while(fscanf(op,"%s%s",sopcode,value)!=EOF)
    {
        if(strcmp(sopcode,l)==0)
        {
            fclose(op);
            return 1;
        }
    }
    fclose(op);
    return 0;
}


int main()
{
    FILE *f1,*f2,*f3;
    char label[50],opcode[50],operand[50];
    int SA=0,LOCCTR=0;

    f1 = fopen("input.txt","r");
    f2 = fopen("symtab.txt","w+");
    f3 = fopen("intermediate.txt","w");

    fscanf(f1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        SA=strtol(operand,NULL,16);
        LOCCTR=SA;
        fprintf(f3,"%x\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand);
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    else
    {
        LOCCTR=0;
    }
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(f3,"%x\t",LOCCTR);
        if(strcmp(label,"-")!=0)
        {
            if(isDuplicate(label))
            {
                printf("Error duplicate");
                return 1;
            }
            else
            {
                fprintf(f2,"%s\t%x",label,LOCCTR);
                fflush(f2);
            }
        }


        if(strcmp(opcode,"WORD")==0)
        {
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            LOCCTR+=atoi(operand)*3;
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            LOCCTR+=atoi(operand);
        }
        else if (strcmp(opcode,"BYTE")==0)
        {
            int len=strlen(operand)-3;
            if(opcode[0]=='X' ||opcode[0]=='x')
            {
                len=(len+1)/2;
            }
            LOCCTR+=len;
        }
        else if(isValidOp(opcode))
        {
            LOCCTR+=3;
        }
        else
        {
            printf("yo");
            exit(1);
        }

        fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }

    fprintf(f3,"%s\t%s\t%s\n",label,opcode,operand);

    int length=LOCCTR-SA;
    printf("length %d",length);

    return 1;
}
