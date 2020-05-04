#include <stdio.h>
#include <stdlib.h>

// 전역 변수 선언 field
int i, j, k, a, b, u, v, n, ne = 1;
int min, mincost = 0, cost[9][9], parent[9];


int find(int);
int uni(int, int);


void main()
{
	printf("\n\t Kruskal's Algorithm으로 MST 찾기! \n");
	printf("\n\t\t 2017320233김채령 \n");
	printf("\n노드의 개수를 입력하세요. (최대 9 개) : ");
	scanf("%d", &n);
	printf("\ncost adjacency matrix를 입력하세요.\n(edge가 없는 노드 사이의 cost는 0으로 입력하고, cost는 998이하로 입력하세요.) :\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &cost[i][j]); //n*n adjacency matrix에 cost를 입력받는다.
			if (cost[i][j] == 0) //cost가 없는 edge는 연결된 edge가 아니니까 매우 큰 가중치를 부여한다.
				cost[i][j] = 999;
		}
	}
	/*
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			printf(" %d ",cost[i][j]); 
	
		}
		printf("\n");
	}*/

	printf("\nMST의 edge들은 다음과 같습니다.\n");
	while (ne < n) //edge들이 n-1개 선택되도록
	{
		min = 999;
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (cost[i][j] < min) //앞서 cost가 없는 edge에 부여한 매우 큰 값은 여기서 걸러진다.
				{ //cost adjacency matrix에서 가장 적은 cost의 edge를 찾는다.
					min = cost[i][j];
					a = u = i;
					b = v = j;
				}
			}
		}
		u = find(u); //printf("find result %d\n", u);
		v = find(v); //printf("find result %d\n", v);
		if (uni(u, v))
		{// 두 개가 다른 집합의 노드들이어서 합쳐질 때
			//printf("uni result %d\n", uni(u, v));
			printf("%d edge (%d,%d) =%d\n", ne++, a, b, min);
			mincost += min;
		}
		cost[a][b] = cost[b][a] = 999;
	}
	printf("\n\tMinimum cost = %d\n", mincost);

	return;
}
int find(int i)
{
	//printf("parent of %d: %d\n", i, parent[i]);
	while (parent[i]) {
		//printf("hi\n");
		i = parent[i];
	}
	return i; 
}

int uni(int i, int j)
{
	if (i != j)
	{
		//printf("dif\n");
		parent[j] = i;
		return 1;
	}
	return 0;
}