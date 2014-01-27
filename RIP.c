#include<stdio.h>
#include<string.h>
int r1,r2;
int own_blot=-7;
int enemy_blot=200;
int inner_points=40;
int holding=200;
int save_blot=100;
int home_base=10;
char name[100];
int valid(int a[],int ini,int fin)
{
	if(a[fin]>=-1 && fin<=24 && a[ini]>0)
		return 1;
	return 0;
}
typedef struct node{
	int initial;
	int final;
}node;
void moves(int a[]);
void final_print(node,node);
int main()
{
	int i;
	scanf("%s",name);
	int a[100]={0};
	if(strcmp(name,"Alice")==0)
	{
		for(i=13;i<=24;i++)
			scanf("%d",&a[i]);
		for(i=12;i>0;i--)
			scanf("%d",&a[i]);
	}
	else if(strcmp(name,"Bob")==0)
	{
		for(i=12;i>0;i--)
			scanf("%d",&a[i]);
		for(i=13;i<=24;i++)
			scanf("%d",&a[i]);
		for(i=0;i<=24;i++)
			a[i]=-a[i];
	}
	scanf("%d%d",&r1,&r2);
	scanf("%d",&a[0]);
	moves(a);
	return 0;
}
void moves(int a[])
{
	int utility=0,max_utility=-1000000000,j,k,b[100]={0},i;
	node move1;
	node move2;
	move1.initial=-1;
	move1.final=-1;
	move2.initial=-1;
	move2.final=-1;
	if(a[0]==0) 
	{
		for(i=1;i<=24;i++)
		{
			if(valid(a,i,i+r1))
			{
				for(k=0;k<=24;k++)
					b[k]=a[k];
				b[i]--;
				b[i+r1]++;
				for(j=1;j<=24;j++)
				{
					if(valid(b,j,r2+j))
					{
						utility=eval(a,i,j);
						if(utility>max_utility)
						{
							max_utility=utility;
							move1.initial=i;
							move1.final=i+r1;
							move2.initial=j;
							move2.final=j+r2;
						}
					}
				}
			}
		}
		for(i=1;i<=24;i++)
		{
			if(valid(a,i,i+r2))
			{
				//		b[100]={0};
				for(k=0;k<=24;k++)
					b[k]=a[k];
				b[i]--;
				b[i+r2]++;
				for(j=1;j<=24;j++)
				{
					if(valid(b,j,r1+j))
					{
						utility=eval(a,j,i);
						if(utility>max_utility)
						{
							max_utility=utility;
							move1.initial=i;
							move1.final=i+r2;
							move2.initial=j;
							move2.final=j+r1;
						}
					}
				}
			}
		}
	}
	else if(a[0]==1)
	{
		if(valid(a,0,r1))
		{
			for(k=0;k<=24;k++)
				b[k]=a[k];
			b[0]--;
			b[r1]++;
			for(i=1;i<=24;i++)
			{
				if(valid(b,i,r2+i))
				{
					utility=eval(a,0,i);
					if(utility>max_utility)
					{
						max_utility=utility;
						move1.initial=0;
						move1.final=r1;
						move2.initial=i;
						move2.final=i+r2;
					}
				}
			}
		}
		if(valid(a,0,r2))
		{
			for(k=0;k<=24;k++)
				b[k]=a[k];
			b[0]--;
			b[r1]++;
			for(i=1;i<=24;i++)
			{
				if(valid(b,i,r1+i))
				{
					utility=eval(a,i,0);
					if(utility>max_utility)
					{
						max_utility=utility;
						move1.initial=0;
						move1.final=r2;
						move2.initial=i;
						move2.final=i+r1;
					}
				}
			}
		}
	}
	else if(a[0]==2)
	{
		if(valid(a,0,r1))
		{
			move1.initial=0;
			move1.final=r1;
		}
		if(valid(a,0,r2))
		{
			move2.initial=0;
			move2.final=r2;
		}
	}
//	printf("%d->%d\n",move1.initial,move1.final);
//	printf("%d->%d\n",move2.initial,move2.final);
//	printf("%d\n",max_utility);
	final_print(move1,move2);
}
int eval(int b[],int f1,int f2)
{
	int utility=0,a[100];
	int i;
	for(i=1;i<=24;i++)
		a[i]=b[i];
	if(f1+r1!=f2)
	{
		if(a[f1+r1]==-1 && a[0]<0)
		{
			a[0]--;
			utility+=enemy_blot+7*(24-f1-r1);
			printf("1enemy_blot ");
		}
		if(f1+r1==7 ||f1+r1==5 || f1+r1==6)
		{
			utility+=holding;
			printf("holding ");
		}
		if(a[f1+r1]==1)
		{
			utility+=save_blot;
			printf("save_blot ");
		}
		if(f1+r1<5)
		{
			utility+=inner_points*(f1+r1);
		}
		if(a[f1+r1]==0 && a[f1]!=1)
		{
			utility+=own_blot*(f1+r1);
			printf("own_blot ");
		}
		if(f1+r1>18)
		{
			utility+=home_base;
			printf("home_base ");
		}
		utility+=r1;
		a[f1]--;
		a[f1+r1]++;
		if(a[f1]==1)
		{
			utility+=own_blot*(f1);
			printf("own_blot ");
		}
		if(a[f2+r2]==-1 && a[0]<0)
		{
			utility+=enemy_blot+7*(24-f2-r2);
			printf("2enemy_blot ");
			a[0]--;
		}
		if(f2+r2==7 ||f2+r2==5 || f2+r2==6)
		{
			utility+=holding;
			printf("holding ");
		}
		if(f1+r1<5)
		{
			utility+=inner_points*(f1+r1);
		}
		if(a[f2+r2]==1)
		{
			utility+=save_blot;
			printf("save_blot ");
		}
		if(a[f2+r2]==0 && a[f2]!=1)
		{
			utility+=own_blot*(f2+r2);
			printf("own_blot ");
		} 
		if(f2+r2>18)
		{
			utility+=home_base;
			printf("home_base ");
		}
		printf("\n");
		utility+=r2;
		a[f2]--;
		a[f2+r2]++;
	}
	else
	{
		if(a[f1+r1+r2]==-1 && a[0]<0)
		{
			utility+=enemy_blot+7*(24-f1-r1-r2);
			printf("enemy_blot ");
			a[0]--;
		}
		if(f1+r1+r2==7 ||f1+r1+r2==5 || f1+r2+r1==6)
		{
			utility+=holding;
			printf("holding ");
		}
		if(a[f1+r1+r2]==1)
		{
			utility+=save_blot;
			printf("save_blot ");
		}
		if(f1+r1+r2<5)
		{
			utility+=inner_points*(f1+r1);
		}
		if(a[f1+r1+r2]==0)
		{
			utility+=own_blot*(f1+r1+r2);
			printf("own_blot ");
		}
		if(f1+r2+r1>18)
		{
			utility+=home_base;
			printf("home_base ");
		}
		utility+=r1+r2;
		a[f1]--;
		a[f1+r1+r2]++;
	}
	return utility;
}
void final_print(node move1,node move2)
{
	if(strcmp(name,"Alice")==0)
	{
		if(move1.initial>12)
			printf("A%d ",move1.initial-12);
		else if(move1.initial<=12 && move1.initial>0)
		{
			if(move1.initial==0)
			{
				move1.initial=13;
			}
			printf("B%d ",13-move1.initial);
		}
		else 
			printf("pass\n");
		if(move1.final>12)
			printf("A%d\n",move1.final-12);
		else if(move1.final<=12 && move1.final>0)
			printf("B%d\n",13-move1.final);
		else 
			printf("pass\n");

		if(move2.initial>12)
			printf("A%d ",move2.initial-12);
		else if(move2.initial<=12 && move2.initial>0)
		{
			if(move2.initial==0)
			{
				move2.initial=13;
			}
			printf("B%d ",13-move2.initial);
		}
		else 
			printf("pass\n");
		if(move2.final>12)
			printf("A%d\n",move2.final-12);
		else if(move2.final<=12 && move2.final>0)
			printf("B%d\n",13-move2.final);
		else 
			printf("pass\n");
	}
	else if(strcmp(name,"Bob")==0)
	{
		if(move1.initial<=12 && move1.initial>0)
		{
			if(move1.initial==0)
			{
				move1.initial=13;
			}
			printf("A%d ",13-move1.initial);
		}
		else if(move1.initial>12)
			printf("B%d ",move1.initial-12);
		else 
			printf("pass\n");
		if(move1.final<=12 && move1.final>0)
		{
			printf("A%d\n",13-move1.final);
		}
		else if(move1.final>12)
			printf("B%d\n",move1.final-12);
		else 
			printf("pass\n");

		if(move2.initial<=12 && move2.initial>0)
		{
			if(move2.initial==0)
			{
				move2.initial=13;
			}
			printf("A%d ",13-move2.initial);
		}
		else if(move2.initial>12)
			printf("B%d ",move2.initial-12);
		else 
			printf("pass\n");
		if(move2.final<=12 && move2.final>0)
		{
			printf("A%d\n",13-move2.final);
		}
		else if(move2.final>12)
			printf("B%d\n",move2.final-12);
		else 
			printf("pass\n");
	}
}
