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
void search_data(nodePtr currentnode) { //특정 데이터를 찾는 함수
	printf("%d", currentnode->node[0]);
}
void print_data(nodePtr currentnode) {
	for (int i = 0; i < membernum; i++) {
		printf(" %d  ", currentnode->node[i]);
	}
	printf("\n");
}
int data_count(nodePtr currentnode) {	//노드에 데이터 숫자
	int count = 0;
	for (int i = 0; i < membernum; i++) {
		if (currentnode->node[i] == NULL) {
			return i;
		}
	}
	return membernum;
}

void replace_node(nodePtr currentnode,int startpoint) { //노드를 뒤로 한칸씩 미룬다.
	for (int i = data_count(currentnode)-1; i > startpoint-1 ; i--)
	{
		currentnode->node[i + 1] = currentnode->node[i];
	}
}
void search_point(nodePtr currentnode, int targetdata) {//데이터를 삽입하는 노드
	for (int i = 0; i < membernum-1; i++) {
		if (currentnode->node[i] > targetdata) {	// 해당 데이터보다 작다
			if (currentnode->pointer[i] == NULL) {	//앞 포인터가 비어있다 
				
			}
			else {	//가장 앞 포인터가 비어있지 않다. 자식 노드가 존재 한다.
				search_point(currentnode->pointer[i], targetdata); // 재귀로 위치를 찾는다.
			}
			break;
		}
		else {//현재 노드의 앞 데이터 보다 찾는 데이터가 큰경우
			if (currentnode->node[i + 1] == NULL) {	//현재 노드의 뒤 데이터가 비어있는경우
				if (currentnode->pointer[i+1] == NULL) {	//현재 노드의 뒤 포인터가 비어있는 경우 (리프노드)
					currentnode->node[i + 1] = targetdata;	//현재노드의 뒤 쪽 데이터에 삽입
				}
				else { //현재 노드의 뒤 포인터가 존재 (자식 노드가 있다)
					search_point(currentnode->pointer[i + 1], targetdata); //다시한번 inseart_data로 들어간다 (재귀)
				}
				break;
			}
		}
	}
}
/*
void search_point(nodePtr currentnode, int targetdata) {//데이터를 삽입하는 노드
for (int i = 0; i < membernum-1; i++) {
if (currentnode->node[i] > targetdata) {	// 해당 데이터보다 작다
if (currentnode->pointer[i] == NULL) {	//앞 포인터가 비어있다
if (data_count(currentnode) == membernum ) {	//현재 노드가 가득 찼다
//재배열
}
else {	//현재 노드에 빈 공간이 있다.
replace_node(currentnode, i);
currentnode->node[i] = targetdata;
}
}
else {	//가장 앞 포인터가 비어있지 않다. 자식 노드가 존재 한다.
search_point(currentnode->pointer[i], targetdata); // 재귀로 위치를 찾는다.
}
break;
}
else {//현재 노드의 앞 데이터 보다 찾는 데이터가 큰경우
if (currentnode->node[i + 1] == NULL) {	//현재 노드의 뒤 데이터가 비어있는경우
if (currentnode->pointer[i+1] == NULL) {	//현재 노드의 뒤 포인터가 비어있는 경우 (리프노드)
currentnode->node[i + 1] = targetdata;	//현재노드의 뒤 쪽 데이터에 삽입
}
else { //현재 노드의 뒤 포인터가 존재 (자식 노드가 있다)
search_point(currentnode->pointer[i + 1], targetdata); //다시한번 inseart_data로 들어간다 (재귀)
}
break;
}
}
}
}
*/
void inseart_data(nodePtr currentnode) {
	printf("입력하세요\n");
	scanf("%d", &a);
	search_point(currentnode, a);
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