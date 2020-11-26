#include<stdio.h>
#include<stdlib.h>
#define MAXV 100

struct queue
{
	int a[MAXV];
	int front, rear;
};

void enqueue(struct queue *q, int x)
{
	q->a[q->rear] = x;
	q->rear = q->rear + 1;
}

int dequeue(struct queue *q)
{
	int x = q->a[q->front];
	q->front = q->front + 1;
	return x;
}

struct adjNode
{
	int y;
	int weight;
	struct adjNode *next;
};

