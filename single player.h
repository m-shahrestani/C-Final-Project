#ifndef SINGLE_PLAYER_H_INCLUDED
#define SINGLE_PLAYER_H_INCLUDED

struct cell randomcell(struct khoone** maps);

struct node* new_cell(int ncell,struct khoone **maps);

struct node* loadcell(void);

void show_cell(struct node* head);

void loadmaps(struct khoone **maps);

void main_menu(struct node* head,struct khoone **maps);

void move_menu(struct node* cur,struct khoone **maps);

void boost(struct node *cur, struct khoone **maps);

void split(struct node *cur,struct node *head,struct khoone **maps);

void savemaps(struct khoone **maps);

void savecell(struct node* head);

#endif // SINGLE_PLAYER_H_INCLUDED
