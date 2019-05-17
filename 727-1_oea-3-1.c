#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int value; // çíà÷åíèå, êîòîðîå õðàíèò óçåë
		struct node *next; // ññûëêà íà ñëåäóþùèé ýëåìåíò ñïèñêà
}node;

typedef struct list
{
	struct node *head; // íà÷àëî ñïèñêà
	struct node *tail; // êîíåö ñïèñêà
}list;

// èíèöèàëèçàöèÿ ïóñòîãî ñïèñêà
void init(list* l) 
{
	l->head = NULL;
	l->tail = NULL;
}

//óäàëèòü âñå ýëåìåíòû èç ñïèñêà
void clear(list* l)
{
	while (l->head != NULL) 
	{
		node *tmp = l->head;
		l->head = l->head->next;
		free(tmp);
	}
}

// ïðîâåðêà íà ïóñòîòó ñïèñêà
int isEmpty(list* l)
{
	if((l->head == NULL) && (l->tail == NULL))
	{
		return 1;
	}
	else 
	{
		return 0;
	}

}

// ïîèñê ýëåìåíòà ïî çíà÷åíèþ. âåðíóòü NULL åñëè ýëåìåíò íå íàéäåí
node* find(list* l, int value) 
{
	int i = 0;
	node *tmp = (node*)malloc(sizeof(node));
	tmp = l->head;
	while (tmp != NULL)
	{
		if (tmp->value == value) 
		{
			i = 1;
			return tmp;
			break;
		}
		tmp = tmp->next;
	}
	if (i == 0) 
	{
		return NULL;
	}
}

// âñòàâêà çíà÷åíèÿ â êîíåö ñïèñêà, âåðíóòü 0 åñëè óñïåøíî
int push_back(list* l, int value)
{
	node *tmp = (node*)malloc(sizeof(node));
	tmp->value = value;
	tmp->next = NULL;
	if (l->tail == NULL) 
	{
		l->tail = tmp;
		l->head = tmp;
	}
	else
	{
		l->tail->next = tmp;
		l->tail = tmp;
	}
	return 0;
}

// âñòàâêà çíà÷åíèÿ â íà÷àëî ñïèñêà, âåðíóòü 0 åñëè óñïåøíî
int push_front(list* l, int value) 
{
	node *tmp = (node*)malloc(sizeof(node));
	tmp->value = value;
	tmp->next = l->head;
	l->head = tmp;
	return 0;
}

// âñòàâêà çíà÷åíèÿ ïîñëå óêàçàííîãî óçëà, âåðíóòü 0 åñëèóñïåøíî
int insertAfter(node* n, int value) 
{
	node *tmp = (node*)malloc(sizeof(node));
	tmp->value = value;
	tmp->next = n->next;
	n->next = tmp;
	return 0;
}

// óäàëèòü ïåðâûé ýëåìåíò èç ñïèñêà ñ óêàçàííûì çíà÷åíèåì,âåðíóòü 0 åñëè óñïåøíî
int remove1(list* l, int value) 
{
	node *tmp1 = (node*)malloc(sizeof(node));
	node *tmp2 = (node*)malloc(sizeof(node));
	tmp1 = find(l, value);
	tmp2 = l->head;
	if (tmp1 != NULL) 
	{
		while (tmp2->next != tmp1) 
		{
			tmp2 = tmp2->next;
		}
		tmp2->next = tmp1->next;
		free(tmp1);
		return 0;
	}
}

// âûâåñòè âñå çíà÷åíèÿ èç ñïèñêà â ïðÿìîì ïîðÿäêå, ÷åðåç ïðîáåë, ïîñëå îêîí÷àíèÿ âûâîäà ïåðåéòè íà íîâóþ ñòðîêó
void print(list* l)
{
	node *tmp = (node*)malloc(sizeof(node));
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


int main() 
{
	
	unsigned int j;
	int n, a,k,m,t,z,x;
	
	scanf("%d", &n);
	list l;
	init(&l);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &a);
		push_back( &l, a);
	}
	print(&l);
	for (int i = 0; i < 3; ++i) 
	{
		scanf("%d", &k);
		if (find(&l, k) == NULL) 
		{
			printf("0");
		}
		else 
		{
			printf("1");
		}

	}
	printf("\n");
	scanf("%d", &m);
	push_back(&l, m);
	print(&l);

	scanf("%d", &t);
	push_front(&l, t);
	print(&l);

	list *p = &l;
	node *tmp = (node*)malloc(sizeof(node));
	tmp =p->head;
	scanf("%u%d", &j,&x);//!!
	for (int i = 0; i < j-1; ++i) 
	{
		tmp = tmp->next;
	}
	insertAfter(tmp, x);
	print(&l);

	scanf("%d", &z);
	remove1(&l, z);
	print(&l);
	clear(&l);
	return 0;
}
