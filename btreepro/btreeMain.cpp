#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)
#define membernum 5

int a;

struct datanode {
	int node[membernum];
	datanode* cpointer[membernum + 1];
	datanode* ppointer;
	bool leaf;
	int count;
};
struct bignode {
	int node[membernum + 1];
	datanode* cpointer[membernum + 2];
	datanode* ppointer;
};
typedef struct datanode* nodePtr;
typedef struct bignode* bignodePtr;
void find_node() {

}
void init_node(nodePtr initnode) {
	for (int i = 0; i < membernum; i++) {
		initnode->node[i] = NULL;
		initnode->cpointer[i] = NULL;
		initnode->ppointer = NULL;
	}
	initnode->leaf = 0;
	initnode->count = 0;
}
void make_node(int inputdata) {
	nodePtr newnode = (nodePtr)malloc(sizeof(datanode));
}

void add_node() {

};
void search_data(nodePtr currentnode) { //Ư�� �����͸� ã�� �Լ�
	printf("%d", currentnode->node[0]);
}
void print_data(nodePtr currentnode) {
	for (int i = 0; i < membernum; i++) {
		printf(" %d  ", currentnode->node[i]);
	}
	printf("\n");
}
int data_count(nodePtr currentnode) {	//��忡 ������ ����
	int count = 0;
	for (int i = 0; i < membernum; i++) {
		if (currentnode->node[i] == NULL) {
			return i;
		}
	}
	return membernum;
}
int search_point(nodePtr currentnode,int targetdata) { //�����Ͱ� �� ��ġ
	for (int i = 0; i < membernum - 1; i++) {
		if (currentnode->node[i] > targetdata) {
			return i;
		}
	}
	return membernum - 1;
}
void inputbignode(nodePtr currentnode, bignodePtr bignodetemp, int location, int targetdata) { // big��忡 �߰��� �����Ϳ� ���� �����͸� �����ϴ°�
	if (location == 0) {
		bignodetemp->node[0] = targetdata;
		bignodetemp->ppointer = currentnode->ppointer;
		for (int i = 0; i < membernum ; i++) {
			bignodetemp->node[i + 1] = currentnode->node[i];
			bignodetemp->cpointer[i + 1] = currentnode->cpointer[i];
		}
	}
	else if (location == membernum - 1) {
		bignodetemp->node[membernum] = targetdata;
		bignodetemp->ppointer = currentnode->ppointer;
		for (int i = 0; i < membernum - 1; i++) {
			bignodetemp->node[i ] = currentnode->node[i];
			bignodetemp->cpointer[i] = currentnode->cpointer[i];
		}
	}
	else {
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
	for (int i = data_count(currentnode) - 1; i > startpoint - 1; i--)
	{
		currentnode->node[i + 1] = currentnode->node[i];
	}
	currentnode->node[startpoint] = targetdata;
}

void branchnode(nodePtr currentnode, int targetdata) {	//��尡 �� ���ִ� ���¿��� ����
	//��Ʈ�� ���� ��Ʈ�� �ƴѰ��
	bignodePtr bignodetemp = (bignodePtr)malloc(sizeof(bignodePtr));
	nodePtr newnode = (nodePtr)malloc(sizeof(datanode));
	nodePtr newrootnode = (nodePtr)malloc(sizeof(datanode));

	init_node(newnode);
	init_node(newrootnode);

	inputbignode(currentnode, bignodetemp, search_point(currentnode, targetdata), targetdata);
	for (int i = 0; i < membernum / 2; i++) {
		currentnode->node[i] = bignodetemp->node[i];
		currentnode->cpointer[i] = bignodetemp->cpointer[i];
	}
	currentnode->ppointer = newrootnode;

	newrootnode->node[0] = bignodetemp->node[membernum / 2];
	newrootnode->cpointer[0] = currentnode;
	newrootnode->cpointer[1] = newnode;

	for (int i = (membernum / 2) + 1, int j = 0; i < membernum + 1; i++, j++) {
		newnode->node[i] = bignodetemp->node[i];
		newnode->cpointer[i] = bignodetemp->cpointer[i];
	}
	newnode->ppointer = newrootnode;

	if (bignodetemp->ppointer == NULL){//�� ���ο� ��Ʈ
	}
	else if (bignodetemp->ppointer->count < membernum-1) { //�θ��忡 �ڸ��� �ִ� newroot�� �θ��忡 �ִ´�.
		replace_node(bignodetemp->ppointer, search_point(bignodetemp->ppointer, bignodetemp->node[0]), newrootnode->node[0]);	//������ �θ� newroot����� �����͸� �����Ѵ�.
		currentnode->ppointer = bignodetemp->ppointer; //�θ��带 bignode�� �θ�� �ٲ۴�.
		newnode->ppointer = bignodetemp->ppointer;
	}
	else {//�θ��忡 �ڸ��� ����.
		branchnode(bignodetemp->ppointer, newrootnode->node[0]); //bignode�� �θ�� newroot��带 ��ģ��.

	}
}
//////////////////////////////////////////////////////
void insert_point(nodePtr currentnode, int targetdata) {//�����͸� �����ϴ� ���
	for (int i = 0; i < membernum-1; i++) {
		if (currentnode->node[i] > targetdata) {	// �ش� �����ͺ��� �۴�
			if (currentnode->leaf == true) {
				if (currentnode->count < membernum) {	//��忡 �ڸ��� �ִ�
					currentnode->node[ currentnode->count - 1] = targetdata;
				}
				else {	//��忡 �ڸ��� ����.
					branchnode(currentnode,targetdata);
				}
			}

			if (currentnode->cpointer[i] == NULL) {	//�� �����Ͱ� ����ִ� 
				
			}
			else {	//���� �� �����Ͱ� ������� �ʴ�. �ڽ� ��尡 ���� �Ѵ�.
				//search_point(currentnode->cpointer[i], targetdata); // ��ͷ� ��ġ�� ã�´�.
			}
			break;
		}
		else {//���� ����� �� ������ ���� ã�� �����Ͱ� ū���
			if (currentnode->node[i + 1] == NULL) {	//���� ����� �� �����Ͱ� ����ִ°��
				if (currentnode->cpointer[i+1] == NULL) {	//���� ����� �� �����Ͱ� ����ִ� ��� (�������)
					currentnode->node[i + 1] = targetdata;	//�������� �� �� �����Ϳ� ����
				}
				else { //���� ����� �� �����Ͱ� ���� (�ڽ� ��尡 �ִ�)
				//	search_point(currentnode->cpointer[i + 1], targetdata); //�ٽ��ѹ� inseart_data�� ���� (���)
				}
				break;
			}
		}
	}
}
/*
void search_point(nodePtr currentnode, int targetdata) {//�����͸� �����ϴ� ���
for (int i = 0; i < membernum-1; i++) {
if (currentnode->node[i] > targetdata) {	// �ش� �����ͺ��� �۴�
if (currentnode->pointer[i] == NULL) {	//�� �����Ͱ� ����ִ�
if (data_count(currentnode) == membernum ) {	//���� ��尡 ���� á��
//��迭
}
else {	//���� ��忡 �� ������ �ִ�.
replace_node(currentnode, i);
currentnode->node[i] = targetdata;
}
}
else {	//���� �� �����Ͱ� ������� �ʴ�. �ڽ� ��尡 ���� �Ѵ�.
search_point(currentnode->pointer[i], targetdata); // ��ͷ� ��ġ�� ã�´�.
}
break;
}
else {//���� ����� �� ������ ���� ã�� �����Ͱ� ū���
if (currentnode->node[i + 1] == NULL) {	//���� ����� �� �����Ͱ� ����ִ°��
if (currentnode->pointer[i+1] == NULL) {	//���� ����� �� �����Ͱ� ����ִ� ��� (�������)
currentnode->node[i + 1] = targetdata;	//�������� �� �� �����Ϳ� ����
}
else { //���� ����� �� �����Ͱ� ���� (�ڽ� ��尡 �ִ�)
search_point(currentnode->pointer[i + 1], targetdata); //�ٽ��ѹ� inseart_data�� ���� (���)
}
break;
}
}
}
}
*/
void inseart_data(nodePtr currentnode) {
	printf("�Է��ϼ���\n");
	scanf("%d", &a);
	//search_point(currentnode, a);
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