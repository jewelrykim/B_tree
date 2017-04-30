#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)
#define membernum 5

int a;

struct datanode {
	int node[membernum];
	datanode* pointer[membernum + 1];
	bool leaf;
};
typedef struct datanode* nodePtr;
void find_node() {

}
void init_node(nodePtr initnode, int inputdata) {
	//nodePtr initnode = (nodePtr)malloc(sizeof(datanode));
	for (int i = 0; i < membernum; i++) {
		initnode->node[i] = NULL;
		initnode->pointer[i] = NULL;
	}
	initnode->node[0] = inputdata;
	initnode->leaf = 0;
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

void replace_node(nodePtr currentnode,int startpoint) { //��带 �ڷ� ��ĭ�� �̷��.
	for (int i = data_count(currentnode)-1; i > startpoint-1 ; i--)
	{
		currentnode->node[i + 1] = currentnode->node[i];
	}
}
void search_point(nodePtr currentnode, int targetdata) {//�����͸� �����ϴ� ���
	for (int i = 0; i < membernum-1; i++) {
		if (currentnode->node[i] > targetdata) {	// �ش� �����ͺ��� �۴�
			if (currentnode->pointer[i] == NULL) {	//�� �����Ͱ� ����ִ� 
				
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
	search_point(currentnode, a);
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
	init_node(initnode,a);

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