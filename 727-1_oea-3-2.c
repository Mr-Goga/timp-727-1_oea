#include<stdlib.h>
#include<stdio.h>
typedef struct node
{
	int value; // çíà÷åíèå, êîòîðîå õðàíèò óçåë
	struct node *next; // ññûëêà íà ñëåäóþùèé ýëåìåíò ñïèñêà
		struct node *prev; // ññûëêà íà ïðåäûäóùèé ýëåìåíò
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
	if ((l->head == NULL) && (l->tail == NULL))
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
	
		
		node *buf,*tmp;
		buf = l->tail;
		tmp = (node*)malloc(sizeof(node));
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

// âñòàâêà çíà÷åíèÿ â íà÷àëî ñïèñêà, âåðíóòü 0 åñëè óñïåøíî
int push_front(struct list* l, int value)
{
		node *buf, *tmp;
		buf = l->head;
		tmp = (node*)malloc(sizeof(node));
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

// âñòàâêà çíà÷åíèÿ ïîñëå óêàçàííîãî óçëà, âåðíóòü 0 åñëèóñïåøíî
int insertAfter(struct list* l, int position, int value)
{
	node *buf, *sec,*tmp;
	buf = l->head;
	if (buf == NULL)
	{
		return 1;
	}
	for (int i = 1; i < position; i++)
	{
		if (buf->next == NULL)
		{
			return 1;
		}
		buf = buf->next;
	}
	sec = buf->next;
	
	tmp = (node*)malloc(sizeof(node));
	tmp->next = sec;
	tmp->prev = buf;
	tmp->value = value;
	buf->next = tmp;
	if (sec != NULL)
	{
		sec->prev = tmp;
	}
	if (l->tail == buf)
	{
		l->tail = tmp;
	}
	if (buf->next->value == value)
	{
		return 0;
	}
	return 1;
}

// âñòàâêà çíà÷åíèÿ ïåðåä óêàçàííûì óçëîì, âåðíóòü 0 åñëè óñïåøíî
int insertBefore(struct list* l, int position, int value)
{
	node *buf, *pre,*tmp;
	buf = l->head;
	if (buf == NULL)
	{
		return 1;
	}
	for (int i = 1; i < position; i++)
	{
		if (buf->next == NULL)
		{
			return 1;
		}
		buf = buf->next;
	}
	pre = buf->prev;
	tmp = (node*)malloc(sizeof(node));
	tmp->next = buf;
	tmp->prev = pre;
	tmp->value = value;
	buf->prev = tmp;
	if (pre != NULL)
	{
		pre->next = tmp;
	}
	if (l->head == pre)
	{
		l->head = tmp;
	}
	if (buf->prev->value == value)
	{
		return 0;
	}
	return 1;
}

// óäàëèòü ïåðâûé ýëåìåíò èç ñïèñêà ñ óêàçàííûì çíà÷åíèåì,âåðíóòü 0 åñëè óñïåøíî
int removeFirst(list* l, int value)
{
node *buf, *sec, *pre;
    buf = l->head;
    pre = NULL;
    if(buf == NULL)
        {
            return 1;
        }
    while (buf->value != value)
    {
        if(buf->next == NULL)
        {
            return 1;
        }
        pre = buf;
        buf = buf->next;
    }
    sec = buf->next;
    free(buf);
    if(pre == NULL)
    {
        l->head = sec;
    }
    else
    {
        pre->next = sec;
    }
    if(sec == NULL)
    {
        l->tail = pre;
    }
    else
    {
        sec->prev = pre;
    }
    return 0;
}

int removeLast(struct list* l, int value)
{
	node *buf, *sec, *pre;
	buf = l->tail;
	sec = NULL;
	if (buf == NULL)
	{
		return 1;
	}
	while (buf->value != value)
	{
		if (buf->prev == NULL)
		{
			return 1;
		}
		sec = buf;
		buf = buf->prev;
	}
	pre = buf->prev;
	free(buf);
	if (pre == NULL)
	{
		l->head = sec;
	}
	else
	{
		pre->next = sec;
	}
	if (sec == NULL)
	{
		l->tail = pre;
	}
	else
	{
		sec->prev = pre;
	}
	return 0;
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

void print_invers(struct list* l)
{
	node *tmp = (node*)malloc(sizeof(node));
	tmp = l->tail;
	while (tmp != NULL)
	{
		printf("%d", tmp->value);
		if (tmp->prev != NULL)
		{
			printf(" ");
			tmp = tmp->prev;
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
	list *l;
	l = (list*)malloc(sizeof(list));

	init(l);

	int n, x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		push_back(l, x);
	}
	print(l);
	//3
	int k1, k2, k3;
	scanf("%d%d%d", &k1, &k2, &k3);
	if (find(l, k1) != NULL)
	{
		printf("%d", 1);
	}
	else { printf("%d", 0); }
	if (find(l, k2) != NULL)
	{
		printf("%d", 1);
	}
	else { printf("%d", 0); }
	if (find(l, k3) != NULL)
	{
		printf("%d\n", 1);
	}
	else { printf("%d\n", 0); }
	//5
	int m;
	scanf("%d", &m);
	push_back(l, m);
	print_invers(l);
	//7
	int t;
	scanf("%d", &t);
	push_front(l, t);
	print(l);
	//9
	int j;
	scanf("%d%d", &j, &x);
	insertAfter(l, j, x);
	print_invers(l);
	//11
	int u, y;
	scanf("%d%d", &u, &y);
	insertBefore(l, u, y);
	print(l);
	//13
	int z;
	scanf("%d", &z);
	removeFirst(l, z);
	print_invers(l);
	//15
	int r;
	scanf("%d", &z);
	removeLast(l, z);
	print(l);
	//17
	clear(l);
	
	return 0;
}
