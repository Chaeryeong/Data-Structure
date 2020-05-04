#include <stdio.h>
#include <stdlib.h>

// ���� ���� ���� field
int i, j, k, a, b, u, v, n, ne = 1;
int min, mincost = 0, cost[9][9], parent[9];


int find(int);
int uni(int, int);


void main()
{
	printf("\n\t Kruskal's Algorithm���� MST ã��! \n");
	printf("\n\t\t 2017320233��ä�� \n");
	printf("\n����� ������ �Է��ϼ���. (�ִ� 9 ��) : ");
	scanf("%d", &n);
	printf("\ncost adjacency matrix�� �Է��ϼ���.\n(edge�� ���� ��� ������ cost�� 0���� �Է��ϰ�, cost�� 998���Ϸ� �Է��ϼ���.) :\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &cost[i][j]); //n*n adjacency matrix�� cost�� �Է¹޴´�.
			if (cost[i][j] == 0) //cost�� ���� edge�� ����� edge�� �ƴϴϱ� �ſ� ū ����ġ�� �ο��Ѵ�.
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

	printf("\nMST�� edge���� ������ �����ϴ�.\n");
	while (ne < n) //edge���� n-1�� ���õǵ���
	{
		min = 999;
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (cost[i][j] < min) //�ռ� cost�� ���� edge�� �ο��� �ſ� ū ���� ���⼭ �ɷ�����.
				{ //cost adjacency matrix���� ���� ���� cost�� edge�� ã�´�.
					min = cost[i][j];
					a = u = i;
					b = v = j;
				}
			}
		}
		u = find(u); //printf("find result %d\n", u);
		v = find(v); //printf("find result %d\n", v);
		if (uni(u, v))
		{// �� ���� �ٸ� ������ �����̾ ������ ��
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