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

void bfs(graph* g, int s)
{
	queue<int>q;
	int v = g->vertices;
	string color[v];
	int d[v];
	int p[v];
	for(int i=0; i<v; i++)
	{
		p[i] = -1;
		d[i] = -1;
		color[i] = "white";
	}
	color[s] = "gray";
	d[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		adjNode* x = g->adj[u];
		while(x!=NULL)
		{
			if(color[x->y]=="white")
			{
				color[x->y] = "gray";
				d[x->y] = d[u]+1;
				p[x->y] = u;
				q.push(x->y);
			}
			x = x->next;
		}
		color[u] = "black";
	}
	for(int i=0; i<v; i++)
	{
		cout<<i<<": "<<d[i]<<endl;
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
	bfs(g, 0);
}