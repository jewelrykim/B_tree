#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)
#define membernum 3

int a;

struct datanode {
	int node[membernum];
	int pointer[membernum + 1];
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
}
void make_node(int inputdata) {
	nodePtr newnode = (nodePtr)malloc(sizeof(datanode));
}

void add_node() {

};
void search_data(nodePtr currentnode) {
	
}
void search_point() {

}
int memu() {
	printf("메뉴 \n 1.검색 2.입력 3.삭제 4.전체표시 0.종료\n");
	scanf("%d", &a);
	return a;
}
void main() {
	nodePtr initnode = (nodePtr)malloc(sizeof(datanode));
	printf("입력하세요\n");
	scanf("%d", &a);
	init_node(initnode,a);
	while (memu() != 0){
		switch (a)
		{
		case 1:
			//search_data();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			search_data(initnode);
			break;
		default:
			break;
		}
	}
}