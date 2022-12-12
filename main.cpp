#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 9125
#define MIN 550
#define MAX_MAX 80965

char ch1,ch2,ch3,*fp1,*fp2,*fp3;
FILE *fp_a, *fp_b, *fp_c, *fp_d;	
char temp[500];   //temp����ʱ����˼,��ʱ����һ������ 
int i,index=0;

struct movie{	//�û�������Ӱ����Ϣ 
	char m_id[20];	
	char m_name[500];	
	char m_ratings[20];
	char m_genre[500];	
};
struct user{	//�û�ID��Ӧ���ۿ���Ӱ������ 
	char u_id[20];	 
	char u_movies_id[20]; 
	char u_ratings[20];	
};
struct movie movies[MAX];
struct user users[MAX_MAX];

void function_A();   //ѡ����ĸ� 
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
	
	rewind(fp_a);    //rewind�ǽ��ļ��ڲ���λ��ָ������ָ��һ������������/�ļ����Ŀ�ͷ
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
		fp1 = strtok(temp,",");  //strtok�����������ǰ��ַ����Թ涨���ַ��ָ 
		strcpy(movies[index].m_id,fp1);     
		//strcpy����string copy���ַ������ƣ�����д��
//strcpy��һ��C���Եı�׼�⺯����strcpy�Ѵ�src��ַ��ʼ�Һ��С�\0�����������ַ������Ƶ���dest��ʼ�ĵ�ַ�ռ䣬����ֵ������Ϊchar*��
		fp1 = strtok(NULL,",");   
		strcpy(movies[index].m_name,fp1);
		index++;
	}
	fclose(fp_c);

	index=0;	//���¼��� 
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

	index=0;	//���¼��� 
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
		
	printf("welcome to the Film Recommendation System(����'q'��������)\n");
	printf("You can choose one of the following:\n");
	printf("%s\n%s\n%s\n%s\n",msgs[0],msgs[1],msgs[2],msgs[3]); 
	
	int alpha;	//�˵�ѡ�� 
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
		if((strcmp(a1,users[index].u_id))==0)   //c������strcmp�Ƚ������ַ����Ĵ�С�������ַ�����ͬʱ����0����һ���ַ������ڵڶ����ַ���ʱ����һ����ֵ�����򷵻ظ�ֵ�� 
		{
			if((strcmp(a2,movies[index].m_id))==0)
				printf("�û� %d �� %s ��Ӱ������Ϊ: %s\n",u_id,movies[index].m_name,users[index].u_ratings);
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
					printf("�û� %d �ۿ����ĵ�Ӱ��: %s \n",u_id,movies[count].m_name);
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
					printf("��Ӱ %s ���û� %s �ۿ���\n",movies[index].m_name,users[count].u_id);
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
						printf("Ϊ�û� %d �Ƽ��ĵ�ӰΪ��%s %s \n",u_id,movies[count].m_genre,movies[count].m_name);
						i++;
					}
				} 
			}
		}
	}
}
