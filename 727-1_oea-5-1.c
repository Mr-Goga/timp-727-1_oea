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
int push_front(struct list* l, int value)
{
	node_list *buf, *tmp;
	buf = l->head;
	tmp = (node_list*)malloc(sizeof(node_list));
	tmp->next = buf;
	tmp->prev = NULL;
	tmp->value = value;
	l->head = tmp;
	if (l->tail == NULL)
	{
		l->tail = tmp;
	}
	else
	{
		buf->prev = tmp;
	}

	if (l->head->value == value)
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
void print_list(list* l)
{
	node_list *tmp = (node_list*)malloc(sizeof(node_list));
	tmp = l->head;
	while (tmp != NULL)
	{
		printf("%d", tmp->value);
		if (tmp->next != NULL)
		{
			printf(" ");
			tmp = tmp->next;
		}
		else
		{
			printf("\n");
			break;
		}
	}
	tmp = NULL;
	free(tmp);
}
void movement_width(tree* t) // Îáõîä äåðåâà â øèðèíó
{
	node *n = t->root;
	list *arr = (list*)malloc(sizeof(list));
	init1(arr);
	node  *tmp_node = (node*)malloc(sizeof(node));
	
	if (n != NULL)
	{
		push_back(arr, n->value);
		if (n->left != NULL)
		{
			push_back(arr, n->left->value);
		}
		if (n->right != NULL)
		{
			push_back(arr, n->right->value);
		}
	}
	node_list *buf_arr = arr->head->next;
	while(buf_arr!=NULL)
	{
		
		find(t, buf_arr->value, &tmp_node);
			if (tmp_node != NULL)
			{
				if (tmp_node->left != NULL)
				{
					push_back(arr, tmp_node->left->value);
				}
				if (tmp_node->right != NULL)
				{
					push_back(arr, tmp_node->right->value);
				}
			}
			buf_arr = buf_arr->next;
	}
	print_list(arr);
	clear_list(arr);
	tmp_node = NULL;
	free(tmp_node);
	free(arr);
}
int main() 
{
	tree *mytree=(tree*)malloc(sizeof(tree));
	init(mytree);
	int x;
	for (int i = 0; i < 7; ++i) 
	{
		scanf("%d", &x);
		insert(mytree, x);
	}
	movement_width(mytree);
	clear(mytree);
	return 0;
}
