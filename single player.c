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

struct cell randomcell(struct khoone** maps)
{
    struct cell t;
    int a,b;
    t.Energy=0;
    strcpy(t.name, rand_string(3));
    while(1)
    {
        a=rand()%n;
        b=rand()%n;
        if(maps[a][b].IsFull == 0&&maps[a][b].type !=3)
        {
            maps[a][b].IsFull=1;
            break;
        }
    }
    t.x=a;
    t.y=b;
    return t;
}
struct node* new_cell(int ncell,struct khoone **maps)
{
        struct node *cells;
        struct cell t;
        t=randomcell(maps);
        cells = create_node(t);
        for(int i=1;i<ncell;i++)
        {
            t=randomcell(maps);
            add_end(cells,create_node(t));
        }
        return cells;
}

void show_cell(struct node* head)
{
    struct node* curr=head;
    while(curr!=NULL)
    {
        int i=curr->Cell.x;
        int j=curr->Cell.y;
        if(i%2==0)
        {
            gotoxy(10*i+2,3*((n-1)-j)+1);
        }
        if(i%2!=0)
        {
            gotoxy(10*i+2,3*((n-1)-j)+1+1);
        }
        printf("%s-%d",curr->Cell.name,curr->Cell.Energy);
        curr=curr->next;
    }
}

void loadmaps(struct khoone **maps)
{
    FILE *fp;
    struct khoone **mapscopy;
    //tarif araye dobodi
    mapscopy = (struct khoone **)malloc(n*sizeof(struct khoone *));
    for(int i = 0; i < n; i++)
    {
        mapscopy[i] = (struct khoone*)malloc(n*sizeof(struct khoone));
    }
    fp=fopen("savemaps.bin","rb");
    if(fp == NULL)
    {
        printf("Cannot find savemaps file.\n");
        return -1;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fread(&mapscopy[i][j],sizeof(struct khoone),1,fp);
        }
    }
    fclose(fp);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            maps[i][j]=mapscopy[i][j];
        }
    }
}

struct node* loadcell(void)
{
    int ncell;
    FILE *fp;
    fp=fopen("savecell.bin","rb");
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

void main_menu(struct node* head,struct khoone **maps)
{
	printf("[1]Move\n");
	printf("[2]Split a cell\n");
	printf("[3]Boost energy\n");
	printf("[4]Save\n");
	printf("[5]Exit\n");
    int code=0;
    int code1=0;
	struct node *current;
    scanf("%d",&code);
    switch(code)
    {
        case 1:
            system("cls");
            show_map(maps);
            show_cell(head);
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
            show_cell(head);
            gotoxy(0,n*3+2);
            move_menu(current,maps);
        break;
        case 2:
            system("cls");
            show_map(maps);
            show_cell(head);
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
            show_cell(head);
            gotoxy(0,n*3+2);
            split(current,head,maps);
        break;
        case 3:
            system("cls");
            show_map(maps);
            show_cell(head);
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
            show_cell(head);
            gotoxy(0,n*3+2);
            boost(current,maps);
        break;
        case 4:
            system("cls");
            show_map(maps);
            show_cell(head);
            gotoxy(0,n*3+2);
            savemaps(maps);
            savecell(head);
            printf("Game has been saved.");
            Sleep(1000);
        break;
        case 5:
            exit(0);
        break;
    }
}

void move_menu(struct node* cur,struct khoone **maps)
{
	printf("[1]North\n");
	printf("[2]South\n");
	printf("[3]Northeast\n");
	printf("[4]Northwest\n");
	printf("[5]Southeast\n");
	printf("[6]Southwest\n");
    int code = 0;
    scanf("%d",&code);
    switch(code)
    {
        case 1:
            if((cur->Cell.y)+1<n&& maps[(cur->Cell.x)][(cur->Cell.y)+1].type!=3&&maps[(cur->Cell.x)][(cur->Cell.y)+1].IsFull==0)
            {
                maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                maps[(cur->Cell.x)][(cur->Cell.y)+1].IsFull=1;
                cur->Cell.y++;

            }
        break;
        case 2:
            if(0<=(cur->Cell.y)-1&& maps[(cur->Cell.x)][(cur->Cell.y)-1].type!=3&&maps[(cur->Cell.x)][(cur->Cell.y)-1].IsFull==0)
            {
                maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                maps[(cur->Cell.x)][(cur->Cell.y)-1].IsFull=1;
                cur->Cell.y--;
            }
        break;
        case 3:
            if((cur->Cell.x)%2==0)
            {
                if((cur->Cell.x)+1<n && (cur->Cell.y)+1<n && maps[(cur->Cell.x)+1][(cur->Cell.y)+1].type!=3 && maps[(cur->Cell.x)+1][(cur->Cell.y)+1].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)+1][(cur->Cell.y)+1].IsFull=1;
                    cur->Cell.x++;
                    cur->Cell.y++;
                }
            }
            else
            {
                if((cur->Cell.x)+1<n && maps[(cur->Cell.x)+1][(cur->Cell.y)].type!=3 && maps[(cur->Cell.x)+1][(cur->Cell.y)].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)+1][(cur->Cell.y)].IsFull=1;
                    cur->Cell.x++;
                    cur->Cell.y;
                }
            }
        break;
        case 4:
            if((cur->Cell.x)%2==0)
            {
                if(0<=(cur->Cell.x)-1 && (cur->Cell.y)+1<n && maps[(cur->Cell.x)-1][(cur->Cell.y)+1].type!=3 && maps[(cur->Cell.x)-1][(cur->Cell.y)+1].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)-1][(cur->Cell.y)+1].IsFull=1;
                    cur->Cell.x--;
                    cur->Cell.y++;
                }
            }
            else
            {
                if(0<=(cur->Cell.x)-1 && maps[(cur->Cell.x)-1][(cur->Cell.y)].type!=3 && maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull=1;
                    cur->Cell.x--;
                }
            }
        break;
        case 5:
            if((cur->Cell.x)%2==0)
            {
                if((cur->Cell.x)+1<n && maps[(cur->Cell.x)+1][(cur->Cell.y)].type!=3 && maps[(cur->Cell.x)+1][(cur->Cell.y)].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)+1][(cur->Cell.y)].IsFull=1;
                    cur->Cell.x++;
                }
            }
            else
            {
                if((cur->Cell.x)+1<n && 0<=(cur->Cell.y)-1 && maps[(cur->Cell.x)+1][(cur->Cell.y)-1].type!=3 && maps[(cur->Cell.x)+1][(cur->Cell.y)-1].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)+1][(cur->Cell.y)-1].IsFull=1;
                    cur->Cell.x++;
                    cur->Cell.y--;
                }
            }
        break;
        case 6:
            if((cur->Cell.x)%2==0)
            {
                if(0<=(cur->Cell.x)-1 && maps[(cur->Cell.x)-1][(cur->Cell.y)].type!=3 && maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull=1;
                    cur->Cell.x--;
                }
            }
            else
            {
                if(0<=(cur->Cell.x)-1 && 0<=(cur->Cell.y)-1 && maps[(cur->Cell.x)-1][(cur->Cell.y)-1].type!=3 && maps[(cur->Cell.x)-1][(cur->Cell.y)-1].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)-1][(cur->Cell.y)-1].IsFull=1;
                    cur->Cell.x--;
                    cur->Cell.y--;
                }
            }
        break;
    }
}

void boost(struct node *cur, struct khoone **maps)
{
    if(maps[cur->Cell.x][cur->Cell.y].resource!=0)
    {
        if(maps[cur->Cell.x][cur->Cell.y].resource>=15)
        {
            maps[cur->Cell.x][cur->Cell.y].resource-=15;
            cur->Cell.Energy+=15;
        }
        else
        {
            cur->Cell.Energy+=(maps[cur->Cell.x][cur->Cell.y].resource);
            maps[cur->Cell.x][cur->Cell.y].resource=0;
        }
        if(cur->Cell.Energy>100)
        {
            maps[cur->Cell.x][cur->Cell.y].resource+=cur->Cell.Energy-100;
            cur->Cell.Energy=100;
        }
    }
}

void split(struct node *cur,struct node *head,struct khoone **maps)
{
    if(cur->Cell.Energy>=80&&maps[cur->Cell.x][cur->Cell.y].type==2)
    {
        int a,b;
        struct cell t;
        int found =0;
        for(int i=-1; i<2; i++)
        {
            for(int j=-1; j<2; j++)
            {
                a=(cur->Cell.x)+i;
                b=(cur->Cell.y)+j;
                if( (a>= 0 && a<=n-1 && b>= 0 && b<=n-1 ) == 0)
                    continue;
                if(maps[a][b].IsFull == 0&&maps[a][b].type !=3)
                {
                    maps[a][b].IsFull=1;
                    found=1;
                    break;
                }
            }
        }
        if(!found)
        {
            Sleep(1000);
            printf("Impossible.");
            return;
        }
        t.x=a;
        t.y=b;
        t.Energy=40;
        strcpy(t.name, rand_string(3));
        add_end(head,create_node(t));
        cur->Cell.Energy-=40;
    }
}

void savemaps(struct khoone **maps)
{
    FILE *fp;
    fp=fopen("savemaps.bin","wb");
    if(fp == NULL)
    {
        printf("Cannot make savemaps file.\n");
        return -1;
    }
    for(int i=0;i<n;i++)//deghat kon
    {
        for(int j=0;j<n;j++)
        fwrite(&maps[i][j],sizeof(struct khoone),1,fp);
    }
    fclose(fp);
}

void savecell(struct node* head)
{
    int ncell=1;
    FILE *fp;
	struct node *current;
	for(current = head; current->next != NULL; current = current->next)
	{
	    ncell++;

	}
	fp=fopen("savecell.bin","wb");
	fwrite(&ncell,sizeof(int),1,fp);
	for(current = head; current != NULL; current = current->next)
	{
        fwrite(&(current->Cell),sizeof(struct cell),1,fp);
    }
    fclose(fp);
}
