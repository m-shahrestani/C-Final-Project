#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

int n;

struct khoone
{
    int x,y;
    int type;
    int resource;
    int IsFull;
};

struct cell
{
    int x,y;
    char name[3];
    int Energy;
};

struct node
{
    struct cell Cell;
    struct node* next;
};

char *rand_string(size_t size);

struct node *create_node(struct cell n);

void add_end(struct node *list, struct node * new_node);

void print_list(struct node *list);


#endif // LINKEDLIST_H_INCLUDED
