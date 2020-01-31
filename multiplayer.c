#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include "linkedlist.h"
#include "show.h"
#include "multiplayer.h"

void main_menu2(struct node* head,struct khoone **maps,struct node* head2)
{
    gotoxy(0,n*3+3);
    textcolor(15);
	printf("[1]Move\n");
	printf("[2]Split a cell\n");
	printf("[3]Boost energy\n");
	printf("[4]Save\n");
	printf("[5]Exit\n");
    int code=0;
    int code1=0;
	struct node *current;
    scanf("%d",&code);
    if(code<1||code>5)
        return;
    switch(code)
    {
        case 1:
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            print_list(head);
            scanf("%d",&code1);
            int i=1;
            for(current = head;i<code1; current = current->next)
            {
                i++;
            }
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            move_menu(current,maps);
        break;
        case 2:
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            print_list(head);
            scanf("%d",&code1);
            i=1;
            for(current = head;i<code1; current = current->next)
            {
                i++;
            }
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            split(current,head,maps);
        break;
        case 3:
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            print_list(head);
            scanf("%d",&code1);
            i=1;
            for(current = head;i<code1; current = current->next)
            {
                i++;
            }
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            boost(current,maps);
        break;
        case 4:
            system("cls");
            show_map(maps);
            textcolor(15);
            show_cell(head);
            textcolor(0);
            show_cell(head2);
            textcolor(15);
            gotoxy(0,n*3+2);
            savemaps(maps);
            savecell(head);
            savecell2(head2);
            PlaySound(TEXT("sounds\\pacman_chomp.wav"),0,SND_ASYNC);
            printf("Game has been saved.");
            Sleep(1000);
        break;
        case 5:
            exit(0);
        break;
    }
}

void savecell2(struct node* head)
{
    int ncell=1;
    FILE *fp;
	struct node *current;
	for(current = head; current->next != NULL; current = current->next)
	{
	    ncell++;

	}
	fp=fopen("savecell2.bin","wb");
	fwrite(&ncell,sizeof(int),1,fp);
	for(current = head; current != NULL; current = current->next)
	{
        fwrite(&(current->Cell),sizeof(struct cell),1,fp);
    }
    fclose(fp);
}

struct node* loadcell2(void)
{
    int ncell;
    FILE *fp;
    fp=fopen("savecell2.bin","rb");
    fread(&ncell,sizeof(int),1,fp);
    struct node *head;
    struct cell t;
    fread(&t,sizeof(struct cell),1,fp);
    head = create_node(t);
    for(int i=1;i<ncell;i++)
    {
        fread(&t,sizeof(struct cell),1,fp);
        add_end(head,create_node(t));
    }
    fclose(fp);
    return head;
}
