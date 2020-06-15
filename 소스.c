#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define INT_MAX 2147483647
#define INF 1000	
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES];   //시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES];   //방문한 정점 표시
char location[MAX_VERTICES][MAX_VERTICES];
int check[MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];


typedef struct GraphType
{
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

GraphType g;

void graph_init(GraphType *g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = INT_MAX;
		}
	}
}

void insert_vertex(GraphType *g) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프:정점의 개수 초과");
		return;
	}

	g->n++;
}


void insert_edge(GraphType *g, int start, int end, int weight)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	g->adj_mat[start][end] = weight;

}


int choose(int distance[], int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < g.n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortest_check(GraphType *g, int start) {
	int i, u, w;

	for (int i = 0; i < g->n; i++)
		for (int j = 0; j < g->n; j++)
			path[i][j] = INF;


	for (i = 0; i < g->n; i++) {
		distance[i] = g->adj_mat[start][i];
		found[i] = FALSE;
		check[i] = 2;
		path[i][0] = start;
		path[i][1] = i;

	}
	found[start] = TRUE;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, found);
		found[u] = TRUE;

		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[w] > distance[u] + g->adj_mat[u][w] && distance[u] + g->adj_mat[u][w] > 0) {
					distance[w] = distance[u] + g->adj_mat[u][w];
					for (int j = 0; j < (check[u] + 1); j++) {
						path[w][j] = path[u][j];
						path[w][j + 1] = w;
						check[w]++;
					}
				}

			}
		}
	}
}



int main() {

	int n, e;
	int v1, v2, weight;
	int i;


	graph_init(&g);

	printf("정점의 수 입력) ");
	scanf("%d", &n);
	printf("\n");

	printf("[%d만큼 각 정점의 이름 입력]\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d)", i);
		scanf("%s", &location[i]);
		insert_vertex(&g);
	}
	printf("\n");
	printf("간선의 수 입력) ");
	scanf("%d", &e);
	printf("[%d만큼 출발 정점, 도착 정점, 가중치 입력]\n", e);
	for (int i = 0; i < e; i++) {
		printf("%d)", i);
		scanf("%d %d %d", &v1, &v2, &weight);
		insert_edge(&g, v1, v2, weight);
	}
	printf("\n");

	shortest_check(&g, 0);

	printf("[최소비용] [최소 경로]\n");
	for (i = 1; i < g.n; i++) {
		printf("[%5d   ] ", distance[i]);
		for (int j = 0; j < g.n; j++) {

			if (path[i][j] != INF) {

				printf("%s", location[path[i][j]]); //저장된 경로를 출력

			}
			if (path[i][j + 1] == INF || j + 1 >= g.n) continue;
			else printf("-");

		}

		printf("\n");
	}

}
