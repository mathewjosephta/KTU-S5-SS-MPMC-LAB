#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void main()
{
    FILE *fp1,*fp2,*fp3,*fp4;
    char label[20],opcode[20],operand[20],op[20],value[20];
    int locctr,flag,op1;

    fp1=fopen("input.txt","r");
    fp2=fopen("optab.txt","r");
    fp3=fopen("output.txt","w");
    fp4=fopen("symtab.txt","w");

    if(fp1==NULL || fp2==NULL || fp3==NULL || fp4==NULL)
    {
        printf("Error opening files!\n");
        exit(1);
    }

    fscanf(fp1,"%s%s%x",label,opcode,&op1);

    while(!feof(fp1))
    {
        if(strcmp(opcode,"START")==0)
        {
            locctr=op1;
            fprintf(fp3,"**\t%s\t%s\t%x\n",label,opcode,op1);  
            fscanf(fp1,"%s%s%s",label,opcode,operand);        
        }
        else
        {
            flag=0;
            rewind(fp2);
            while(fscanf(fp2,"%s%s",op,value)!=EOF)
            {
                if(strcmp(op,opcode)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1 && strcmp(label,"**")!=0)
            {
                fprintf(fp4,"%s\t%x\n",label,locctr);
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                locctr+=3;
            }
            else if(flag==1)
            {
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                locctr+=3;
            }
            else if(flag==0 && strcmp(opcode,"WORD")==0)
            {
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                fprintf(fp4,"%s\t%x\n",label,locctr);
                locctr+=3;
            }
            else if(flag==0 && strcmp(opcode,"RESW")==0)
            {
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                fprintf(fp4,"%s\t%x\n",label,locctr);
                locctr=locctr+3*atoi(operand);
            }
            else if(flag==0 && strcmp(opcode,"RESB")==0)
            {
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                fprintf(fp4,"%s\t%x\n",label,locctr);
                locctr=locctr+atoi(operand);   
            }
            else if(flag==0 && strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                fprintf(fp4,"%s\t%x\n",label,locctr);
                locctr=locctr+strlen(operand)-3;
            }

            fscanf(fp1,"%s%s%s",label,opcode,operand);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}
