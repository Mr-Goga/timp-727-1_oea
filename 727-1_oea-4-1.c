#include<stdio.h>
#include<stdlib.h>
/* ñòðóêòóðà äëÿ õðàíåíèÿ óçëà äåðåâà. Íåîáõîäèìî õðàíèòü
ññûëêè íà ïîòîìêîâ, ïðåäêà è íåêîòîðîå çíà÷åíèå (öåëîå ÷èñ
ëî) */
typedef struct node
{
	int value;
	struct node *pred;
	struct node *left; 
	struct node *right;
}node;


/* ñòðóêòóðà äëÿ õðàíåíèÿ äåðåâà. õðàíèò ññûëêó íà êîðåíü
äåðåâà è êîëè÷åñòâî ýëåìåíòîâ â äåðåâå */
typedef struct tree
{
	node *root;
	int size;
}tree;


// èíèöèàëèçàöèÿ ïóñòîãî äåðåâà
void init(tree* t) 
{
	t->root = NULL;
	t->size = 0;
}


//óäàëèòü âñå ýëåìåíòû èç äåðåâà
void clear(struct tree* t)
{
	while (t->root != NULL)
	{
		if (t->root->left != NULL)
		{
			if (t->root->right != NULL)
			{
				t->root = t->root->right;
				while (t->root->left != NULL)
				{
					t->root = t->root->left;
				}
				if (t->root->right != NULL)
				{
					t->root = t->root->right;
					free(t->root);
					t->root = NULL;
					
				}
			}
			else
			{
				t->root = t->root->left;
			}
		}
		else
		{
			free(t->root);
			t->root = NULL;
			
		}
	}
}



/* ïîèñê ýëåìåíòà ïî çíà÷åíèþ. âåðíóòü 0 åñëè ýëåìåíò íàéä
åí è ññûëêó íà íàéäåííéû ýëåìåíò â ïåðåìåííóþ n åñëè n !=
NULL. â ñëó÷àå åñëè ýëåìåíò íå íàéäåí âåðíóòü 1
*/

int find(struct tree* t, int value, struct node** n) {
	struct node* tmp = t->root;
	for (;;) {
		if (tmp != NULL) {
			if (tmp->value == value) {
				*n = tmp;
				tmp = NULL;
				return 0;
			}
			else
				if (tmp->value > value)
				{
					tmp = tmp->left;
				}
				else
				{
					tmp = tmp->right;
				}
		}
		else {
			return 1;
		}
	}

}



/* âñòàâêà çíà÷åíèÿ â äåðåâî. âåðíóòü 0 åñëè âñòàâêà âûïîë
íåíà óñïåøíà,
1 åñëè ýëåìåíò óæå ñóùåñòâóåò
2 åñëè íå óäàëîñü âûäåëèòü ïàìÿòü äëÿ íîâîãî ýëåìåíòà
*/

int insert(struct tree* t, int value) {
	struct node* tmp = (struct node*)malloc(sizeof(struct node));
	if (tmp == NULL) {
		return 2;
	}
	tmp->value = value;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->pred = NULL;
	struct node* t2 = t->root;
	if (t2 == NULL) {
		t2 = tmp;
		t->root = t2;
		t->size++;
		return 0;
	}

	for (;;) {
		if (t2->value == value) {
			return 1;
		}
		struct node* t3;
		if (t2->value > value)
		{
			if (t2->left == NULL) {
				t2->left = tmp;
				t2->left->pred = t2;
				tmp = NULL;
				t->size++;
				return 0;
			}
			else {
				t3 = t2;
				t2 = t2->left;
			}
		}
		else
		{
			if (t2->right == NULL) {
				t2->right = tmp;
				t2->right->pred = t2;
				tmp = NULL;
				t->size++;
				return 0;
			}
			else {
				t2 = t2->right;
			}
		}
	}
}




/* óäàëèòü ýëåìåíò èç äåðåâà. âåðíóòü 0 åñëè ýëåìåíò áûë ó
äàëåí è 1 åñëè íåò ýëåìåíòà ñ óêàçàííûì çíà÷åíèåì */
int remove_(tree* t, int value) 
{
	node *n=NULL;
	if (find(t, value, &n) == 1)
	{
		return 1;
	}
	else 
	{
		if ((n->left == NULL) && (n->right == NULL))// Åñëè íåò ïîòîìêîâ 
		{
			if (n->pred != NULL)//Óñëîâèå ïðîâåðÿåò ïîïàäàíèå â êîðåíü
			{
				if (n->pred->left == n)
				{
					t->size--;
					n->pred->left = NULL;
					free(n);
					return 0;
				}
				else
				{
					t->size--;
					n->pred->right = NULL;
					free(n);
					return 0;
				}
			}
			else 
			{
				free(n);
				return 0;
			}
		}
		if ((n->left == NULL) && (n->right != NULL))// Åñëè ëåâûé ïîòîìîê íóëåâîé
		{
			if (n->pred != NULL)//Óñëîâèå ïðîâåðÿåò ïîïàäàíèå â êîðåíü
			{

				if (n->pred->left == n)
				{
					t->size--;
					n->pred->left = n->right;
					free(n);
					return 0;
				}
				else
				{
					t->size--;
					n->pred->right = n->right;
					free(n);
					return 0;
				}
			}
			else
			{
				t->size--;
				t->root = n->right;
				free(n);
				return 0;
			}
		}
		if ((n->left != NULL) && (n->right == NULL))// Åñëè ïðàâûé ïîòîìîê íóëåâîé
		{
			if (n->pred != NULL)
			{
				if (n->pred->left == n)
				{
					t->size--;
					n->pred->left = n->left;
					free(n);
					return 0;
				}
				else
				{
					t->size--;
					n->pred->right = n->left;
					free(n);
					return 0;
				}
			}
			else 
			{
				t->size--;
				t->root = n->left;
				free(n);
				return 0;
			}
		}
		if ((n->left != NULL) && (n->right != NULL)) //Åñëè åñòü äâà ïîòîìêà
		{
			node *max_left = n->right, *tmp=n->right->left;
			for(;;)
			{
				if (max_left->left != NULL)
				{
					max_left = max_left->left;
				}
				
				else break;
			}
			
				if (max_left->pred->left == n)
				{
					max_left->pred->left = max_left->right;
				}
				else if(max_left->pred->right == n)
				{
					max_left->pred->right = max_left->right;
				}
				
			if (n->pred != NULL)
			{
				max_left->pred = n->pred;
			}
			else 
			{
				t->root = max_left;
				max_left->pred = n->pred;
			}
			//max_left->right = n->right;
			max_left->left = n->left;
			//max_left->value = n->value;
			free(n);
			t->size--;
			return 0;

		}
		return 0;
	}
}


/* óäàëèòü ìèíèìàëüíûé ýëåìåíò èç ïîääåðåâà, êîðíåì êîòîðî
ãî ÿâëÿåòñÿ n. âåðíóòü çíà÷åíèå óäàëåííîãî ýëåìåíòà */
int removeMin(node* n) 
{
	int value;
	node *min=n, *tmp = n->left;
	while (tmp != NULL) 
	{
		min = tmp;
		tmp = tmp->left;
	}
	value = min->value;
	tree *tmp1=NULL; //ÂÍÈÌÀÍÈÅ ÊÎÑÒÛËÈ (íå çàáûòü â ðó÷íîì ðåæèìå èçìåòèòü size!!!!!)
	init(tmp1);
	tmp1->root = min;
	remove_(tmp1, value);
	return value;
}


/* âûïîëíèòü ïðàâîå âðàùåíèå ïîääåðåâà, êîðíåì êîòîðîãî ÿâ
ëÿåòñÿ n. âåðíóòü 0 ïðè óñïåùøíî âûïîëíåíèå îïåðàöèè è 1 â
ñëó÷àå åñëè âðàùåíèå íåâîçìîæíî */
int rotateRight(struct node* n) {
	if (n->left == NULL) {
		return 1;
	}
	struct node* tmp = n->left;
	if (n->pred != NULL) {
		if (n->pred->left == n) {
			n->pred->left = tmp;
		}
		else {
			n->pred->right = tmp;
		}
	}
	tmp->pred = n->pred;
	n->pred = tmp;
	struct node* t1 = tmp->right;
	tmp->right = n;
	n->left = t1;
	n = tmp;
	return 0;
}



/* âûïîëíèòü ëåâîå âðàùåíèå ïîääåðåâà, êîðíåì êîòîðîãî ÿâë
ÿåòñÿ n. âåðíóòü 0 ïðè óñïåùøíî âûïîëíåíèå îïåðàöèè è 1 â
ñëó÷àå åñëè âðàùåíèå íåâîçìîæíî */

int rotateLeft(struct node* n) {
	if (n->right == NULL) {
		return 1;
	}
	struct node* tmp = n->right;
	if (n->pred != NULL) {
		if (n->pred->right == n) {
			n->pred->right = tmp;
		}
		else {
			n->pred->left = tmp;
		}
	}
	tmp->pred = n->pred;
	n->pred = tmp;
	struct node* t1 = tmp->left;
	tmp->left = n;
	n->right = t1;
	n = tmp;
	return 0;
}



/* âûâåñòè âñå çíà÷åíèÿ èç ïîääåðåâà êîðíåì êîòîðîãî ÿâëÿå
òñÿ n ïî óðîâíåì, íà÷èíàÿ ñ êîðíÿ.êàæäûé óðîâåíü âûâîäèòñ
ÿ íà ñâîåé ñòðîêå.ýëåìåíòû â ñòðîêå ðàçäåëÿþòñÿ ïðîáåëîì.
åñëè íà óêàçàííîì ìåñòå íåò ýëåìåíòà, çàìåíèòü åãî çíà÷åí
èåì '_'.Åñëè äåðåâî ïóñòî âûâåñòè '-'*/


typedef struct node_list
{
	int value; // çíà÷åíèå, êîòîðîå õðàíèò óçåë
	struct node_list *next; // ññûëêà íà ñëåäóþùèé ýëåìåíò ñïèñêà
	struct node_list *prev; // ññûëêà íà ïðåäûäóùèé ýëåìåíò
}node_list;

typedef struct list
{
	struct node_list *head; // íà÷àëî ñïèñêà
	struct node_list *tail; // êîíåö ñïèñêà
}list;

void init1(list* l)
{
	l->head = NULL;
	l->tail = NULL;
}



void clear_list(list* l)
{
	while (l->head != NULL)
	{
		node_list *tmp = l->head;
		l->head = l->head->next;
		free(tmp);
	}
}
int push_back(list* l, int value)
{


	node_list *buf, *tmp;
	buf = l->tail;
	tmp = (node_list*)malloc(sizeof(node_list));
	tmp->next = NULL;
	tmp->prev = l->tail;
	tmp->value = value;
	l->tail = tmp;
	if (l->head == NULL)
	{
		l->head = tmp;
	}
	else
	{
		buf->next = tmp;
	}
	if (l->tail->value == value)
	{
		return 0;
	}
	return 1;
}

void copy_list(list *arr, list *arr1) //Èç arr â arr1
{
	node_list *tmp = arr->head;
	while (tmp != 0)
	{
		push_back(arr1, tmp->value);
		tmp = tmp->next;
	}

}
void zap(node*n, list *arr) 
{
	if (n->left != NULL)
	{
		push_back(arr, n->left->value);
	}
	else 
	{
		push_back(arr, 999);
	}
	if (n->right != NULL)
	{
		push_back(arr, n->right->value);
	}
	else
	{
		push_back(arr, 999);
	}

}


void print(node* n)
{
	tree *tmp_tree=(tree*)malloc(sizeof(tree));
	init(tmp_tree);
	tmp_tree->root = n; 
	list *arr = (list*)malloc(sizeof(list)), *arr1 = (list*)malloc(sizeof(list));
	init1(arr);
	init1(arr1);
	
	node *tmp = n, *tmp_node = (node*)malloc(sizeof(node)), *tmp1_node = (node*)malloc(sizeof(node));
	node_list *shet = arr->head, *buf_arr=arr->head;

	int t = 0, k = 1, step = 1;
	if (tmp == NULL)
	{
		printf("-\n");
	}
	else
	{
		printf("%d\n", n->value);
		zap(tmp, arr);
		while (k != 0)
		{
			shet = arr->head;
			buf_arr = arr->head;
			for (int i = 0; i < step * 2; i++) //Öèêë ïðîâåðêè
			{

				if (shet->value == 999)
				{
					t++;
				}
				shet = shet->next;
			}
			if (t == step * 2)
			{
				k = 0;
				break;
			}
			t = 0;
			
			for (int i = 0; i < step * 2; i++)
			{
				if (i != 0) printf(" ");
				if (buf_arr->value != 999)
				{
					printf("%d", buf_arr->value);
				}
				else
				{
					printf("_");
				}
				if (find(tmp_tree, buf_arr->value, &tmp_node) == 0) //Åñëè íàéäåí
				{
					zap(tmp_node, arr1);
				}
				else 
				{
					//tmp_node = NULL;
					tmp1_node->pred = NULL;
					tmp1_node->left = NULL;
					tmp1_node->right = NULL;
					zap(tmp1_node, arr1);
				}
							
				buf_arr = buf_arr->next;
			}
			printf("\n");
			clear_list(arr);
			copy_list(arr1, arr);
			clear_list(arr1);
			
			
			step = step * 2;
		}
		clear_list(arr);
		clear_list(arr1);
		free(tmp1_node);
	}
}

// âûâåñòè âñå çíà÷åíèÿ äåðåâà t, àíàëîãè÷íî ôóíêöèè print
void printTree(tree* t)
{
	if (t == NULL) 
	{
		printf("-\n");
	}
	else
	{
		node *f = t->root;
		print(f);
	}
}

int main() 
{
	tree *mytree=(tree*)malloc(sizeof(tree));
	init(mytree);
	int x;
	node *n= (node*)malloc(sizeof(node));
	
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &x);
		insert(mytree, x);
	}
	printTree(mytree); 

	
	//3
	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &x);
		insert(mytree, x);
	}
	printTree(mytree);
	//4
	int m1;
	scanf("%d", &m1);
	if (find(mytree, m1, &n) == 0) //ÍÀéäåí
	{
		if (n->pred != NULL)
		{
			printf("%d ", n->pred->value);
		}
		else
		{
			printf("_ ");//!!!!!!!!!!!
		}
		if (n->left != NULL)
		{
			printf("%d ", n->left->value);
		}
		else
		{
			printf("_ ");
		}
		if (n->right != NULL)
		{
			printf("%d\n", n->right->value);
		}
		else
		{
			printf("_\n");
		}
	}
	else 
	{
		printf("-\n");
	}

	//6
	int m2;
	scanf("%d", &m2);
	if (find(mytree, m2, &n) == 0) //ÍÀéäåí
	{
		if (n->pred != NULL)
		{
			printf("%d ", n->pred->value);
		}
		else
		{
			printf("_ ");//!!!!!!!!!!!
		}
		if (n->left != NULL)
		{
			printf("%d ", n->left->value);
		}
		else
		{
			printf("_ ");
		}
		if (n->right != NULL)
		{
			printf("%d\n", n->right->value);
		}
		else
		{
			printf("_\n");
		}
	}
	else
	{
		printf("-\n");
	}
	

	//7
	int m3;
	scanf("%d", &m3);
	remove_(mytree, m3);
	printTree(mytree);
	

	//9
	
	for (;;)
	{
		node *tmp = mytree->root->right;
		if (rotateLeft(mytree->root)) break;
		mytree->root = tmp;
	};
	
	//10
	printTree(mytree);

	//11
	for (;;)
	{
		node *tmp = mytree->root->left;
		if (rotateRight(mytree->root)) break;
		mytree->root = tmp;
	};
	//12
	printTree(mytree);

	//13
	printf("%d\n", mytree->size);
	
	//14
	clear(mytree);

	//15
	printTree(mytree);
	free(n);
	return 0;
}
