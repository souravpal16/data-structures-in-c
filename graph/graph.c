#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

struct Edgenode
{
	int y;
	int weight;
	struct Edgenode *next;
};

struct graph
{
	int vertices, edges;
	int degree[MAXV];
	struct Edgenode* adj[MAXV];
	int directed;
};

struct graph *empty_Graph(struct graph *g, int directed)
{
	printf("Initializing Graph\n");
	printf("Initializing edge number = 0\n");
	g->edges = 0;
	printf("Initializing vertices number = 0\n");
	g->vertices = 0;
	g->directed = directed;
	for(int i = 0; i<MAXV; i++)
	{
		g->degree[i] = 0;
	}
	for(int i = 0; i<MAXV; i++)
	{
		g->adj[i] = NULL;
	}
	printf("Graph Initializing done\n");
	return g;
}

void insert_edge(struct graph *g, int x, int y, int directed)
{
	struct Edgenode *p = (struct Edgenode*)malloc(sizeof(struct Edgenode));
	p->weight = 0;
	p->y = y;
	p->next = g->adj[x];
	g->adj[x] = p;
	g->degree[x]++;
	if(directed == 0)
	{
		insert_edge(g, y, x, 1);
	}
}

struct graph *read_Graph(struct graph *g, int directed)
{
	g = empty_Graph(g, directed);
	printf("Graph reading begins\n");
	scanf("%d", &(g->vertices));
	scanf("%d", &(g->edges));
	for(int i = 0; i<g->edges; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		insert_edge(g, x, y, directed);
	}
	return g;
}

void print_Graph(struct graph *g)
{
	for(int i = 0; i<g->vertices; i++)
	{
		struct Edgenode *p = g->adj[i];
		printf("%d: ", i);
		while(p!=NULL)
		{
			printf("%d, ", p->y);
			p = p->next;
		}
		printf("\n");
	}	
}

int main()
{
	struct graph *g = (struct graph*)malloc(sizeof(struct graph));
	int directed = 0;
	printf("Program begins\n");
	g = read_Graph(g, directed);
	print_Graph(g);
	free(g);
}