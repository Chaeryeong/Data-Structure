/* ���Ḯ��Ʈ�� ������ �����ϱ� ���α׷� ���� */
/*
-task 
user friendly menu driven program!
add
mult
transpose

-given
read
write
erase
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/* ��� ��� ǥ�� ���Ḯ��Ʈ�� �ϱ� 

        head             &               entry              - node with tag field
  ---------------                -------------------
 |      next     |              | row | col | value |
 ----------------                -------------------
 | down |  right |              |   down  |  right  |
  ---------------                -------------------

*/
typedef enum tagfield { head, entry } tagfield;
typedef struct mnode *matrixPointer; 
typedef struct enode {
	int row;
	int col;
	int value;
}enode;
typedef struct mnode {
	matrixPointer down;
	matrixPointer right;
	enum tagfield tag;
	union
	{
		matrixPointer next;
		enode entry;
	} u;
}mnode;
/* ���� ��� ��Ŀ� ���� */
typedef struct re
{
	int row;
	int col;
	int val;
}re;
matrixPointer hdnode[MAX_SIZE];


/* �Լ� ����Ʈ */
matrixPointer mread(void);
matrixPointer xmread(int ncol, int nrow, int nterm, re *rehdnode); 
void mwrite(matrixPointer);
void merase(matrixPointer*);
matrixPointer madd(matrixPointer, matrixPointer);
matrixPointer mmult(matrixPointer, matrixPointer);
matrixPointer mtranspose(matrixPointer);
matrixPointer newNode(void);

void main() {
	/* �޴� �� ����, ��� �Լ� ȣ�� */
	int menu1, menu2, menu3;
	matrixPointer op1, op2, result;

	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("|                              ��� ��� �����ϱ�!                                 |\n");
	printf("|                                                                                  |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                   2019 ���б� �ڷᱸ�� 2�� ����  |\n");
	printf("|                                                    2017320233 ��ǻ���а� ��ä��  |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("+------------------------------------  �޴�  --------------------------------------+\n");
	printf("|      [1] ��� ��� �Է��ϱ�                       [2] ������                     |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("\n=>�޴����� ���ϴ� ��������� �������ּ��� (1 �Ǵ� 2�� �Է����ּ���) ===>   ");
	scanf("%d", &menu1);
	switch(menu1){
	 case 1:
		 printf("\n**��� ��� �Է��ϱ⸦ �����ϼ̽��ϴ�**\n");
		 op1 = mread();
		 mwrite(op1);
		 break;
	 case 2:
		 printf("\n**��� ��� �����ϱ� ���α׷��� �����ϴ�. BYE BYE~**\n\n");
		 return 0;
		 break;
	 default:
		 printf("\n**���� �޴��� �����ϼ̽��ϴ�. ���α׷��� �����մϴ�.**\n\n");
		 return 0;
}
printf("\n");
printf("+--------------------------------- �ι�° �޴�  -----------------------------------+\n");
printf("| [1] �ι�° ��� ��� �Է�(����, ����)  [2] �Էµ� ��� Transpose�ϱ�  [3] ������ |\n");
printf("+----------------------------------------------------------------------------------+\n");
printf("\n=>�ι�°�޴����� ���ϴ� ��������� �������ּ��� (1 �Ǵ� 2 �Ǵ� 3���� �Է����ּ���) ===>   ");
scanf("%d", &menu2);
switch (menu2) {
case 1:
	printf("\n**�ι�° ��� ��� �Է��ϱ⸦ �����ϼ̽��ϴ�**\n");
	op2 = mread();
	mwrite(op2);
	break;
case 2:
	printf("\n**�Էµ� ��� Transpose�ϱ⸦ �����ϼ̽��ϴ�**\n");
	result = mtranspose(op1);
	mwrite(result);
	merase(&op1);
	merase(&result);
	printf("\n**��� ��� ������ ����Ǿ����ϴ�. BYE BYE~**\n\n");
	return 0;
	break;
case 3:
	printf("\n**��� ��� �����ϱ� ���α׷��� �����ϴ�. BYE BYE~**\n\n");
	return 0;
	break;
default:
	printf("\n**���� �޴��� �����ϼ̽��ϴ�. ���α׷��� �����մϴ�.**\n\n");
	return 0;
}
printf("\n");
printf("+--------------------------------- ����° �޴�  -----------------------------------+\n");
printf("|   [1] �� ��� ���� ����            [2] �� ��� ���� ����            [3] ������   |\n");
printf("+----------------------------------------------------------------------------------+\n");
printf("\n=>����°�޴����� ���ϴ� ��������� �������ּ��� (1 �Ǵ� 2 �Ǵ� 3���� �Է����ּ���) ===>   ");
scanf("%d", &menu3);
switch (menu3) {
case 1:
	printf("\n**�� ��� ���� �����ϱ⸦ �����ϼ̽��ϴ�**\n");
	result = madd(op1, op2);
	mwrite(result);
	merase(&op1);
	merase(&op2);
	merase(&result);
	printf("\n**��� ��� ������ ����Ǿ����ϴ�. BYE BYE~**\n\n");
	return 0;
	break;
case 2:
	printf("\n**�� ��� ���� �����ϱ⸦ �����ϼ̽��ϴ�**\n");
	result = mmult(op1, op2);
	mwrite(result);
	merase(&op1);
	merase(&op2);
	merase(&result);
	printf("\n**��� ��� ������ ����Ǿ����ϴ�. BYE BYE~**\n\n");
	return 0;
	break;
case 3:
	printf("\n**��� ��� �����ϱ� ���α׷��� �����ϴ�. BYE BYE~**\n\n");
	return 0;
	break;
default:
	printf("\n**���� �޴��� �����ϼ̽��ϴ�. ���α׷��� �����մϴ�.**\n\n");
	return 0;
}

}


	
matrixPointer mread(void)
{ /* ������ �Է¹޾� �����ϱ� */

	int numRow, numCol, numTerm, numHead, i, row, col, value, currentRow = 0;

	matrixPointer temp, last, node;

	printf("\n����� ���� ����, ���� ����, 0�� �ƴ� entry�� ������ �Է��ϼ���.\n�Է��� ������ �����ڷ� ������ ���ּ���.(�Է¿���: 2 4 2)==> ");

	scanf("%d %d %d", &numRow, &numCol, &numTerm);

	numHead = (numCol > numRow) ? numCol : numRow;//������� ������ ��, �� �� ���� �ɷ�
	node = newNode();
	node->tag = entry;
	node->u.entry.row = numRow;
	node->u.entry.col = numCol;

	if (!numHead)
		node->right = node;
	else {
		for (i = 0; i < numHead; i++) {
			/* hdnode�� �ʱ�ȭ */
			temp = newNode();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];

		printf("\n�� �� ���� ������� ������ �����ڷ� �Է����ּ���. \n");
		for (i = 0; i < numTerm; i++)
		{
			printf("%d��° ������ �� �� ��==> ", (i+1));
			scanf("%d %d %d", &row, &col, &value);
			if (row > currentRow) {    
				/* ������ �Է¹��� �� ������ ���� �Է¹��� �� ���� Ŭ �� */
				last->right = hdnode[currentRow]; 
				currentRow = row;     
				last = hdnode[row];   
			}

			temp = newNode();    
			temp->tag = entry;  
			temp->u.entry.col = col;  
			temp->u.entry.row = row;
			temp->u.entry.value = value;
			last->right = temp;   
			last = temp;

			hdnode[col]->u.next->down = temp; 
			hdnode[col]->u.next = temp;
		}

		last->right = hdnode[currentRow];   
		for (i = 0; i < numCol; i++)     
			hdnode[i]->u.next->down = hdnode[i];

		for (i = 0; i < numHead - 1; i++)   
			hdnode[i]->u.next = hdnode[i + 1];

		hdnode[numHead - 1]->u.next = node; 
		node->right = hdnode[0];  
	}
	return node;
}

void mwrite(matrixPointer node)
{
	/* ��� ��� */
	int i;
	matrixPointer temp, head = node->right;

	printf(" \n ���� ������ %d, ���� ������ %d \n", node->u.entry.row, node->u.entry.col);
	printf(" ��, ��, ������ ����մϴ�! \n\n");
	for (i = 0; i < node->u.entry.row; i++) { 
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	}
}

void merase(matrixPointer *node) {
	/* ���� �� ��� �޸� ��ȯ */
	matrixPointer x, y, head = (*node)->right;
	int i;
	for (i = 0; i < (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head)
		{
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}
	y = head;
	while (y != *node)
	{
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*node);
	*node = NULL;
}

matrixPointer madd(matrixPointer nodea, matrixPointer nodeb)
{
	/* ��� ���� */
	int i, n = 0, j, no = 0;
	int numRow = 0, numCol = 0, numTerm = 0;
	int numHead, row, col, value, currentRow;
	matrixPointer temp, head1 = nodea->right, nodec;
	re rehdnode[MAX_SIZE];  

	for (i = 0; i < nodea->u.entry.row; i++) {
		for (temp = head1->right; temp != head1; temp = temp->right) { 
			/* �� �࿡�� 0�� �ƴ� ���� ã�� */
			rehdnode[n].row = temp->u.entry.row;
			rehdnode[n].col = temp->u.entry.col;
			rehdnode[n].val = temp->u.entry.value;
			n++;
		}
		head1 = head1->u.next; 
	}

	head1 = nodeb->right; 

	for (i = 0; i < nodeb->u.entry.row; i++) {
		no = 0;
		for (temp = head1->right; temp != head1; temp = temp->right) {
			for (j = 0; j < n; j++) {
				/* ��� ���� ���� ���Ұ� ������ ���� �ǽ� */
				if ((rehdnode[j].row == temp->u.entry.row) && (rehdnode[j].col == temp->u.entry.col)) { 
					no++;
					rehdnode[j].val += temp->u.entry.value; 
				}
			}
			if (no == 0) { 
				/* ��� ���� ���� ���Ұ� ���� �� */
				rehdnode[n].row = temp->u.entry.row;
				rehdnode[n].col = temp->u.entry.col;
				rehdnode[n].val = temp->u.entry.value;
				n++;
			}
		}
		head1 = head1->u.next; 
	}

	for (i = 0; i < n; i++) {
		if (rehdnode[i].val) { 
			/* 0�� �ƴ� ������ ���� */
			if (numRow <= rehdnode[i].row)
				numRow = rehdnode[i].row + 1;
			if (numCol <= rehdnode[i].col)
				numCol = rehdnode[i].col + 1;
			numTerm++;
		}
	}
	return xmread(numCol, numRow, numTerm, rehdnode); 
}

matrixPointer mmult(matrixPointer nodea, matrixPointer nodeb) {
	/* ��� ���� */
	int i, n1 = 0, n2 = 0, j, k, no = 0;
	int numRow = 0, numCol = 0, numTerm = 0;
	int row, col, value, crow = 0;
	matrixPointer temp, heads = nodea->right, nodec;
	re rehdnode[MAX_SIZE];
	re copy[MAX_SIZE];

	for (i = 0; i < nodea->u.entry.row; i++) {
		/* �� �࿡�� 0�� �ƴ� ���� ã�� ���� */
		for (temp = heads->right; temp != heads; temp = temp->right) {
			copy[n1].row = temp->u.entry.row;
			copy[n1].col = temp->u.entry.col;
			copy[n1].val = temp->u.entry.value;
			n1++;
		}
		heads = heads->u.next; 
	}

	heads = nodeb->right; 
	for (i = 0; i < nodeb->u.entry.row; i++) {
		for (temp = heads->right; temp != heads; temp = temp->right) {
			for (j = 0; j < n1; j++) {
				no = 1;
				if ((copy[j].col == temp->u.entry.row) && (copy[j].val * temp->u.entry.value)) {
					for (k = 0; k < n2; k++) {
						if ((rehdnode[k].row == copy[j].row) && (rehdnode[k].col == temp->u.entry.col)) {
							rehdnode[k].val += copy[j].val * temp->u.entry.value;
							no = 0;
						}
					}
					if (no) {
						rehdnode[n2].row = copy[j].row;
						rehdnode[n2].col = copy[j].col;
						rehdnode[n2].val = copy[j].val * temp->u.entry.value;
						n2++;
					}
				}
			}
		}
		heads = heads->u.next;
	}

	for (i = 0; i < n2; i++) {
		if (rehdnode[i].val) {
			if (numRow <= rehdnode[i].row) numRow = rehdnode[i].row + 1;
			if (numCol <= rehdnode[i].col) numCol = rehdnode[i].col + 1;
			numTerm++;
		}
	}

	return xmread(nodeb->u.entry.col, nodea->u.entry.row, numTerm, rehdnode);
} 


matrixPointer mtranspose(matrixPointer node) {
	/* ��� ��ġ */
	int i, n = 0;
	int numRow = 0, numCol = 0, numTerm = 0;
	int row, col, value, currentRow;
	matrixPointer temp, heads = node->right, nodec;
	re rehdnode[MAX_SIZE];

	for (i = 0; i < node->u.entry.row; i++) {
		for (temp = heads->right; temp != heads; temp = temp->right) {
			rehdnode[n].row = temp->u.entry.col;
			rehdnode[n].col = temp->u.entry.row;
			rehdnode[n].val = temp->u.entry.value;
			n++;
		}
		heads = heads->u.next;
	}

	for (i = 0; i < n; i++) {
		if (rehdnode[i].val) {
			if (numRow <= rehdnode[i].row) numRow = rehdnode[i].row + 1;
			if (numCol <= rehdnode[i].col) numCol = rehdnode[i].col + 1;
			numTerm++;
		}
	}

	return xmread(node->u.entry.row, node->u.entry.col, numTerm, rehdnode);
} 


matrixPointer newNode() {
	/* ���ο� ��� �޸� �Ҵ� */
	matrixPointer node;
	node = (matrixPointer)malloc(sizeof(*node));
	return node;
}

matrixPointer xmread(int ncol, int nrow, int nterm, re *rehdnode) {
	/* ��� ��� */
	int numHead, j = 0, i, currentRow, row, col, value;
	matrixPointer nodec, temp, head1;

	numHead = (ncol > nrow) ? ncol : nrow;
	nodec = newNode();
	nodec->tag = entry;
	nodec->u.entry.row = nrow;
	nodec->u.entry.col = ncol;

	if (!numHead) nodec->right = nodec;
	else {
		for (i = 0; i < numHead; i++) {
			temp = newNode();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		head1 = hdnode[0];
		for (i = 0; i < nterm; i++) {
			if (rehdnode[j].val) {
				row = rehdnode[j].row;
				col = rehdnode[j].col;
				value = rehdnode[j].val;
				j++;
			}
			if (row > currentRow) {
				head1->right = hdnode[currentRow];
				currentRow = row;
				head1 = hdnode[row];
			}
			temp = newNode();
			temp->tag = entry;
			temp->u.entry.col = col;
			temp->u.entry.row = row;
			temp->u.entry.value = value;
			head1->right = temp;
			head1 = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		head1->right = hdnode[currentRow];
		for (i = 0; i < ncol; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHead - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHead - 1]->u.next = nodec;
		nodec->right = hdnode[0];
	}

	return nodec;
}

/* the end ! */



