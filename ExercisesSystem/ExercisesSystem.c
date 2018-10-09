#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#define OPERATORSTACKSIZE 20 //运算符栈长度
#define NUMBERSTACKSIZE 20 //运算数栈长度
#define EQUATIONLEN 30 //存储运算式字符串的长度
#define BRACKETSTACKMAX 30 //存放括号栈的长度
//运算栈-用来解析算术表达式便于求值
typedef struct computingstack
{
	int operatorstop;
	char operators[20]; //运算符栈
	float number[20]; //运算数栈
	int numbertop;
}CS;
typedef struct bracketstack
{
	char bracket[BRACKETSTACKMAX];//存放括号
	int top;
}BS;
const char prioritizedlist[][8]=
{
	' ','+','-','*','/','(',')','#',	//运算符优先表
	'+','>','>','<','<','<','>','>',
	'-','>','>','<','<','<','>','>',
	'*','>','>','>','>','<','>','>',
	'/','>','>','>','>','<','>','>',
	'(','<','<','<','<','<','=',' ',	
	'#','<','<','<','<',' ',' ','='	
};
void operatorpush(CS *expression,char opera);//运算符入栈函数
void operatorpop(CS *expression);//运算符出栈函数
void numberpush(CS *expression,int num);//运算数入栈函数
void numberpop(CS *expression);//运算数出栈函数
void operatorcomparing(CS *expression,char p2);//运算符优先比较
void computing(CS *expression,char *equation);//对运算栈里的数据进行运算
void computingstackInit(CS *expression);//初始化运算栈
int readnumber(char **equation,int num);//把字符串中连续的数字转换成一个整型数字
int BracketMatching(char *equation);//括号匹配及运算式正确性的简单判断
int bracketpush(BS *verity,char x);//括号栈的入栈操作
int bracketpop(BS *verity);//括号栈的出栈操作
int openfile(char questions[][20]);//读取文件
void simpleBuild(char questions[][20],int nummax);
void testing(char questions[][20],int nummax);
int main(){
	int num=0,nummax;
	char questions[200][20];
	printf("\t\t\t\t\t自动出题系统\n\n");
	printf("\t\t\t\t1.基础出题\n");
	printf("\t\t\t\t2.进阶版出题\n");
	printf("请输入你的选择:");
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
	computingstackInit(&expression);//初始化栈
	
	printf("请输入出题数：");
	scanf("%d",&num);
	srand((unsigned)time(NULL)); 
	for(i=0;i<num;i++)
	{

		computingstackInit(&expression);//初始化栈
		
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
							printf("\n对不起，你答错了，正确答案是%.2f\n\n",expression.number[expression.numbertop]);
						}
						else
						{
							printf("\n恭喜你答对了，请继续下一题\n");
							correctnum++;
						}
					}
					else
					{
						if(fabs(expression.number[expression.numbertop]-answer)>0.0001)
						{
							printf("\n对不起，你答错了，正确答案是%.0f\n\n",expression.number[expression.numbertop]);
						}
						else
						{
							printf("\n恭喜你答对了，请继续下一题\n");
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
	printf("测验结束\n总题数为%d\n正确题数为%d\n你的总分为%.0f\n",num,correctnum,1.0*correctnum/num*100);
	printf("---------------------------------------");
}
void simpleBuild(char questions[][20],int nummax)
{
	int num,index;
	int i,j;
	CS expression;
	computingstackInit(&expression);//初始化栈
	
	printf("请输入出题数：");
	scanf("%d",&num);
	srand((unsigned)time(NULL)); 
	for(i=0;i<num;i++)
	{

		computingstackInit(&expression);//初始化栈
		
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
//初始化运算栈
void computingstackInit(CS *expression)
{
	expression->numbertop=-1;
	expression->operatorstop=-1;
	operatorpush(expression,'#');
}

//对运算栈里的数据进行运算
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

//运算符优先比较
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

//把字符串中连续的数字转换成一个整型数字
int readnumber(char **equation,int num)
{
	if(*(*equation+1)>47&&*(*equation+1)<58)
		readnumber(equation,num*10+*(++*equation)-48);
	else return num;
}

//运算符入栈函数
void operatorpush(CS *expression,char opera)
{
	if(expression->operatorstop>OPERATORSTACKSIZE-1)
	{
		printf("栈满，无法添加！");
		return;
	}
	else
	{
		(expression->operatorstop)++;
		expression->operators[expression->operatorstop]=opera;
		
	}
}

//运算符出栈操作
void operatorpop(CS *expression)
{
	if(expression->operatorstop>-1)
	{
		expression->operators[expression->operatorstop]=' ';
		expression->operatorstop--;
	}
}

//运算数入栈操作
void numberpush(CS *expression,int num)
{
	if(expression->numbertop>NUMBERSTACKSIZE-1)
	{
		printf("栈满，无法添加！");
		return;
	}
	else
	{
		(expression->numbertop)++;
		expression->number[expression->numbertop]=num;
	}
}

//运算数出栈操作
void numberpop(CS *expression)
{
	if(expression->numbertop>-1)
	{
		expression->number[expression->numbertop]=-1;
		expression->numbertop--;
	}
}

//括号匹配及运算式正确性的简单判断
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
				printf("有多个运算符（+，-，*，/）相邻\n");
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
			printf("运算式有误！  ");
			printf("-----缺少(\n");
			return 0;
		}
	}
	else 
	{
		printf("运算式有误！  ");
		printf("-----缺少)\n");
		return 0;
	}
}

//括号栈的入栈操作
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

//括号栈的出栈操作
int bracketpop(BS *verity,char x)
{
	if(verity->top==-1)return 1;
    else 
	{
		verity->top--;
		return 0;
	}
}
