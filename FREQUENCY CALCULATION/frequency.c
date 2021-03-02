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
														 // 데이터 형식
typedef struct {
	char word[MAX_WORD_SIZE];					 		 // 키필드          
	int count;                                  		 //문자형 word와 정수형 count 
} element;

													     // 노드의 구조

typedef struct TreeNode {
	element key;                      					 //element 타입의 키 
	struct TreeNode *left, *right;      				 //노드의 왼쪽자식, 오른쪽자식 
} TreeNode;

														// 만약 e1 > e2 -> -1 반환
														// 만약 e1 == e2 -> 0 반환
														// 만약 e1 < e2 -> 1 반환
int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word);
}
														// 디스크 파일로부터 한 개 단어를 읽어 배열 word에 저장
														// 성공적으로 읽었으면 TRUE, 그렇지 않으면(파일 끝) FALSE 리턴
int getword(FILE *fd, char *word) {
    char ch;                                   		 //문자형 변수 ch 
                                                     //정수형 변수i 
	int i;
	do {
		ch = getc(fd);                               // 변수ch에 파일을 읽어들인다 

		if (ch == EOF)                               // 만일 ch가 파일의 끝이면 false를 반환 

			return FALSE;

	} while (!isalpha(ch)); 						// 첫번째 알파벳 문자가 나올때까지 읽는다.
	i = 0;                   
	do { 										    // 단어 1개를 읽는다.
		ch = tolower(ch); 							// 소문자로 변환
		word[i++] = ch;     					    // 배열 word에 단어를 저장 
		ch = getc(fd);     						    // 다시ch에 파일을 읽어들인다 
	} while (isalpha(ch)); 							// 알파벳 문자이면 계속 읽는다. 
	word[i] = '\0';           
	return TRUE;
}
													// Binary Search Tree에 새 단어 추가 또는 기존 단어인 경우 빈도 갱신
TreeNode *update_BST(TreeNode **root, element key) {
	TreeNode* pre = *root;                                
	TreeNode* newNode;
	if (pre != NULL) {
		if (compare(key, pre->key) == 0) {
													// 같으면 pre의 count를 하나 올리고, newNode(반환할값)에 할당

		pre->key.count++;
		newNode = pre;

		}

		else if (compare(key, pre->key) < 0) {
													// 새로 들어온 것이 앞서면(0보다 작을 경우에는), 왼쪽 노드에 대하여 재호출

		newNode = update_BST(&(pre->left), key);

		}

		else {
													// 뒤에있는 경우(0보다 클 경우),오른쪽 노드에 대해서 재호출
			newNode = update_BST(&(pre->right), key);
		}

	}

	else {
													// pre가 NULL이라면 루트 노드에 새 노드를 삽입

		newNode = (TreeNode*)malloc(sizeof(TreeNode));
													// key값 넣기
		newNode->key.count = key.count;
		strcpy(newNode->key.word, key.word);
													// 새 노드의 좌우 자식 설정
		newNode->left = newNode->right = NULL;
													// root에 넣기
		*root = newNode;
	}

	return newNode;

}

 

													// inorder traversal
void inorder(TreeNode *t) {
													// 방문한 노드의 단어와 count 출력
	if (t) {

		inorder(t->left);                             //재귀함수를 호출해 노드 의 왼쪽자식을 방문  

		printf("%s %d ", t->key.word, t->key.count);   // 방문한 노드의 단어 와 카운트를 출력 

		inorder(t->right);                       //재귀함수를 호출해 노드의 오른쪽 자식을 방문 

	}

}

 

														// 노드 개수 세기

int get_node_count(TreeNode *node) {
												      	//노드 개수 = 자신의 수+ 왼쪽 서브트리의 노드 수 + 오른쪽 서브트리의 노드 수

	int count = 0;       								// 카운트를 0으로 초기화 

	if (node != NULL) {      						    //만일 노드가 NULL이 아니면 즉 노드에 값이 있으면  재귀함수를 호출해 자신의 수와 노드의 왼쪽 자식과 오른쪽 자식을 더한다 
		return 1 + get_node_count(node->left) +                                                                
		get_node_count(node->right);
	
        }
	return count;
}

														// 최대값 return
int max(int a, int b) {
	return (a > b) ? a : b;             			   //최대값을 구하는 함수 만일 a가 b보다 크면 a를 출력 그렇지 않으면 b를 출력 
} 
														// 트리 높이 계산
int get_height(TreeNode *node) {
	int height = 0;                        				 //높이를 0으로 초기화 
	if (node != NULL)
                                                        //만일 노드 값이NULL이 아니면 즉 노드값이 존재하면 
       height = 1 + max(get_height(node->left),
	    get_height(node->right));  						// 재귀함수를 호출 해 노드의 왼쪽 자식과 오른쪽 자식의 높이를 구한다                       음

                    									 //최대값을 구하는 함수를 적용 한 다음 1을 더한 후 높이를 리턴 			
	return height;

}

 

														// Binary Search Tree를 사용하여 단어 빈도 파악

void main() {

	FILE *fd;                                  
	element e; 						//읽어들일 파일 fd와 element 타입의 변수 e           
	TreeNode *root = NULL; 			// 트리노드 타입의 root와 tmp를 NULL값으로 초기화 
	TreeNode *tmp = NULL;
	char fname[MAX_NAME]; 			// 파일 이름
	char w[MAX_WORD_SIZE]; 			// 읽어들인 단어
	int flag; 						// 파일 끝이 아닌지 여부
	clock_t start, finish;          //시간측정                     
	double duration;                //시간측정 후 소수점 으로 표시 
	printf("파일 이름: ");
	scanf("%s", fname);             //scanf를 사용하여 파일 이름을 적는다 

	if ((fd = fopen(fname, "r")) == NULL) {

		fprintf(stderr, "파일을 열수없습니다.\n");   //만일 파일을 읽었는데 값이NULL이라면 
                                                     //파일을 열수없습니다라는 오류 출력 
		return;

	}
	start = clock(); 								// 시간 측정 시작
	do {
		flag = getword(fd, w); 						// 단어 1개 읽기                
                     
		if (flag == FALSE)                        //만일 읽은 단어가 FALSE면 break문을 통해 탈출 
			break;

		                                      	  //글자를 읽었다면 e를 초기화
		                                  
		 
		strcpy(e.word, w);           		        //w의 값을 e.word로 복사 
		e.count = 1;              			        //e.count의 값을 1로 초기화 
		tmp = update_BST(&root, e); 		    	// wordlist update     
		 

		

	} while (1);
	finish = clock(); 								// 시간 측정 종료
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	
	
	inorder(root);                             //inorder 함수를 호출 해 root를 넘겨 준 후 방문한 노드의 단어와 count를 출력 
	int a = get_node_count(root);              //정수형 변수 a에 get_node_count를 호출 해 root를 넘겨준 후 노드갯수 계산 
    int b = get_height(root);                  //정수형 변수 b에 get_height를 호출 해 트리의 높이 계산 
	
	fclose(fd);                     		   //파일을 닫는다 
	printf("\n노드의 개수: %d", a);           //노드의 개수와 트리의 높이 그리고 소 요 시간 출력 
        printf("\n트리의 높이: %d", b);  
	printf("\n%.6f 초입니다.\n", duration);

	

}
