#include<stdio.h>
#include<stdlib.h>


/* key 값과 다른 노드를 가리킬 링크를 담고있는 노드 구조체 선언 */
typedef struct Node {
	int key; // 데이터
	struct Node* link; // 다른 노드를 가리킬 링크를 자기참조 구조체 포인터로 지정
} listNode;

/* 리스트를 가리킬 헤드 구조체 선언 */
typedef struct Head {
	struct Node* first; 
} headNode;


/** 함수 원형 선언 **/
headNode* initialize(headNode* h);
int freeList(headNode* h);

/* 특정 노드를 추가하는 함수들 */
int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

/* 특정 노드를 삭제하는 함수들 */
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL; // headNode 포인터(HEAD)를 NULL로 선언

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		/** 사용자로부터 받은 입력에 해당하는 케이스를 실행 **/
		switch(command) {
		/* 연결리스트 초기화 */
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		/* 연결리스트 출력 */
		case 'p': case 'P':
			printList(headnode);
			break;
		/* 중간에 새로운 노드를 추가 */
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		/* 중간 노드를 삭제 */
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		/* 끝에 새로운 노드 추가 */
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		/* 마지막 노드를 삭제 */
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		/* 시작에 새로운 노드를 추가 */
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		/* 시작 노드를 삭제 */
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		/* 연결리스트 뒤집기 */
		case 'r': case 'R':
			invertList(headnode);
			break;
		/* 프로그램 종료 */
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/** 연결리스트를 초기화하는 함수 **/
headNode* initialize(headNode* h) {

	if(h != NULL)
		freeList(h); // HEAD가 NULL이 아니면, 할당된 메모리 모두 해제

	// HEAD가 NULL이면 새로운 HEAD를 생성
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode에 대한 메모리를 temp에 할당하여 리턴
	temp->first = NULL;
	return temp;
}

/** 연결리스트 구현에 할당된 메모리를 해제하는 함수 **/
int freeList(headNode* h){
	listNode* p = h->first; // 노드포인터 p 생성

	listNode* prev = NULL;
	/* p 노드가 마지막 노드일때까지 반복 */
	while(p != NULL) { 
		prev = p; // prev를 p와 일치 (p의 이전노드를 계속해서 따라가며 메모리 해제)
		p = p->link; // p가 다음 노드를 가리키게 함
		free(prev); // prev 노드에 할당된 메모리 해제
	}
	free(h);
	return 0;
}


/** 연결리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 해당 노드를 삽입하는 함수 **/
int insertNode(headNode* h, int key) {

	/* 삽입할 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 메모리 할당
	node->key = key; // 노드에 입력받은 key 대입
	node->link = NULL; // 노드 링크에 NULL 지정

	/* 빈 연결리스트일 경우 */
	if (h->first == NULL)
	{
		h->first = node; // HEAD가 생성노드를 가리키게 하고 함수 종료
		return 0;
	}

	/* 빈 연결리스트가 아닐 경우 */
	listNode* n = h->first; // 노드 포인터 n 생성
	listNode* trail = h->first; // n 이전 노드를 가리킬 노드 포인터 trail 생성

	/* key를 기준으로 삽입할 위치 탐색 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 */
			if(n == h->first) {
				h->first = node; // HEAD가 생성노드를 가리키게 한 후
				node->link = n; // 생성노드의 link에 기존의 첫노드 연결
			} else { /* 중간에 삽입해야할 경우 */
				node->link = n; // 1. 생성노드의 link에 n 노드 연결
				trail->link = node; // 2. trail의 link에 생성노드 연결
			}
			return 0;
		}

		trail = n; // trail과 n을 일치 (trail이 다음 노드를 가리키게 함)
		n = n->link; // n이 다음 노드를 가리키게 함
	}

	/* 마지막 노드의 값보다도 클 경우(n이 NULL일 경우) 마지막에 삽입 */
	trail->link = node; // trail의 link에 생성노드 연결
	return 0;
}

/** 연결리스트 마지막에 노드를 추가하는 함수 **/
int insertLast(headNode* h, int key) {
	
	/* 삽입할 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 메모리 할당
	node->key = key; // 노드에 입력받은 key 대입
	node->link = NULL; // 노드 링크에 NULL 지정

	/* HEAD가 NULL이면 함수 종료 */
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first; // 노드 포인터 n 생성
	// HEAD부터 시작하여 연결리스트 끝까지 검색
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node; // n이 마지막 노드를 가리키면, n의 link에 생성노드 연결 
	return 0;
}

/** 연결리스트 처음에 노드를 추가하는 함수 **/
int insertFirst(headNode* h, int key) {

	/* 삽입할 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 메모리 할당
	node->key = key; // 노드에 입력받은 key 대입

	node->link = h->first; // 생성노드의 link에 HEAD 노드 연결
	h->first = node; // HEAD를 생성노드를 가리키게 함

	return 0;
}

/** 연결리스트에서 해당 key의 노드를 삭제하는 함수 **/
int deleteNode(headNode* h, int key) {

	/* 빈 연결리스트일 경우 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 노드포인터 n 생성
	listNode* trail = NULL; // 노드포인터 trail 생성

	/* key를 기준으로 삭제해야 할 노드 검색 */
	while(n != NULL) {
		/* 해당 key가 n의 key와 같은 경우 실행 */
		if(n->key == key) {
			// 첫 노드인 경우
			if(n == h->first) {
				h->first = n->link; // n 노드 다음 노드를 HEAD 노드로 지정
			} else { /* 중간이거나 마지막 노드인 경우 */
				trail->link = n->link; // trail의 link에 n의 다음노드 연결
			}
			free(n); // n에 할당된 메모리 해제
			return 0;
		}

		trail = n; // trail과 n을 일치 (trail이 다음 노드를 가리키게 함)
		n = n->link; // n이 다음노드를 가리키게 함
	}

	/* 해당 key의 노드가 없는 경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/** 연결리스트 마지막 노드를 삭제하는 함수 **/
int deleteLast(headNode* h) {

	/* 빈 연결리스트일 경우 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 노드포인터 n 생성
	listNode* trail = NULL; // 노드포인터 trail 생성

	/* 노드가 하나만 있는 경우 */
	if(n->link == NULL) { // n의 다음노드 즉, HEAD의 다음노드가 없는 경우
		h->first = NULL; // HEAD를 NULL로 지정
		free(n); // n에 할당된 메모리 해제
		return 0;
	}

	/* 마지막 노드 직전 노드까지 이동 */
	while(n->link != NULL) {
		trail = n; // trail과 n을 일치 (trail이 다음 노드를 가리키게 함)
		n = n->link; // n이 다음노드를 가리키게 함
	}

	trail->link = NULL; // trail 노드(마지막 노드 직전 노드)의 link를 NULL로 지정
	free(n); // n에 할당된 메모리 해제

	return 0;
}

/** 연결리스트 첫 노드를 삭제하는 함수 **/
int deleteFirst(headNode* h) {

	/* 빈 연결리스트일 경우 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 노드포인터 n 생성

	h->first = n->link; // HEAD를 n 노드의 다음 노드로 지정
	free(n); // n에 할당된 메모리 해제

	return 0;
}


/** 연결리스트를 역순으로 뒤집는 함수 **/
int invertList(headNode* h) {

	/* 빈 연결리스트일 경우 */
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first; // 노드포인터 n 생성
	listNode *trail = NULL; // 노드포인터 trail 생성
	listNode *middle = NULL; // 노드포인터 middle 생성

	/* n 노드가 마지막 노드일때까지 반복 */
	while(n != NULL){
		trail = middle; // trail을 middle과 일치 (trail은 middle 바로 뒤를 따라감)
		middle = n; // middle을 n과 일치 (middle은 n 바로 뒤를 따라감)
		n = n->link; // n이 다음노드를 가리키게 함
		middle->link = trail; // middle의 link에 trail(n의 이전노드) 연결
	}

	h->first = middle; // HEAD 초기화 (middle 노드가 마지막 노드)

	return 0;
}

/** 연결리스트를 출력하는 함수 **/
void printList(headNode* h) {
	int i = 0; // 연결리스트의 노드갯수를 담을 변수
	listNode* p; // 노드포인터 p 생성

	printf("\n---PRINT\n");

	/* 빈 연결리스트일 경우 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p가 HEAD를 가리키게 함

	/* 연결리스트 마지막까지 탐색 */
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); // p의 key값 출력
		p = p->link; // p를 p 노드의 다음 노드로 지정 
		i++;
	}

	printf("  items = %d\n", i); // 노드갯수 출력
}

