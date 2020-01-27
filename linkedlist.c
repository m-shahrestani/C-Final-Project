#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"


char *rand_string(size_t size)
{ // reserves a place for NULL
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(size_t i = 0; i < size; i++)
        {
            int key = rand() % (sizeof(charset) / sizeof(char) - 1);
            str[i] = charset[key];
        }
    str[size] = '\0';
    return str;
}

struct node *create_node(struct cell n)
{
	struct node *p;
	p = (struct node *) malloc(sizeof(struct node));
	if (p == NULL)
		return NULL;
	p->Cell = n;
	p->next = NULL;
	return p;
}

void add_end(struct node *list, struct node * new_node){
	struct node *current;
	for(current = list; current-> next != NULL; current = current->next);
	current->next = new_node;
	new_node->next = NULL;
}

//void remove_node(struct node** list, struct cell t)
//{
//	struct node *cur,*temp;
//	cur=*list;
//	if((cur->Cell).name==t.name)
//	{
//		*list=(*list)->next;
//		printf("%s has been removed\n",t.name);
//		free(cur);
//		return;
//	}
//	cur=*list;
//	while(cur->next!=NULL)
//	{
//		if(cur->next->Cell.name!=t.name)
//		{
//			cur=cur->next;
//		}
//		else
//		{
//			temp=cur->next;
//			cur->next=cur->next->next;
//			free(temp);
//			printf("%s has been removed\n",t.name);
//			return;
//		}
//	}
//	printf("%s does not exist\n",t.name);
//}
//
//void print_list(struct node *list){
//    struct node * current = list;
//    int i=1;
//    while(current != NULL)
//	{
//        printf("%s \n",current->Cell.name);
//        current = current->next;
//        i++;
//    }
//}
