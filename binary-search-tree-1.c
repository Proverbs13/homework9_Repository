/* 필요한 헤더파일 추가 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //트리 구조체 노드
	int key; // 가질 값
	struct node *left;  //왼쪽 자식 노드 가리킬 자기참조 구조체 포인터
	struct node *right; //오른쪽 자식 노드 카리킬 자기참조 구조체 포인터
} Node; //별칭 Node

/* 함수 리스트 */
int initializeBST(Node** h);  // 헤드 노드 생성, 메모리 동적할당
// 매개변수로 이중포인터 사용해 헤드노드의 주소를 인수로 보내고 헤드노드를 직접 건듬
void inorderTraversal(Node* ptr);	 //재귀방식 중위 순회
void preorderTraversal(Node* ptr);   //재귀방식 전위 순회
void postorderTraversal(Node* ptr);	 //재귀방식 후위 순회
int insert(Node* head, int key);  	 //트리에 노드 추가
int deleteLeafNode(Node* head, int key);    //리프노드 삭제
Node* searchRecursive(Node* ptr, int key);  //재귀방식 노드 탐색
Node* searchIterative(Node* head, int key); //반복방식 노드 탐색
int freeBST(Node* head); //트리 노드들의 동적 메모리 해제
int FNode(Node* p); //재귀형식으로 동적 메모리 해제를 위한 함수

int main()
{
	char command; //명령 입력받을 command
	int key;	  //노드에 넣을 내용 key
	Node* head = NULL; //트리 구조체 포인터인 헤드,헤드는 루트노드를 가리킴
	Node* ptr = NULL;  //일시적 주소값 저장 용도의 트리 구조체 포인터 	
	printf("[----- [이찬] [2019038029] -----]\n");
	do{
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { //사용자의 입력에 따른 명령 실행
		case 'z': case 'Z':
			initializeBST(&head); //루트노드 포인터의 주소를 보냄
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			//반복방식으로 노드를 찾아 찾은노드주소를 ptr에 반환
			ptr = searchIterative(head, key); 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			//재귀방식으로 노드를 찾아 찾은노드주소를 ptr에 반환
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 'i': case 'I':
			inorderTraversal(head->left); 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1; //프로그램 종료
}

// 헤드 노드 생성, 메모리 동적할당
int initializeBST(Node** h) { //head자체의 주소값 받아옴, 함수에서 *h=head
	// 트리가 비어있지 않다면 동적메모리 해제 먼저 진행
	if(*h != NULL){
		freeBST(*h);
	}
	*h = (Node*)malloc(sizeof(Node)); //헤드노드 동적할당
	(*h)->left = NULL; // 루트노드 가리킬 left
	(*h)->right= (*h); // 자기자신을 가리키는 right 
	(*h)->key = -9999;
	return 1; //함수 종료
}

//재귀방식 중위 순회 = 왼쪽자식 먼저 출력-> 부모->오른쪽자식
void inorderTraversal(Node* ptr) {
	//이동한 ptr이 NULL이 아니면 실행
	if(ptr!=NULL) {
		inorderTraversal(ptr->left);  // 왼쪽자식노드로 이동한 주소로 함수 호출
		printf("[%d]  ", ptr->key);   // 현재 노드 key 출력
		inorderTraversal(ptr->right); // 오른쪽자식노드로 이동한 주소로 함수 호출
	}

}

//재귀방식 전위 순회 = 부모먼저 출력->왼쪽자식->오른쪽자식
void preorderTraversal(Node* ptr) {	
	//이동한 ptr이 NULL이 아니면 실행
	if(ptr!=NULL) {
		printf(" [%d] ", ptr->key); //이동한 현재 노드(부모) 우선 출력후
		preorderTraversal(ptr->left); //왼쪽,오른쪽 자식 주소로 함수 호출
		preorderTraversal(ptr->right);
	}

}

//재귀방식 후위 순회 = 자식노드 먼저출력(왼,오 순서) -> 부모
void postorderTraversal(Node* ptr) {
	//이동한 ptr이 NULL이 아니면 실행
	if(ptr!=NULL) {
		postorderTraversal(ptr->left);  //우선 왼쪽,오른쪽 자식 노드주소로 함수 호출 
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);     //이후 부모 노드 출력
	}
}

//트리에 노드 추가 
int insert(Node* head, int key){
	Node* Nnode = (Node*)malloc(sizeof(Node)); //새로 만든 자식 노드 동적할당
	Nnode->key = key; 	//입력받은 key 를 노드key값으로 초기화
	Nnode->left = NULL; //left,right는 초기값으로 NULL 초기화
	Nnode->right = NULL;

	// 루트노드가 안 만들어진 경우
	if (head->left == NULL) {
		head->left = Nnode; //헤드노드 연결해 루트노드 생성 후
		return 0; // 함수종료
	}
	//이진탐색트리 생성규칙에 맞춰 루트노드 기준으로 대소에 따라 노드 생성될 위치 설정
	Node* ptr1 = head->left; //탐색용 트리구조체 포인터 ptr1
	Node* ptr2 = NULL; //탐색하는 ptr1노드의 부모노드 위치를 저장해 놓을 포인터 ptr2
	
	while (ptr1!=NULL) { // 탐색하던 ptr이 NULL일 때까지 반복
		//트리 내에 이미입력한 key노드가 있는경우
		if(ptr1->key==key){
			printf("\nThe key you entered is already in the tree.");
			return 0; //바로 함수를 종료함
		}
		//ptr1이 탐색하기위해 이동하기 전 부모노드 위치 저장
		ptr2 = ptr1;
		//입력된 key 와 원래 노드의 키값과의 비교
		if(ptr1->key > key) // 트리내 ptr1의 현재위치의 노드key가 입력된 key보다 클 때
			ptr1= ptr1->left; //ptr1 왼쪽자식노드로 이동
		else //작을 때 (같을 때는 이미 윗 조건에서 걸러짐)
			ptr1= ptr1->right;
			printf("!!!!");
	} 
	//반복문 종료되면서 ptr1=NULL이 되고 
	//ptr2는 추가되는 노드의 부모노드 위치에 있음

	if (ptr2->key > key) // 부모노드보다 새로운 노드의 값이 작으면
		ptr2->left = Nnode; // 새노드는 왼쪽 자식노드로
	else //크다면
		ptr2->right = Nnode; // 새노드는 오른쪽 자식노드로 
}


//리프노드 삭제
int deleteLeafNode(Node* head, int key){

}

//재귀방식 노드 탐색
Node* searchRecursive(Node* ptr, int key){

}

//반복방식 노드 탐색
Node* searchIterative(Node* head, int key){

}

//트리 노드들의 동적 메모리 해제
int freeBST(Node* head){	
	// 트리가 비어있다면
	if(head->left == NULL)
	{
		free(head); //헤드 동적 메모리 해제
		return 1;   //함수종료
	}
	Node* dt = head->left; // 노드 포인터 p는 루트노드 가리킴
	FNode(dt);  //루트노드의 주소를 보내줘 재귀적으로 동적메모리 해제
	free(head); // 처음의 헤드노드 동적 메모리 해제
	return 1;   //함수 종료

}

//재귀형식으로 동적 메모리 해제를 위한 함수
int FNode(Node* p){
	//받아온 p가 NULL이 아닐때 실행-> 자식노드가 없을 때 까지 탐색
	if(p!=NULL){
		FNode(p->left);  //왼쪽자식노드 주소로 함수호출
		FNode(p->right); //오른쪽 자식 노드 주소로 함수호출 
		free(p); //현재 p 위치 동적 메모리 해제
	} 
	// 자식노드들을 먼저 동적 메모리 해제 시킨 이후에 부모노드가 해제되야
	// 모든 자식들을 동적메모리 해제시킬 수 있기 때문에 후위 순회 방식으로 해제함
	return 0; //함수종료
}



