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
	initnode->ppointer = NULL;
}
void init_bignode(bignodePtr initbignode) {
	for (int i = 0; i < membernum + 1; i++) {
		initbignode->node[i] = NULL;
		initbignode->cpointer[i] = NULL;
		initbignode->ppointer = NULL;
	}
	initbignode->cpointer[membernum+1] = NULL;
}

void search_data(nodePtr currentnode) { //특정 데이터를 찾는 함수
	printf("%d", currentnode->node[0]);
}
void print_data(nodePtr currentnode) {

	for (int i = 0; i < membernum; i++) {
		printf(" %d  ", currentnode->node[i]);
	}
	printf(" \n");

	for (int i = 0; i < membernum+1; i++) {
		if (currentnode->cpointer[i] != NULL) {
			print_data(currentnode->cpointer[i]);
		}
	}
}

int data_count(nodePtr currentnode) {	//노드에 데이터 숫자 1 ~ N
	int count = 0;
	for (int i = 0; i < membernum; i++) {
		if (currentnode->node[i] == NULL) {
			return i;
		}
	}
	return membernum;
}
int search_point(nodePtr currentnode,int targetdata) { //데이터가 들어갈 위치 0 ~ N
	int count = data_count(currentnode);
	for (int i = 0; i < count; i++) {
		if (currentnode->node[i] > targetdata) {
			return i;
		}
	}
	return count ;
}
void inputbignode(nodePtr currentnode, bignodePtr bignodetemp, int location, nodePtr targetdata) { // big노드에 추가된 데이터와 기존 데이터를 삽입하는것
	if (location == 0) {	//target이 가장 작은 수이다.
		
		for (int i = 0; i < membernum ; i++) {
			bignodetemp->node[i + 1] = currentnode->node[i];
			bignodetemp->cpointer[i + 1] = currentnode->cpointer[i];
		}
		bignodetemp->node[0] = targetdata->node[0];
		bignodetemp->cpointer[0] = targetdata->cpointer[0];
		bignodetemp->cpointer[1] = targetdata->cpointer[1];
		bignodetemp->ppointer = currentnode->ppointer;
	}
	else if (location == membernum ) { //target이 가장 큰 수 이다.

		for (int i = 0; i < membernum ; i++) {
			bignodetemp->node[i ] = currentnode->node[i];
			bignodetemp->cpointer[i] = currentnode->cpointer[i];
		}
		bignodetemp->node[membernum] = targetdata->node[0];

		bignodetemp->cpointer[membernum] = targetdata->cpointer[0];
		bignodetemp->cpointer[membernum+1] = targetdata->cpointer[1];
		bignodetemp->ppointer = currentnode->ppointer;
	}
	else {	//target이 중간에 들어간다.
		for (int i = 0; i < location; i++) {
			bignodetemp->node[i] = currentnode->node[i];
			bignodetemp->cpointer[i] = currentnode->cpointer[i];
		}
	
		for (int i = location+1; i < membernum+1; i++) {
			bignodetemp->node[i] = currentnode->node[i-1];
			bignodetemp->cpointer[i] = currentnode->cpointer[i-1];
		}
		bignodetemp->node[location] = currentnode->node[location];
		bignodetemp->cpointer[location] = currentnode->cpointer[0];
		bignodetemp->cpointer[location+1] = currentnode->cpointer[1];
		bignodetemp->ppointer = currentnode->ppointer;
	}
	init_node(currentnode);
}

void replace_node(nodePtr currentnode, int startpoint, nodePtr targetdata) { //노드를 뒤로 한칸씩 미룬다.
	for (int i = data_count(currentnode)-1 ; i > startpoint - 1; i--)
	{
		currentnode->node[i + 1] = currentnode->node[i];
		currentnode->cpointer[i + 1] = currentnode->cpointer[i];
	}
	currentnode->node[startpoint] = targetdata->node[0];
	currentnode->cpointer[startpoint] = targetdata->cpointer[0];
	currentnode->cpointer[startpoint + 1] = targetdata->cpointer[1];

}
int leafnodeflag(nodePtr currentnode) {
	for (int i = 0; i < membernum + 1; i++) {
		if (currentnode->cpointer[i] != NULL) {
			return 0;
		}
	}
	return 1;
}

void branchnode(nodePtr currentnode, nodePtr targetdata) {	//노드가 꽉 차있는 상태에서 삽입
	//루트인 경우와 루트가 아닌경우
	bignodePtr bignodetemp = (bignodePtr)malloc(sizeof(bignode));
	nodePtr newnode = (nodePtr)malloc(sizeof(datanode));
	nodePtr newrootnode = (nodePtr)malloc(sizeof(datanode));
	int j = 0;
	int point;
	init_node(newnode);
	init_node(newrootnode);
	init_bignode(bignodetemp);

	inputbignode(currentnode, bignodetemp, search_point(currentnode, targetdata->node[0]), targetdata);
	
	if (bignodetemp->ppointer == NULL){//새로운 루트 currentnode를 root로
		newrootnode->cpointer[0] = bignodetemp->cpointer[0];
		for (int i = 0; i < membernum / 2; i++) {
			newrootnode->node[i] = bignodetemp->node[i];
			newrootnode->cpointer[i+1] = bignodetemp->cpointer[i+1];
		}
		newrootnode->ppointer = currentnode;

		currentnode->node[0] = bignodetemp->node[membernum / 2];
		currentnode->cpointer[0] = newrootnode;
		currentnode->cpointer[1] = newnode;

		newnode->cpointer[0] = bignodetemp->cpointer[(membernum / 2)+1];
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j+1] = bignodetemp->cpointer[i+1];
		}
		newnode->ppointer = currentnode;

	}
	else if (data_count(bignodetemp->ppointer) < membernum) { //부모노드에 자리가 있다 newroot를 부모노드에 넣는다.
		
		currentnode->cpointer[0] = bignodetemp->cpointer[0];
		for (int i = 0; i < membernum / 2; i++) {
			currentnode->node[i] = bignodetemp->node[i];
			currentnode->cpointer[i+1] = bignodetemp->cpointer[i+1];
		}
		currentnode->ppointer = newrootnode;

		newrootnode->node[0] = bignodetemp->node[membernum / 2];
		newrootnode->cpointer[0] = currentnode;
		newrootnode->cpointer[1] = newnode;

		newnode->cpointer[0] = bignodetemp->cpointer[(membernum / 2) + 1];
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j+1] = bignodetemp->cpointer[i+1];
		}
		newnode->ppointer = newrootnode;
		point = search_point(bignodetemp->ppointer, bignodetemp->node[0]);

		replace_node(bignodetemp->ppointer,point, newrootnode);	//빅노드의 부모에 newroot노드의 데이터를 삽입한다.
		

		currentnode->ppointer = bignodetemp->ppointer; //부모노드를 bignode의 부모로 바꾼다.

		newnode->ppointer = bignodetemp->ppointer;
		//if(bignodetemp->ppointer)
	}
	else {//부모노드에 자리가 없다.
		currentnode->cpointer[0] = bignodetemp->cpointer[0];
		for (int i = 0; i < membernum / 2; i++) {
			currentnode->node[i] = bignodetemp->node[i];
			currentnode->cpointer[i + 1] = bignodetemp->cpointer[i + 1];
		}
		currentnode->ppointer = newrootnode;

		newrootnode->node[0] = bignodetemp->node[membernum / 2];
		newrootnode->cpointer[0] = currentnode;
		newrootnode->cpointer[1] = newnode;

		newnode->cpointer[0] = bignodetemp->cpointer[(membernum / 2) + 1];
		for (int i = (membernum / 2) + 1, j = 0; i < membernum + 1; i++, j++) {
			newnode->node[j] = bignodetemp->node[i];
			newnode->cpointer[j + 1] = bignodetemp->cpointer[i + 1];
		}
		newnode->ppointer = newrootnode;

		branchnode(bignodetemp->ppointer, newrootnode); //bignode의 부모와 newroot노드를 합친다.
	}
}

void insert_point(nodePtr currentnode, nodePtr parent, int targetdata) {//데이터를 삽입하는 노드
	int point;
	nodePtr targetnode = (nodePtr)malloc(sizeof(datanode));
	init_node(targetnode);
	targetnode->node[0]= targetdata;
	point = search_point(currentnode, targetdata);
	currentnode->ppointer = parent;
	if (leafnodeflag(currentnode)== 0) {  //리프노드가 아니다.
		insert_point(currentnode->cpointer[point],currentnode, targetdata);
	}
	else {	//리프노드다
		if (data_count(currentnode) < membernum) {	//노드에 자리가 있다
			replace_node(currentnode, point, targetnode);
		}
		else {	//노드에 자리가 없다.
			branchnode(currentnode, targetnode);
		}
	}
	free(targetnode);
}

void inseart_data(nodePtr currentnode) {
	printf("입력하세요\n");
	scanf("%d", &a);
	insert_point(currentnode,NULL, a);
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