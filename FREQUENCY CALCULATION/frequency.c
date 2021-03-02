#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include <time.h>
 
#define MAX_NAME 100
#define MAX_WORDS 10000
#define MAX_WORD_SIZE 100
#define TRUE 1
#define FALSE 0
														 // ������ ����
typedef struct {
	char word[MAX_WORD_SIZE];					 		 // Ű�ʵ�          
	int count;                                  		 //������ word�� ������ count 
} element;

													     // ����� ����

typedef struct TreeNode {
	element key;                      					 //element Ÿ���� Ű 
	struct TreeNode *left, *right;      				 //����� �����ڽ�, �������ڽ� 
} TreeNode;

														// ���� e1 > e2 -> -1 ��ȯ
														// ���� e1 == e2 -> 0 ��ȯ
														// ���� e1 < e2 -> 1 ��ȯ
int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word);
}
														// ��ũ ���Ϸκ��� �� �� �ܾ �о� �迭 word�� ����
														// ���������� �о����� TRUE, �׷��� ������(���� ��) FALSE ����
int getword(FILE *fd, char *word) {
    char ch;                                   		 //������ ���� ch 
                                                     //������ ����i 
	int i;
	do {
		ch = getc(fd);                               // ����ch�� ������ �о���δ� 

		if (ch == EOF)                               // ���� ch�� ������ ���̸� false�� ��ȯ 

			return FALSE;

	} while (!isalpha(ch)); 						// ù��° ���ĺ� ���ڰ� ���ö����� �д´�.
	i = 0;                   
	do { 										    // �ܾ� 1���� �д´�.
		ch = tolower(ch); 							// �ҹ��ڷ� ��ȯ
		word[i++] = ch;     					    // �迭 word�� �ܾ ���� 
		ch = getc(fd);     						    // �ٽ�ch�� ������ �о���δ� 
	} while (isalpha(ch)); 							// ���ĺ� �����̸� ��� �д´�. 
	word[i] = '\0';           
	return TRUE;
}
													// Binary Search Tree�� �� �ܾ� �߰� �Ǵ� ���� �ܾ��� ��� �� ����
TreeNode *update_BST(TreeNode **root, element key) {
	TreeNode* pre = *root;                                
	TreeNode* newNode;
	if (pre != NULL) {
		if (compare(key, pre->key) == 0) {
													// ������ pre�� count�� �ϳ� �ø���, newNode(��ȯ�Ұ�)�� �Ҵ�

		pre->key.count++;
		newNode = pre;

		}

		else if (compare(key, pre->key) < 0) {
													// ���� ���� ���� �ռ���(0���� ���� ��쿡��), ���� ��忡 ���Ͽ� ��ȣ��

		newNode = update_BST(&(pre->left), key);

		}

		else {
													// �ڿ��ִ� ���(0���� Ŭ ���),������ ��忡 ���ؼ� ��ȣ��
			newNode = update_BST(&(pre->right), key);
		}

	}

	else {
													// pre�� NULL�̶�� ��Ʈ ��忡 �� ��带 ����

		newNode = (TreeNode*)malloc(sizeof(TreeNode));
													// key�� �ֱ�
		newNode->key.count = key.count;
		strcpy(newNode->key.word, key.word);
													// �� ����� �¿� �ڽ� ����
		newNode->left = newNode->right = NULL;
													// root�� �ֱ�
		*root = newNode;
	}

	return newNode;

}

 

													// inorder traversal
void inorder(TreeNode *t) {
													// �湮�� ����� �ܾ�� count ���
	if (t) {

		inorder(t->left);                             //����Լ��� ȣ���� ��� �� �����ڽ��� �湮  

		printf("%s %d ", t->key.word, t->key.count);   // �湮�� ����� �ܾ� �� ī��Ʈ�� ��� 

		inorder(t->right);                       //����Լ��� ȣ���� ����� ������ �ڽ��� �湮 

	}

}

 

														// ��� ���� ����

int get_node_count(TreeNode *node) {
												      	//��� ���� = �ڽ��� ��+ ���� ����Ʈ���� ��� �� + ������ ����Ʈ���� ��� ��

	int count = 0;       								// ī��Ʈ�� 0���� �ʱ�ȭ 

	if (node != NULL) {      						    //���� ��尡 NULL�� �ƴϸ� �� ��忡 ���� ������  ����Լ��� ȣ���� �ڽ��� ���� ����� ���� �ڽİ� ������ �ڽ��� ���Ѵ� 
		return 1 + get_node_count(node->left) +                                                                
		get_node_count(node->right);
	
        }
	return count;
}

														// �ִ밪 return
int max(int a, int b) {
	return (a > b) ? a : b;             			   //�ִ밪�� ���ϴ� �Լ� ���� a�� b���� ũ�� a�� ��� �׷��� ������ b�� ��� 
} 
														// Ʈ�� ���� ���
int get_height(TreeNode *node) {
	int height = 0;                        				 //���̸� 0���� �ʱ�ȭ 
	if (node != NULL)
                                                        //���� ��� ����NULL�� �ƴϸ� �� ��尪�� �����ϸ� 
       height = 1 + max(get_height(node->left),
	    get_height(node->right));  						// ����Լ��� ȣ�� �� ����� ���� �ڽİ� ������ �ڽ��� ���̸� ���Ѵ�                       ��

                    									 //�ִ밪�� ���ϴ� �Լ��� ���� �� ���� 1�� ���� �� ���̸� ���� 			
	return height;

}

 

														// Binary Search Tree�� ����Ͽ� �ܾ� �� �ľ�

void main() {

	FILE *fd;                                  
	element e; 						//�о���� ���� fd�� element Ÿ���� ���� e           
	TreeNode *root = NULL; 			// Ʈ����� Ÿ���� root�� tmp�� NULL������ �ʱ�ȭ 
	TreeNode *tmp = NULL;
	char fname[MAX_NAME]; 			// ���� �̸�
	char w[MAX_WORD_SIZE]; 			// �о���� �ܾ�
	int flag; 						// ���� ���� �ƴ��� ����
	clock_t start, finish;          //�ð�����                     
	double duration;                //�ð����� �� �Ҽ��� ���� ǥ�� 
	printf("���� �̸�: ");
	scanf("%s", fname);             //scanf�� ����Ͽ� ���� �̸��� ���´� 

	if ((fd = fopen(fname, "r")) == NULL) {

		fprintf(stderr, "������ ���������ϴ�.\n");   //���� ������ �о��µ� ����NULL�̶�� 
                                                     //������ ���������ϴٶ�� ���� ��� 
		return;

	}
	start = clock(); 								// �ð� ���� ����
	do {
		flag = getword(fd, w); 						// �ܾ� 1�� �б�                
                     
		if (flag == FALSE)                        //���� ���� �ܾ FALSE�� break���� ���� Ż�� 
			break;

		                                      	  //���ڸ� �о��ٸ� e�� �ʱ�ȭ
		                                  
		 
		strcpy(e.word, w);           		        //w�� ���� e.word�� ���� 
		e.count = 1;              			        //e.count�� ���� 1�� �ʱ�ȭ 
		tmp = update_BST(&root, e); 		    	// wordlist update     
		 

		

	} while (1);
	finish = clock(); 								// �ð� ���� ����
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	
	
	inorder(root);                             //inorder �Լ��� ȣ�� �� root�� �Ѱ� �� �� �湮�� ����� �ܾ�� count�� ��� 
	int a = get_node_count(root);              //������ ���� a�� get_node_count�� ȣ�� �� root�� �Ѱ��� �� ��尹�� ��� 
    int b = get_height(root);                  //������ ���� b�� get_height�� ȣ�� �� Ʈ���� ���� ��� 
	
	fclose(fd);                     		   //������ �ݴ´� 
	printf("\n����� ����: %d", a);           //����� ������ Ʈ���� ���� �׸��� �� �� �ð� ��� 
        printf("\nƮ���� ����: %d", b);  
	printf("\n%.6f ���Դϴ�.\n", duration);

	

}
