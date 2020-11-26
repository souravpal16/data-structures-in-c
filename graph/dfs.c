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

void dfs_visit(struct graph *g, int u, int *time, char *color[], int p[], int start[], int end[])
{
	*time = *time + 1;
	start[u] = *time;
	color[u] = "gray";
	struct adjNode *x = g->adj[u];
	while(x!=NULL)
	{
		if(color[x->y] == "white")
		{
			p[x->y] = u;
			dfs_visit(g, x->y, time, color, p, start, end);
		}
		x = x->next;
	}
	color[u] = "black";
	*time = *time + 1;
	end[u] = *time;
}

void dfs(struct graph *g)
{
	int v = g->vertices;
	char *color[v];
	int p[v];
	int time = 0;
	int start[v];
	int end[v];
	for(int i=0; i<v; i++)
	{
		color[i] = "white";
		p[i] = -1;
		start[i] = 0;
		end[i] = 0;
	}
	for(int i=0; i<v; i++)
	{
		if(color[i] == "white")
		{
			dfs_visit(g, i, &time, color, p, start, end);
		}
	}
	for(int i=0; i<v; i++)
	{
		printf("%d: %d %d\n", i, start[i], end[i]);
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
	dfs(g);
}



