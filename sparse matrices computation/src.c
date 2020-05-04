/* 연결리스트로 희소행렬 연산하기 프로그램 구현 */
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

/* 희소 행렬 표현 연결리스트로 하기 

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
/* 연산 결과 행렬용 구조 */
typedef struct re
{
	int row;
	int col;
	int val;
}re;
matrixPointer hdnode[MAX_SIZE];


/* 함수 리스트 */
matrixPointer mread(void);
matrixPointer xmread(int ncol, int nrow, int nterm, re *rehdnode); 
void mwrite(matrixPointer);
void merase(matrixPointer*);
matrixPointer madd(matrixPointer, matrixPointer);
matrixPointer mmult(matrixPointer, matrixPointer);
matrixPointer mtranspose(matrixPointer);
matrixPointer newNode(void);

void main() {
	/* 메뉴 및 연산, 출력 함수 호출 */
	int menu1, menu2, menu3;
	matrixPointer op1, op2, result;

	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("|                              희소 행렬 연산하기!                                 |\n");
	printf("|                                                                                  |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                   2019 봄학기 자료구조 2차 과제  |\n");
	printf("|                                                    2017320233 컴퓨터학과 김채령  |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("|                                                                                  |\n");
	printf("+------------------------------------  메뉴  --------------------------------------+\n");
	printf("|      [1] 희소 행렬 입력하기                       [2] 끝내기                     |\n");
	printf("+----------------------------------------------------------------------------------+\n");
	printf("\n=>메뉴에서 원하는 실행사항을 선택해주세요 (1 또는 2로 입력해주세요) ===>   ");
	scanf("%d", &menu1);
	switch(menu1){
	 case 1:
		 printf("\n**희소 행렬 입력하기를 선택하셨습니다**\n");
		 op1 = mread();
		 mwrite(op1);
		 break;
	 case 2:
		 printf("\n**희소 행렬 연산하기 프로그램을 끝냅니다. BYE BYE~**\n\n");
		 return 0;
		 break;
	 default:
		 printf("\n**없는 메뉴를 선택하셨습니다. 프로그램을 종료합니다.**\n\n");
		 return 0;
}
printf("\n");
printf("+--------------------------------- 두번째 메뉴  -----------------------------------+\n");
printf("| [1] 두번째 희소 행렬 입력(덧셈, 곱셈)  [2] 입력된 행렬 Transpose하기  [3] 끝내기 |\n");
printf("+----------------------------------------------------------------------------------+\n");
printf("\n=>두번째메뉴에서 원하는 실행사항을 선택해주세요 (1 또는 2 또는 3으로 입력해주세요) ===>   ");
scanf("%d", &menu2);
switch (menu2) {
case 1:
	printf("\n**두번째 희소 행렬 입력하기를 선택하셨습니다**\n");
	op2 = mread();
	mwrite(op2);
	break;
case 2:
	printf("\n**입력된 행렬 Transpose하기를 선택하셨습니다**\n");
	result = mtranspose(op1);
	mwrite(result);
	merase(&op1);
	merase(&result);
	printf("\n**희소 행렬 연산이 종료되었습니다. BYE BYE~**\n\n");
	return 0;
	break;
case 3:
	printf("\n**희소 행렬 연산하기 프로그램을 끝냅니다. BYE BYE~**\n\n");
	return 0;
	break;
default:
	printf("\n**없는 메뉴를 선택하셨습니다. 프로그램을 종료합니다.**\n\n");
	return 0;
}
printf("\n");
printf("+--------------------------------- 세번째 메뉴  -----------------------------------+\n");
printf("|   [1] 두 행렬 간의 덧셈            [2] 두 행렬 간의 곱셈            [3] 끝내기   |\n");
printf("+----------------------------------------------------------------------------------+\n");
printf("\n=>세번째메뉴에서 원하는 실행사항을 선택해주세요 (1 또는 2 또는 3으로 입력해주세요) ===>   ");
scanf("%d", &menu3);
switch (menu3) {
case 1:
	printf("\n**두 행렬 간의 덧셈하기를 선택하셨습니다**\n");
	result = madd(op1, op2);
	mwrite(result);
	merase(&op1);
	merase(&op2);
	merase(&result);
	printf("\n**희소 행렬 연산이 종료되었습니다. BYE BYE~**\n\n");
	return 0;
	break;
case 2:
	printf("\n**두 행렬 간의 곱셈하기를 선택하셨습니다**\n");
	result = mmult(op1, op2);
	mwrite(result);
	merase(&op1);
	merase(&op2);
	merase(&result);
	printf("\n**희소 행렬 연산이 종료되었습니다. BYE BYE~**\n\n");
	return 0;
	break;
case 3:
	printf("\n**희소 행렬 연산하기 프로그램을 끝냅니다. BYE BYE~**\n\n");
	return 0;
	break;
default:
	printf("\n**없는 메뉴를 선택하셨습니다. 프로그램을 종료합니다.**\n\n");
	return 0;
}

}


	
matrixPointer mread(void)
{ /* 희소행렬 입력받아 저장하기 */

	int numRow, numCol, numTerm, numHead, i, row, col, value, currentRow = 0;

	matrixPointer temp, last, node;

	printf("\n행렬의 행의 개수, 열의 개수, 0이 아닌 entry의 개수를 입력하세요.\n입력은 공백을 구분자로 정수만 해주세요.(입력예시: 2 4 2)==> ");

	scanf("%d %d %d", &numRow, &numCol, &numTerm);

	numHead = (numCol > numRow) ? numCol : numRow;//헤드노드의 개수는 행, 열 중 많은 걸로
	node = newNode();
	node->tag = entry;
	node->u.entry.row = numRow;
	node->u.entry.col = numCol;

	if (!numHead)
		node->right = node;
	else {
		for (i = 0; i < numHead; i++) {
			/* hdnode를 초기화 */
			temp = newNode();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];

		printf("\n행 열 값을 순서대로 공백을 구분자로 입력해주세요. \n");
		for (i = 0; i < numTerm; i++)
		{
			printf("%d번째 원소의 행 열 값==> ", (i+1));
			scanf("%d %d %d", &row, &col, &value);
			if (row > currentRow) {    
				/* 이전에 입력받은 열 값보다 현재 입력받은 열 값이 클 때 */
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
	/* 행렬 출력 */
	int i;
	matrixPointer temp, head = node->right;

	printf(" \n 행의 개수는 %d, 열의 개수는 %d \n", node->u.entry.row, node->u.entry.col);
	printf(" 행, 열, 값으로 출력합니다! \n\n");
	for (i = 0; i < node->u.entry.row; i++) { 
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	}
}

void merase(matrixPointer *node) {
	/* 연산 후 행렬 메모리 반환 */
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
	/* 행렬 덧셈 */
	int i, n = 0, j, no = 0;
	int numRow = 0, numCol = 0, numTerm = 0;
	int numHead, row, col, value, currentRow;
	matrixPointer temp, head1 = nodea->right, nodec;
	re rehdnode[MAX_SIZE];  

	for (i = 0; i < nodea->u.entry.row; i++) {
		for (temp = head1->right; temp != head1; temp = temp->right) { 
			/* 각 행에서 0이 아닌 원소 찾기 */
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
				/* 행과 열이 같은 원소가 나오면 덧셈 실시 */
				if ((rehdnode[j].row == temp->u.entry.row) && (rehdnode[j].col == temp->u.entry.col)) { 
					no++;
					rehdnode[j].val += temp->u.entry.value; 
				}
			}
			if (no == 0) { 
				/* 행과 열에 같은 원소가 없을 때 */
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
			/* 0이 아닌 인자의 개수 */
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
	/* 행렬 곱셈 */
	int i, n1 = 0, n2 = 0, j, k, no = 0;
	int numRow = 0, numCol = 0, numTerm = 0;
	int row, col, value, crow = 0;
	matrixPointer temp, heads = nodea->right, nodec;
	re rehdnode[MAX_SIZE];
	re copy[MAX_SIZE];

	for (i = 0; i < nodea->u.entry.row; i++) {
		/* 각 행에서 0이 아닌 인자 찾아 저장 */
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
	/* 행렬 전치 */
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
	/* 새로운 노드 메모리 할당 */
	matrixPointer node;
	node = (matrixPointer)malloc(sizeof(*node));
	return node;
}

matrixPointer xmread(int ncol, int nrow, int nterm, re *rehdnode) {
	/* 결과 행렬 */
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



