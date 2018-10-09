#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#define OPERATORSTACKSIZE 20 //�����ջ����
#define NUMBERSTACKSIZE 20 //������ջ����
#define EQUATIONLEN 30 //�洢����ʽ�ַ����ĳ���
#define BRACKETSTACKMAX 30 //�������ջ�ĳ���
//����ջ-���������������ʽ������ֵ
typedef struct computingstack
{
	int operatorstop;
	char operators[20]; //�����ջ
	float number[20]; //������ջ
	int numbertop;
}CS;
typedef struct bracketstack
{
	char bracket[BRACKETSTACKMAX];//�������
	int top;
}BS;
const char prioritizedlist[][8]=
{
	' ','+','-','*','/','(',')','#',	//��������ȱ�
	'+','>','>','<','<','<','>','>',
	'-','>','>','<','<','<','>','>',
	'*','>','>','>','>','<','>','>',
	'/','>','>','>','>','<','>','>',
	'(','<','<','<','<','<','=',' ',	
	'#','<','<','<','<',' ',' ','='	
};
void operatorpush(CS *expression,char opera);//�������ջ����
void operatorpop(CS *expression);//�������ջ����
void numberpush(CS *expression,int num);//��������ջ����
void numberpop(CS *expression);//��������ջ����
void operatorcomparing(CS *expression,char p2);//��������ȱȽ�
void computing(CS *expression,char *equation);//������ջ������ݽ�������
void computingstackInit(CS *expression);//��ʼ������ջ
int readnumber(char **equation,int num);//���ַ���������������ת����һ����������
int BracketMatching(char *equation);//����ƥ�估����ʽ��ȷ�Եļ��ж�
int bracketpush(BS *verity,char x);//����ջ����ջ����
int bracketpop(BS *verity);//����ջ�ĳ�ջ����
int openfile(char questions[][20]);//��ȡ�ļ�
void simpleBuild(char questions[][20],int nummax);
void testing(char questions[][20],int nummax);
int main(){
	int num=0,nummax;
	char questions[200][20];
	printf("\t\t\t\t\t�Զ�����ϵͳ\n\n");
	printf("\t\t\t\t1.��������\n");
	printf("\t\t\t\t2.���װ����\n");
	printf("���������ѡ��:");
	scanf("%d",&num);
	nummax=openfile(questions);
	if(num==1)
		simpleBuild(questions,nummax);
	else
		testing(questions,nummax);
	system("pause");
	return 0;
}
void testing(char questions[][20],int nummax)
{
	int num,index;
	int i,j;
	int correctnum=0;
	float answer;
	CS expression;
	computingstackInit(&expression);//��ʼ��ջ
	
	printf("�������������");
	scanf("%d",&num);
	srand((unsigned)time(NULL)); 
	for(i=0;i<num;i++)
	{

		computingstackInit(&expression);//��ʼ��ջ
		
		index=rand()%nummax;
		if(BracketMatching(questions[index]))
		{
			computing(&expression,questions[index]);
			for(j=0;j<20;j++)
			{
				if(questions[index][j]!='#')
					printf("%c",questions[index][j]);
				else
				{
					printf("=");
					scanf("%f",&answer);
					if((int)expression.number[expression.numbertop]*10%10!=0)
					{
						if(fabs(expression.number[expression.numbertop]-answer)>0.01)
						{
							printf("\n�Բ��������ˣ���ȷ����%.2f\n\n",expression.number[expression.numbertop]);
						}
						else
						{
							printf("\n��ϲ�����ˣ��������һ��\n");
							correctnum++;
						}
					}
					else
					{
						if(fabs(expression.number[expression.numbertop]-answer)>0.0001)
						{
							printf("\n�Բ��������ˣ���ȷ����%.0f\n\n",expression.number[expression.numbertop]);
						}
						else
						{
							printf("\n��ϲ�����ˣ��������һ��\n");
							correctnum++;
						}
					}
					break;
				}
			}
		}
		else
		{
			i--;
		}
	
	}
	printf("---------------------------------------\n");
	printf("�������\n������Ϊ%d\n��ȷ����Ϊ%d\n����ܷ�Ϊ%.0f\n",num,correctnum,1.0*correctnum/num*100);
	printf("---------------------------------------");
}
void simpleBuild(char questions[][20],int nummax)
{
	int num,index;
	int i,j;
	CS expression;
	computingstackInit(&expression);//��ʼ��ջ
	
	printf("�������������");
	scanf("%d",&num);
	srand((unsigned)time(NULL)); 
	for(i=0;i<num;i++)
	{

		computingstackInit(&expression);//��ʼ��ջ
		
		index=rand()%nummax;
		if(BracketMatching(questions[index]))
		{
			computing(&expression,questions[index]);
			for(j=0;j<20;j++)
			{
				if(questions[index][j]!='#')
					printf("%c",questions[index][j]);
				else
				{
					printf("=%.0f\n",expression.number[expression.numbertop]);
					break;
				}
			}
		}
		else
		{
			i--;
		}
		
	}
}
int openfile(char questions[][20])
{
	int i=0;
	FILE *fp;
	char question[100][20];
	fp=fopen("timu.txt","r");
	for(i=0;!feof(fp);i++)
	{	
		fscanf(fp,"%s",questions[i]);
	}
	fclose(fp);
	return i;
}
//��ʼ������ջ
void computingstackInit(CS *expression)
{
	expression->numbertop=-1;
	expression->operatorstop=-1;
	operatorpush(expression,'#');
}

//������ջ������ݽ�������
void computing(CS *expression,char *equation)
{
	while(*equation)
	{
		if(*equation>47&&*equation<58)
		{
			numberpush(expression,readnumber(&equation,*equation-48));
		}
		else 
		{
			operatorcomparing(expression,*equation);
		}
		equation++;
	}

}

//��������ȱȽ�
void operatorcomparing(CS *expression,char p2)
{
	int i,j;
	for(i=1;i<8;i++)
	{
		if(p2==prioritizedlist[0][i])break;
	}
	for(j=1;j<8;j++)
	{
		if(expression->operators[expression->operatorstop]==prioritizedlist[j][0])break;
	}
	switch(prioritizedlist[j][i])
	{
		case '>':
			switch(expression->operators[expression->operatorstop])
			{
				case '+':
					expression->number[expression->numbertop-1]+=expression->number[expression->numbertop];
					numberpop(expression);
					operatorpop(expression);
					break;
				case '-':
					expression->number[expression->numbertop-1]-=expression->number[expression->numbertop];
					numberpop(expression);
					operatorpop(expression);
					break;
				case '*':
					expression->number[expression->numbertop-1]*=expression->number[expression->numbertop];
					numberpop(expression);
					operatorpop(expression);
					break;
				case '/':
					expression->number[expression->numbertop-1]/=expression->number[expression->numbertop];
					numberpop(expression);
					operatorpop(expression);
					break;
			}
			operatorcomparing(expression,p2);
			break;
		case '<':
			operatorpush(expression,p2);
			break;
		case '=':
			operatorpop(expression);
			break;
	}
}

//���ַ���������������ת����һ����������
int readnumber(char **equation,int num)
{
	if(*(*equation+1)>47&&*(*equation+1)<58)
		readnumber(equation,num*10+*(++*equation)-48);
	else return num;
}

//�������ջ����
void operatorpush(CS *expression,char opera)
{
	if(expression->operatorstop>OPERATORSTACKSIZE-1)
	{
		printf("ջ�����޷���ӣ�");
		return;
	}
	else
	{
		(expression->operatorstop)++;
		expression->operators[expression->operatorstop]=opera;
		
	}
}

//�������ջ����
void operatorpop(CS *expression)
{
	if(expression->operatorstop>-1)
	{
		expression->operators[expression->operatorstop]=' ';
		expression->operatorstop--;
	}
}

//��������ջ����
void numberpush(CS *expression,int num)
{
	if(expression->numbertop>NUMBERSTACKSIZE-1)
	{
		printf("ջ�����޷���ӣ�");
		return;
	}
	else
	{
		(expression->numbertop)++;
		expression->number[expression->numbertop]=num;
	}
}

//��������ջ����
void numberpop(CS *expression)
{
	if(expression->numbertop>-1)
	{
		expression->number[expression->numbertop]=-1;
		expression->numbertop--;
	}
}

//����ƥ�估����ʽ��ȷ�Եļ��ж�
int BracketMatching(char *equation)
{
	int i;
	int f=0,f1=0;
	BS verity;
	verity.top=-1;
	while(*equation)
	{
		if(*equation=='+'||*equation=='-'||*equation=='*'||*equation=='/')
		{
			if(f1)
			{
				printf("�ж���������+��-��*��/������\n");
				return 0;
			}
			f1=1;
		}
		else if(*equation=='(')
		{	
			if(bracketpush(&verity,*equation))
			{
				f++;
				break;
			}
		}
		else if(*equation==')')
		{
			if(bracketpop(&verity,*equation))
			{
				f++;
				break;
			}
		}
		else 
		{
			f1=0;
		}
		equation++;
	}
	if(verity.top==-1)
	{
		if(f==0)
			return 1;
		else 
		{
			printf("����ʽ����  ");
			printf("-----ȱ��(\n");
			return 0;
		}
	}
	else 
	{
		printf("����ʽ����  ");
		printf("-----ȱ��)\n");
		return 0;
	}
}

//����ջ����ջ����
int bracketpush(BS *verity,char x)
{
	if(verity->top>=BRACKETSTACKMAX)return 1;
	else 
	{
		verity->bracket[verity->top+1]=x;
		verity->top++;
		return 0;
	}
}

//����ջ�ĳ�ջ����
int bracketpop(BS *verity,char x)
{
	if(verity->top==-1)return 1;
    else 
	{
		verity->top--;
		return 0;
	}
}
