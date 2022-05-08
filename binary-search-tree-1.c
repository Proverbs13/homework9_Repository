/* �ʿ��� ������� �߰� */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //Ʈ�� ����ü ���
	int key; // ���� ��
	struct node *left;  //���� �ڽ� ��� ����ų �ڱ����� ����ü ������
	struct node *right; //������ �ڽ� ��� ī��ų �ڱ����� ����ü ������
} Node; //��Ī Node

/* �Լ� ����Ʈ */
int initializeBST(Node** h);  // ��� ��� ����, �޸� �����Ҵ�
// �Ű������� ���������� ����� ������� �ּҸ� �μ��� ������ ����带 ���� �ǵ�
void inorderTraversal(Node* ptr);	 //��͹�� ���� ��ȸ
void preorderTraversal(Node* ptr);   //��͹�� ���� ��ȸ
void postorderTraversal(Node* ptr);	 //��͹�� ���� ��ȸ
int insert(Node* head, int key);  	 //Ʈ���� ��� �߰�
int deleteLeafNode(Node* head, int key);    //������� ����
Node* searchRecursive(Node* ptr, int key);  //��͹�� ��� Ž��
Node* searchIterative(Node* head, int key); //�ݺ���� ��� Ž��
int freeBST(Node* head); //Ʈ�� ������ ���� �޸� ����
int FNode(Node* p); //����������� ���� �޸� ������ ���� �Լ�

int main()
{
	char command; //��� �Է¹��� command
	int key;	  //��忡 ���� ���� key
	Node* head = NULL; //Ʈ�� ����ü �������� ���,���� ��Ʈ��带 ����Ŵ
	Node* ptr = NULL;  //�Ͻ��� �ּҰ� ���� �뵵�� Ʈ�� ����ü ������ 	
	printf("[----- [����] [2019038029] -----]\n");
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

		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			initializeBST(&head); //��Ʈ��� �������� �ּҸ� ����
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
			//�ݺ�������� ��带 ã�� ã������ּҸ� ptr�� ��ȯ
			ptr = searchIterative(head, key); 
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			//��͹������ ��带 ã�� ã������ּҸ� ptr�� ��ȯ
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
	return 1; //���α׷� ����
}

// ��� ��� ����, �޸� �����Ҵ�
int initializeBST(Node** h) { //head��ü�� �ּҰ� �޾ƿ�, �Լ����� *h=head
	// Ʈ���� ������� �ʴٸ� �����޸� ���� ���� ����
	if(*h != NULL){
		freeBST(*h);
	}
	*h = (Node*)malloc(sizeof(Node)); //����� �����Ҵ�
	(*h)->left = NULL; // ��Ʈ��� ����ų left
	(*h)->right= (*h); // �ڱ��ڽ��� ����Ű�� right 
	(*h)->key = -9999;
	return 1; //�Լ� ����
}

//��͹�� ���� ��ȸ = �����ڽ� ���� ���-> �θ�->�������ڽ�
void inorderTraversal(Node* ptr) {
	//�̵��� ptr�� NULL�� �ƴϸ� ����
	if(ptr!=NULL) {
		inorderTraversal(ptr->left);  // �����ڽĳ��� �̵��� �ּҷ� �Լ� ȣ��
		printf("[%d]  ", ptr->key);   // ���� ��� key ���
		inorderTraversal(ptr->right); // �������ڽĳ��� �̵��� �ּҷ� �Լ� ȣ��
	}

}

//��͹�� ���� ��ȸ = �θ���� ���->�����ڽ�->�������ڽ�
void preorderTraversal(Node* ptr) {	
	//�̵��� ptr�� NULL�� �ƴϸ� ����
	if(ptr!=NULL) {
		printf(" [%d] ", ptr->key); //�̵��� ���� ���(�θ�) �켱 �����
		preorderTraversal(ptr->left); //����,������ �ڽ� �ּҷ� �Լ� ȣ��
		preorderTraversal(ptr->right);
	}

}

//��͹�� ���� ��ȸ = �ڽĳ�� �������(��,�� ����) -> �θ�
void postorderTraversal(Node* ptr) {
	//�̵��� ptr�� NULL�� �ƴϸ� ����
	if(ptr!=NULL) {
		postorderTraversal(ptr->left);  //�켱 ����,������ �ڽ� ����ּҷ� �Լ� ȣ�� 
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);     //���� �θ� ��� ���
	}
}

//Ʈ���� ��� �߰� 
int insert(Node* head, int key){
	Node* Nnode = (Node*)malloc(sizeof(Node)); //���� ���� �ڽ� ��� �����Ҵ�
	Nnode->key = key; 	//�Է¹��� key �� ���key������ �ʱ�ȭ
	Nnode->left = NULL; //left,right�� �ʱⰪ���� NULL �ʱ�ȭ
	Nnode->right = NULL;

	// ��Ʈ��尡 �� ������� ���
	if (head->left == NULL) {
		head->left = Nnode; //����� ������ ��Ʈ��� ���� ��
		return 0; // �Լ�����
	}
	//����Ž��Ʈ�� ������Ģ�� ���� ��Ʈ��� �������� ��ҿ� ���� ��� ������ ��ġ ����
	Node* ptr1 = head->left; //Ž���� Ʈ������ü ������ ptr1
	Node* ptr2 = NULL; //Ž���ϴ� ptr1����� �θ��� ��ġ�� ������ ���� ������ ptr2
	
	while (ptr1!=NULL) { // Ž���ϴ� ptr�� NULL�� ������ �ݺ�
		//Ʈ�� ���� �̹��Է��� key��尡 �ִ°��
		if(ptr1->key==key){
			printf("\nThe key you entered is already in the tree.");
			return 0; //�ٷ� �Լ��� ������
		}
		//ptr1�� Ž���ϱ����� �̵��ϱ� �� �θ��� ��ġ ����
		ptr2 = ptr1;
		//�Էµ� key �� ���� ����� Ű������ ��
		if(ptr1->key > key) // Ʈ���� ptr1�� ������ġ�� ���key�� �Էµ� key���� Ŭ ��
			ptr1= ptr1->left; //ptr1 �����ڽĳ��� �̵�
		else //���� �� (���� ���� �̹� �� ���ǿ��� �ɷ���)
			ptr1= ptr1->right;
			printf("!!!!");
	} 
	//�ݺ��� ����Ǹ鼭 ptr1=NULL�� �ǰ� 
	//ptr2�� �߰��Ǵ� ����� �θ��� ��ġ�� ����

	if (ptr2->key > key) // �θ��庸�� ���ο� ����� ���� ������
		ptr2->left = Nnode; // ������ ���� �ڽĳ���
	else //ũ�ٸ�
		ptr2->right = Nnode; // ������ ������ �ڽĳ��� 
}


//������� ����
int deleteLeafNode(Node* head, int key){

}

//��͹�� ��� Ž��
Node* searchRecursive(Node* ptr, int key){

}

//�ݺ���� ��� Ž��
Node* searchIterative(Node* head, int key){

}

//Ʈ�� ������ ���� �޸� ����
int freeBST(Node* head){	
	// Ʈ���� ����ִٸ�
	if(head->left == NULL)
	{
		free(head); //��� ���� �޸� ����
		return 1;   //�Լ�����
	}
	Node* dt = head->left; // ��� ������ p�� ��Ʈ��� ����Ŵ
	FNode(dt);  //��Ʈ����� �ּҸ� ������ ��������� �����޸� ����
	free(head); // ó���� ����� ���� �޸� ����
	return 1;   //�Լ� ����

}

//����������� ���� �޸� ������ ���� �Լ�
int FNode(Node* p){
	//�޾ƿ� p�� NULL�� �ƴҶ� ����-> �ڽĳ�尡 ���� �� ���� Ž��
	if(p!=NULL){
		FNode(p->left);  //�����ڽĳ�� �ּҷ� �Լ�ȣ��
		FNode(p->right); //������ �ڽ� ��� �ּҷ� �Լ�ȣ�� 
		free(p); //���� p ��ġ ���� �޸� ����
	} 
	// �ڽĳ����� ���� ���� �޸� ���� ��Ų ���Ŀ� �θ��尡 �����Ǿ�
	// ��� �ڽĵ��� �����޸� ������ų �� �ֱ� ������ ���� ��ȸ ������� ������
	return 0; //�Լ�����
}



