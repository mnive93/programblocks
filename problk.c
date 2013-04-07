#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int number=0;
struct prgblk
{
char name[100];
int num;
int length;
int start;
int end;
}p[100];
int addr_calc(char line[100],int addr)
{
char op[100],oper[100];
int val;
if(strstr(line,"EQU")!=0 || strstr(line,"START")!=0 )
return addr;
	if(strstr(line,"RESW")!=0)
				{
					sscanf(line,"%s %s %04x",oper,op,&val);
					
					addr+=3*val;
				}
	else if(strstr(line,"RESB")!=0)
				{
					sscanf(line,"%s %s %d",oper,op,&val);
					//printf("%04x..\n",val);	
					addr+=val;
				}

			else
			addr+=3;
			
return addr;
}
int search(char str[100])
{
int i;
for(i=0;i<=number;i++)
{
if(strcmp(str,p[i].name)==0)
return i;
}
return -1;
}
void load_table()
{
int i;
for(i=0;i<=number;i++)
{
if(i!=0)
p[i].start = p[i-1].start + p[i-1].length;
}

}
void load_prgblock(char prg[100][100],int size)
{
	int addr,num;
		int i,flag=0;
	char op[100],oper[100];
	printf("enter the startin address\n");
	scanf("%04x",&addr);
		for(i=0;i<size;i++)
		{
			
		
		if(strstr(prg[i],"USE")!=0)
			{
				
				sscanf(prg[i],"%s %s",op,oper);
			if(isalpha(oper[0]))
			{
			num=search(oper);
			if(num==-1)
			{
			strcpy(p[number].name,oper);
			addr=0;
			}			
else
			{
			addr = p[num].end;
			flag=1;
			number=number-1;
			}
			}
else
{

number=number-1;
flag=1;
num=search("default");
addr = p[num].end;
}
i+=1;
}
else
			{
				
				strcpy(p[number].name,"default");
			}
			
if(number==0)
p[number].start = addr;
			
				while(1)
					{
						
										
					if(strstr(prg[i],"USE")!=0)
						{
							printf("%s\n",prg[i]);	
						if(flag!=1)
						{
						p[number].end=addr;
						p[number].length = p[number].end;
						number+=1;
						}
						else
						{
						
						p[num].end = addr;
						p[num].length = p[num].end;
						
						flag=0;
						}						
						i-=1;
						break;
						}
						if(flag==1)
						printf("%04x\t%d\t%s\n",addr,num,prg[i]);
						else
						printf("%04x\t%d\t%s\n",addr,number,prg[i]);
						
					addr= addr_calc(prg[i],addr);
						i+=1;	
						if(i==(size-1))
						{
						if(flag!=1)
						{
							p[number].end = addr;
					p[number].length = p[number].end;
}						
else
{				p[num].end = addr;
p[num].length = p[num].end;
											
}						break;
						}
					} 

			
			}
load_table();
}
int main()
{
int i=0;
FILE * fp;
	fp=fopen("prg.txt","r");
	
char line[100];
char prg[100][100];
while(fgets ( line, sizeof(line), fp )!=NULL)
	{
		strcpy(prg[i],line);	
		i+=1;
	}
load_prgblock(prg,i);
for(i=0;i<=number;i++)
{
printf("%s %d %04x %04x \n  ",p[i].name,i,p[i].start,p[i].length);
}
return 0;
}
