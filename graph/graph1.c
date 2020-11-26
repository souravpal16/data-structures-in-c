#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

struct adjNode
{
	int y;
	int weight;
	struct adjNode *next;
};

struct graph
{
	int directed;
	int vertices, edges;
	struct adjNode **adj;
};

void add_edge(struct graph *g, int x, int y, int directed)
{
	struct adjNode *p = (struct adjNode*)malloc(sizeof(struct adjNode));
	p->weight = 0;
	p->y = y;
	p->next = g->adj[x];
	g->adj[x] = p;
	if(directed == 0)
	{
		add_edge(g, y, x, 1);
	}
}

struct graph* read_graph(struct graph* g)
{
	for(int i=0; i<g->edges; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(g, x, y, g->directed);
	}
	return g;
}

void print_graph(struct graph *g)
{
	for(int i=0; i<g->vertices;i++)
	{
		struct adjNode *p = g->adj[i];
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
	int vertices;
	int edges;
	int directed = 0;
	scanf("%d%d", &vertices, &edges);
	struct graph* g = (struct graph*)malloc(sizeof(struct graph));
	g->vertices = vertices;
	g->edges = edges;
	g->directed = directed;
	g->adj = (struct adjNode **)malloc(vertices*sizeof(struct adjNode*));
	for(int i=0; i<vertices; i++)
	{
		g->adj[i] = NULL;
	}
	g = read_graph(g);
	print_graph(g);
}