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
    PlaySound(TEXT("sounds\\pacman_intermission.wav"),0,SND_ASYNC);
    FILE *fp;
    struct khoone **mapscopy;
    //tarif araye dobodi
    mapscopy = (struct khoone **)malloc(n*sizeof(struct khoone *));
    for(int i = 0; i < n; i++)
    {
        mapscopy[i] = (struct khoone*)malloc(n*sizeof(struct khoone));
    }
    fp=fopen("savemaps.bin","rb");
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
    int ncell,p;
    FILE *fp;
    fp=fopen("savecell.bin","rb");
    fread(&n2cell,sizeof(int),1,fp);
    fread(&players,sizeof(int),1,fp);
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
            PlaySound(TEXT("sounds\\pacman_chomp.wav"),0,SND_ASYNC);
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
    gotoxy(0,n*3+3);
    textcolor(15);
	printf("[1]North\n");
	printf("[2]South\n");
	printf("[3]Northeast\n");
	printf("[4]Northwest\n");
	printf("[5]Southeast\n");
	printf("[6]Southwest\n");
    int code = 0;
    scanf("%d",&code);
    if(code<1||code>6)
        return;
    switch(code)
    {
        case 1:
            if((cur->Cell.y)+1<n&& maps[(cur->Cell.x)][(cur->Cell.y)+1].type!=3&&maps[(cur->Cell.x)][(cur->Cell.y)+1].IsFull==0)
            {
                maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                maps[(cur->Cell.x)][(cur->Cell.y)+1].IsFull=1;
                cur->Cell.y++;
                PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
            }
        break;
        case 2:
            if(0<=(cur->Cell.y)-1&& maps[(cur->Cell.x)][(cur->Cell.y)-1].type!=3&&maps[(cur->Cell.x)][(cur->Cell.y)-1].IsFull==0)
            {
                maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                maps[(cur->Cell.x)][(cur->Cell.y)-1].IsFull=1;
                cur->Cell.y--;
                PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
                }
            }
            else
            {
                if(0<=(cur->Cell.x)-1 && maps[(cur->Cell.x)-1][(cur->Cell.y)].type!=3 && maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull==0)
                {
                    maps[(cur->Cell.x)][(cur->Cell.y)].IsFull=0;
                    maps[(cur->Cell.x)-1][(cur->Cell.y)].IsFull=1;
                    cur->Cell.x--;
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
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
                    PlaySound(TEXT("sounds\\pacman_eatfruit.wav"),0,SND_ASYNC);
                }
            }
        break;
    }
}

void boost(struct node *cur, struct khoone **maps)
{
    if(maps[cur->Cell.x][cur->Cell.y].resource!=0)
    {
        PlaySound(TEXT("sounds\\pacman_eatghost.wav"),0,SND_ASYNC);
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
        int x=(cur->Cell.x);
        int y=(cur->Cell.y);
        while(1)
        {
            a=(rand()%3)-1;
            b=(rand()%3)-1;
            if((0<=x+a)&&(x+a)<n&&0<=(y+b)&&(y+b)<n)
            {
                if((x%2==0&&((a==0&&b==1)||(a==0&&b==-1)||(a==1&&b==1)||(a==1&&b==0)||(a==-1&&b==1)||(a==-1&&b==0)))||(x%2!=0&&((a==0&&b==1)||(a==0&&b==-1)||(a==1&&b==0)||(a==1&&b==-1)||(a==-1&&b==0)||(a==-1&&b==-1))))
                {
                    if(maps[x+a][y+b].IsFull == 0&&maps[x+a][y+b].type !=3)
                    {
                        maps[x+a][y+b].IsFull=1;
                        t.x=x+a;
                        t.y=y+b;
                        t.Energy=40;
                        strcpy(t.name, rand_string(3));
                        add_end(head,create_node(t));
                        cur->Cell.Energy-=40;
                        PlaySound(TEXT("sounds\\pacman_death.wav"),0,SND_ASYNC);
                        break;
                    }
                }
                if((x%2==0&&(maps[x+0][y+1].IsFull!=0&&maps[x+0][y-1].IsFull!=0
                                      &&maps[x+1][y+1].IsFull!=0&&maps[x+1][y+0].IsFull!=0
                                      &&maps[x-1][y+1].IsFull!=0&&maps[x-1][y+0].IsFull!=0))
                ||(x%2!=0&&(maps[x+0][y+1].IsFull!=0&&maps[x+0][y-1].IsFull!=0
                                    &&maps[x+1][y+0].IsFull!=0&&maps[x+1][y-1].IsFull!=0
                                    &&maps[x-1][y+0].IsFull!=0&&maps[x-1][y-1].IsFull!=0)))
                {
                       break;
                }
            }
        }


//        (maps[x+a][y+b].IsFull == 1&&(((x%2==0)&&((a==0&&b==1)&&(a==0&&b==-1)&&(a==1&&b==1)&&(a==1&&b==0)&&(a==-1&&b==1)&&(a==-1&&b==0)))||((x%2!=0)&&((a==0&&b==1)&&(a==0&&b==-1)&&(a==1&&b==0)&&(a==1&&b==-1)&&(a==-1&&b==0)&&(a==-1&&b==-1)))))

    }
}

void savemaps(struct khoone **maps)
{
    FILE *fp;
    fp=fopen("savemaps.bin","wb");
    for(int i=0;i<n;i++)
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
    fwrite(&n2cell,sizeof(int),1,fp);
    fwrite(&players,sizeof(int),1,fp);
	fwrite(&ncell,sizeof(int),1,fp);
	for(current = head; current != NULL; current = current->next)
	{
        fwrite(&(current->Cell),sizeof(struct cell),1,fp);
    }
    fclose(fp);
}
