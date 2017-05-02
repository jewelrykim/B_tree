#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)
#define membernum 3

int a;

struct datanode {
	int node[membernum];
	datanode* cpointer[membernum + 1];
	datanode* ppointer;
};
struct bignode {
	int node[membernum + 1];
	datanode* cpointer[membernum + 2];
	datanode* ppointer;
};
typedef struct datanode* nodePtr;
typedef struct bignode* bignodePtr;

void init_node(nodePtr initnode) {
	for (int i = 0; i < membernum; i++) {
		initnode->node[i] = NULL;
		initnode->cpointer[i] = NULL;
		initnode->ppointer = NULL;
	}
	initnode->cpointer[membernum] = NULL;
}
void init_bignode(bignodePtr initbignode) {
	for (int i = 0; i < membernum + 1; i++) {
		initbignode->node[i] = NULL;
		initbignode->cpointer[i] = NULL;
		initbignode->ppointer = NULL;
	}
	initbignode->cpointer[membernum+1] = NULL;
}

void search_data(nodePtr currentnode) { //Ư�� �����͸� ã�� �Լ�
	printf("%d", currentnode->node[0]);
}
void print_data(nodePtr currentnode) {
	for (int i = 0; i < membernum; i++) {
		printf(" %d  ", currentnode->node[i]);
	}
	printf("\n");

	for (int i = 0; i < membernum; i++) {
		if (currentnode->cpointer[i] != NULL) {
			print_data(currentnode->cpointer[i]);
			printf("\n");
		}
	}
}

int data_count(nodePtr currentnode) {	//��忡 ������ ���� 1 ~ N
	int count = 0;
	for (int i = 0; i < membernum; i++) {
		if (currentnode->node[i] == NULL) {
			return i;
		}
	}
	return membernum;
}
int search_point(nodePtr currentnode,int targetdata) { //�����Ͱ� �� ��ġ 0 ~ N
	int count = data_count(currentnode);
	for (int i = 0; i < count; i++) {
		if (currentnode->node[i] > targetdata) {
			return i;
		}
	}
	return count ;
}
void inputbignode(nodePtr currentnode, bignodePtr bignodetemp, int location, int targetdata) { // big��忡 �߰��� �����Ϳ� ���� �����͸� �����ϴ°�
	if (location == 0) {	//target�� ���� ���� ���̴�.
		bignodetemp->node[0] = targetdata;
		bignodetemp->ppointer = currentnode->ppointer;
		for (int i = 0; i < membernum ; i++) {
			bignodetemp->node[i + 1] = currentnode->node[i];
			bignodetemp->cpointer[i + 1] = currentnode->cpointer[i];
		}
	}
	else if (location == membernum ) { //target�� ���� ū �� �̴�.
		bignodetemp->node[membernum] = targetdata;
		bignodetemp->ppointer = currentnode->ppointer;
		for (int i = 0; i < membernum ; i++) {
			bignodetemp->node[i ] = currentnode->node[i];
			bignodetemp->cpointer[i] = currentnode->cpointer[i];
		}
	}
	else {	//target�� �߰��� ����.
		for (int i = 0; i < location; i++) {
			bignodetemp->node[i] = currentnode->node[i];
			bignodetemp->cpointer[i] = currentnode->cpointer[i];
		}
		bignodetemp->node[location] = currentnode->node[location];
		bignodetemp->cpointer[location] = currentnode->cpointer[location];
		bignodetemp->ppointer= currentnode->ppointer;
		for (int i = location+1; i < membernum+1; i++) {
			bignodetemp->node[i] = currentnode->node[i-1];
			bignodetemp->cpointer[i] = currentnode->cpointer[i-1];
		}
	}
	init_node(currentnode);
}

void replace_node(nodePtr currentnode, int startpoint ,int targetdata) { //��带 �ڷ� ��ĭ�� �̷��.
	for (int i = data_count(currentnode)-1 ; i > startpoint - 1; i--)
	{
		currentnode->node[i + 1] = currentnode->node[i];
	}
	currentnode->node[startpoint] = targetdata;
}
int leafnodeflag(nodePtr currentnode) {
	for (int i = 0; i < membernum + 1; i++) {
		if (currentnode->cpointer[i] != NULL) {
			return 0;
		}
	}
	return 1;
}

void branchnode(nodePtr currentnode, int targetdata) {	//��尡 �� ���ִ� ���¿��� ����
	//��Ʈ�� ���� ��Ʈ�� �ƴѰ��
	bignodePtr bignodetemp = (bignodePtr)malloc(sizeof(bignodePtr));
	nodePtr newnode = (nodePtr)malloc(sizeof(datanode));
	nodePtr newrootnode = (nodePtr)malloc(sizeof(datanode));
	int j = 0;

	init_node(newnode);
	init_node(newrootnode);
	init_bignode(bignodetemp);
	inputbignode(currentnode, bignodetemp, search_point(currentnode, targetdata), targetdata);

	if (bignodetemp->ppointer == NULL){//���ο� ��Ʈ
		for (int i = 0; i < membernum / 2; i++) {
			newrootnode->node[i] = bignodetemp->node[i];
			newrootnode->cpointer[i] = bignodetemp->cpointer[i];
		}
		newrootnode->ppointer = currentnode;

		currentnode->node[0] = bignodetemp->node[membernum / 2];
		currentnode->cpointer[0] = newrootnode;
		currentnode->cpointer[1] = newnode;

		
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j] = bignodetemp->cpointer[i];
		}
		newnode->ppointer = newrootnode;

	}
	else if (data_count(bignodetemp->ppointer) < membernum) { //�θ��忡 �ڸ��� �ִ� newroot�� �θ��忡 �ִ´�.

		for (int i = 0; i < membernum / 2; i++) {
			currentnode->node[i] = bignodetemp->node[i];
			currentnode->cpointer[i] = bignodetemp->cpointer[i];
		}
		currentnode->ppointer = newrootnode;

		newrootnode->node[0] = bignodetemp->node[membernum / 2];
		newrootnode->cpointer[0] = currentnode;
		newrootnode->cpointer[1] = newnode;
		int j;
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j] = bignodetemp->cpointer[i];
		}
		newnode->ppointer = newrootnode;

		replace_node(bignodetemp->ppointer, search_point(bignodetemp->ppointer, bignodetemp->node[0]), newrootnode->node[0]);	//������ �θ� newroot����� �����͸� �����Ѵ�.
		currentnode->ppointer = bignodetemp->ppointer; //�θ��带 bignode�� �θ�� �ٲ۴�.
		newnode->ppointer = bignodetemp->ppointer;
	}
	else {//�θ��忡 �ڸ��� ����.
		for (int i = 0; i < membernum / 2; i++) {
			currentnode->node[i] = bignodetemp->node[i];
			currentnode->cpointer[i] = bignodetemp->cpointer[i];
		}
		currentnode->ppointer = newrootnode;

		newrootnode->node[0] = bignodetemp->node[membernum / 2];
		newrootnode->cpointer[0] = currentnode;
		newrootnode->cpointer[1] = newnode;
		int j;
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j] = bignodetemp->cpointer[i];
		}
		newnode->ppointer = newrootnode;

		branchnode(bignodetemp->ppointer, newrootnode->node[0]); //bignode�� �θ�� newroot��带 ��ģ��.
	}
}

void insert_point(nodePtr currentnode, int targetdata) {//�����͸� �����ϴ� ���
	int point;
	point = search_point(currentnode, targetdata);
	if (leafnodeflag(currentnode)== 0) {  //������尡 �ƴϴ�.
		insert_point(currentnode->cpointer[point], targetdata);
	}
	else {	//��������
		if (data_count(currentnode) < membernum) {	//��忡 �ڸ��� �ִ�
			replace_node(currentnode, point,targetdata);
		}
		else {	//��忡 �ڸ��� ����.
			branchnode(currentnode, targetdata);
		}
	}
}

void inseart_data(nodePtr currentnode) {
	printf("�Է��ϼ���\n");
	scanf("%d", &a);
	insert_point(currentnode, a);
}

int memu() {
	printf("�޴� \n 1.�˻� 2.�Է� 3.���� 4.��üǥ�� 0.����\n");
	scanf("%d", &a);
	return a;
}
void main() {
	nodePtr initnode = (nodePtr)malloc(sizeof(datanode));
	printf("�Է��ϼ���\n");
	scanf("%d", &a);
	init_node(initnode);
	initnode->node[0] = a;
	while (memu() != 0){
		switch (a)
		{
		case 1:
			//search_data();
			break;
		case 2:
			inseart_data(initnode);
			break;
		case 3:
			break;
		case 4:
			print_data(initnode);
			break;
		default:
			break;
		}
	}
}