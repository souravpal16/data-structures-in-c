#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

class adjNode
{
public:
	int y;
	int weight;
	adjNode *next;
	adjNode(){}
	adjNode(int y, int weight)
	{
		this->weight = weight;
		this->y = y;
		this->next = NULL;
	}
};

class graph
{
public:
	bool directed;
	int vertices;
	int edges;
	adjNode** adj;
	graph(){}
	graph(int vertices, int edges, bool directed)
	{
		this->vertices = vertices;
		this->edges = edges;
		this->directed = directed;
		this->adj = new adjNode*[this->vertices];
		for(int i=0; i<this->vertices; i++)
		{
			this->adj[i] = NULL;
		}
	}
};

graph* insert_edge(graph* g, int x, int y, bool directed)
{
	adjNode *node = new adjNode(y, 0);
	node->next = g->adj[x];
	g->adj[x] = node;
	if(directed == false)
	{
		g = insert_edge(g, y, x, true);
	}
	return g;
}

graph* read_graph(graph* g)
{
	for(int i=0;i < g->edges; i++)
	{
		cout<<"Enter start and end vertex: ";
		int x, y;
		cin>>x>>y;
		g = insert_edge(g, x, y, g->directed);
	}
	return g;
}

void dfs_visit(graph* g, int u, int &time, string color[], int p[], int start[], int end[])
{
	time = time + 1;
	start[u] = time;
	color[u] = "gray";
	adjNode *x = g->adj[u];
	while(x!=NULL)
	{
		if(color[x->y]=="white")
		{
			p[x->y] = u;
			dfs_visit(g, x->y, time, color, p, start, end);
		}
		x = x->next;
	}
	color[u] = "black";
	time = time + 1;
	end[u] = time;	
}

void dfs(graph *g)
{
	int v = g->vertices;
	string color[v];
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
	for(int i = 0; i<v; i++)
	{
		if(color[i]=="white")
		{
			dfs_visit(g, i, time, color, p, start, end);
		}
	}
	for(int i=0; i<v; i++)
	{
		cout<<i<<": "<<start[i]<<" "<<end[i]<<endl;
	}
}
void print_graph(graph *g)
{
	for(int i=0; i<g->vertices; i++)
	{
		cout<<i<<": ";
		adjNode* head = g->adj[i];
		while(head!=NULL)
		{
			cout<<head->y<<" ";
			head = head->next;
		}
		cout<<"\n";
	}
}

int main()
{
	int vertices, edges;
	cout<<"Enter number of vertices: ";
	cin>>vertices;
	cout<<"Enter number of edges: ";
	cin>>edges;
	graph *g = new graph(vertices, edges, false);
	g = read_graph(g);
	print_graph(g);
	dfs(g);
}