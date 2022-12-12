#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 9125
#define MIN 550
#define MAX_MAX 80965

char ch1,ch2,ch3,*fp1,*fp2,*fp3;
FILE *fp_a, *fp_b, *fp_c, *fp_d;	
char temp[500];   //temp是暂时的意思,暂时定义一个数组 
int i,index=0;

struct movie{	//用户所看电影的信息 
	char m_id[20];	
	char m_name[500];	
	char m_ratings[20];
	char m_genre[500];	
};
struct user{	//用户ID对应所观看电影的评分 
	char u_id[20];	 
	char u_movies_id[20]; 
	char u_ratings[20];	
};
struct movie movies[MAX];
struct user users[MAX_MAX];

void function_A();   //选择框四个 
void function_B();
void function_C();
void function_D();

const char* msgs[4]={
	"A:Enter a user ID and a movie name to show the User's rating of the movie",
	"B:Enter the user ID and display the name of all the movies that the user has seen",
	"C:Enter the name of the movie to show which users have seen the movie",
	"D:Enter your user ID and you will be able to recommend movies you might like"
};

int main(void)
{
	fp_a=fopen("average_ratings.csv","r");
	fp_b=fopen("movie_genres.csv","r");
	fp_c=fopen("movie_names.csv","r");
	fp_d=fopen("user_ratings.csv","r");
	
	rewind(fp_a);    //rewind是将文件内部的位置指针重新指向一个流（数据流/文件）的开头
	rewind(fp_b);
	rewind(fp_c);
	rewind(fp_d);
 
	while(index<MAX)
	{
		for(i=0;(ch1=getc(fp_c))!='\n'&&ch1!=EOF;i++)
		{
			temp[i]=ch1;
			if(i>499)
				break;
		}
		
		temp[i]='\0';
		fp1 = strtok(temp,",");  //strtok函数的作用是把字符串以规定的字符分割开 
		strcpy(movies[index].m_id,fp1);     
		//strcpy，即string copy（字符串复制）的缩写。
//strcpy是一种C语言的标准库函数，strcpy把从src地址开始且含有’\0’结束符的字符串复制到以dest开始的地址空间，返回值的类型为char*。
		fp1 = strtok(NULL,",");   
		strcpy(movies[index].m_name,fp1);
		index++;
	}
	fclose(fp_c);

	index=0;	//重新计数 
	while(index<MAX)
	{
		for(i=0;(ch2=getc(fp_a))!='\n'&&ch2!=EOF;i++)
		{
			temp[i]=ch2;
			if(i>499)
				break;
		}	
		temp[i]='\0';	 
		fp2 = strtok(temp,",");
		strcpy(movies[index].m_id,fp2);
		fp2 = strtok(NULL,",");
		strcpy(movies[index].m_ratings,fp2);	
		index++;
	}
	fclose(fp_a);

	index=0;	//重新计数 
	while(index<MAX_MAX)
	{
		for(i=0;(ch3=getc(fp_d))!='\n'&&ch3!=EOF;i++)
		{
			temp[i]=ch3;
			if(i>499)
				break;
		}	
		temp[i]='\0';
		fp3 = strtok(temp,",");
		strcpy(users[index].u_id,fp3);
		fp3 = strtok(NULL,",");
		strcpy(users[index].u_movies_id,fp3);
		fp3 = strtok(NULL,",");
		strcpy(users[index].u_ratings,fp3);
		index++;
	}
	fclose(fp_a);
		
	printf("welcome to the Film Recommendation System(输入'q'结束程序)\n");
	printf("You can choose one of the following:\n");
	printf("%s\n%s\n%s\n%s\n",msgs[0],msgs[1],msgs[2],msgs[3]); 
	
	int alpha;	//菜单选择 
	while((alpha=getchar())!='q')
	{
		switch(alpha=tolower(alpha))
		{
			case 'a':
				function_A();   //ok 
				break;			
			case 'b':
				function_B();	//ok 
				break;
			case 'c':
				function_C();	//ok 
				break;	
			case 'd':
				function_D();   //ok
				break;	
			while(getchar()!='\n')
			continue;
		}
	getchar();
	printf("\nYou can choose one of the following:\n");
	printf("%s\n%s\n%s\n%s\n",msgs[0],msgs[1],msgs[2],msgs[3]);	
	}
	return 0;
}

void function_A()
{
	char a1[20],a2[20],movie_name;
	int u_id,m_id;
	index=0;
	printf("u_id:");
	scanf("%d",&u_id);
	printf("m_id:");
	scanf("%d",&m_id);
	sprintf(a1,"%d",u_id);
	sprintf(a2,"%d",m_id);
	
	for(index=0;index<MAX;index++)
	{
		if((strcmp(a1,users[index].u_id))==0)   //c语言中strcmp比较两个字符串的大小，两个字符串相同时返回0，第一个字符串大于第二个字符串时返回一个正值，否则返回负值。 
		{
			if((strcmp(a2,movies[index].m_id))==0)
				printf("用户 %d 对 %s 电影的评分为: %s\n",u_id,movies[index].m_name,users[index].u_ratings);
		}
	}
}

void function_B()
{
	int u_id,count;
	char b[20];
	printf("u_id:");
	scanf("%d",&u_id);
	sprintf(b,"%d",u_id);
	index=0;
	for(index=0;index<MAX_MAX;index++)
	{
		if((strcmp(b,users[index].u_id))==0)
		{
			for(count=0;count<MAX;count++)
			{
				if((strcmp(users[index].u_movies_id,movies[count].m_id))==0)
					printf("用户 %d 观看过的电影是: %s \n",u_id,movies[count].m_name);
			}
			
		}
	}	
}

void function_C()
{
	int m_id,count;
	char c[20];
	printf("m_id:");
	scanf("%d",&m_id);
	sprintf(c,"%d",m_id);
	index=0;
	for(index=0;index<MAX;index++)
	{
		if((strcmp(c,movies[index].m_id))==0)
		{
			for(count=0;count<MAX_MAX;count++)
			{
				if((strcmp(c,users[count].u_movies_id))==0)
					printf("电影 %s 被用户 %s 观看过\n",movies[index].m_name,users[count].u_id);
			}
		}
	}	
}

void function_D()
{
	int u_id,count,i=0;
	char d[20],d2[20];
	printf("u_id:");
	scanf("%d",&u_id);
	sprintf(d,"%d",u_id);
	sprintf(d2,"%d",4);
	index=0;
	for(index=0;index<MAX_MAX;index++)
	{
		if((strcmp(d,users[index].u_id))==0)
		{
			for(count=0;count<MAX;count++)
			{
				if((strcmp(users[index].u_movies_id,movies[count].m_id))==0)
				{
					if((strcmp(users[index].u_ratings,d2))>0 && i<8)
					{
						printf("为用户 %d 推荐的电影为：%s %s \n",u_id,movies[count].m_genre,movies[count].m_name);
						i++;
					}
				} 
			}
		}
	}
}
