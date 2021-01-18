#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dd
{
	struct dd *next;
	int value;
}graph;

void queue(int *q,int value,int *n)
{
	q[*n]=value;
	*n=*n+1;
}

void dequeue(int *max)
{
	*max=*max-1;
}

void dfs(int v,graph *g[v])
{
	char *color[v];
	for (int i = 0; i < v; ++i)
		color[i]="white";
	int max=1;
	int *q;
	q[0]=0;
	color[0]="grey";
	while(max!=0)
	{
		int b=q[max-1];
		graph *temp;
		temp=g[b];
		dequeue(&max);
		while(temp!=NULL)
		{
			if(strcmp(color[temp->value],"white")==0)
			{
				color[temp->value]="grey";
				queue(q,temp->value,&max);
			}
			temp=temp->next;
		}
		color[b]="black";
		for(int i=0;i<v;++i)
			printf("%s ",color[i]);
		printf("\n");
	}
}

void inputedges(int n,graph *list[n])
{
	char c;
	int a;
	graph *temp,*temp1;
	for(int i=0;i<n;++i)
	{
		c=' ';
		list[i]=(graph*)(malloc(sizeof(graph)));
		temp=list[i];
		while(c!='\n')
		{
			scanf("%d",&a);
			scanf("%c",&c);
			temp->value=a;
			temp->next=(graph*)malloc(sizeof(graph));
			temp1=temp;
			temp=temp->next;
		}
		temp1->next=NULL;
	}
}

int main()
{
	int v;
	scanf("%d ",&v);
	graph *g[v];
	inputedges(v,g);
	dfs(v,g);
	return 0;	 
}