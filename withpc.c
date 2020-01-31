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
#include "withpc.h"

void main_menu3(struct node* head,struct khoone **maps,struct node* head2,int n2cell)
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
	int t=(1+rand()%100);
	if(t<=70)
        code=1;
    if(75<t&&t<=80)
        code=2;
    if(80<t&&t<=100)
        code =3;
    Sleep(1000);
    printf("%d",code);
    Sleep(2000);
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
            code1=1+rand()%n2cell;
            Sleep(1000);
            printf("%d",code1);
            Sleep(2000);
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
            move_menu3(current,maps);
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
            code1=1+rand()%n2cell;
            Sleep(1000);
            printf("%d",code1);
            Sleep(2000);
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
            code1=1+rand()%n2cell;
            Sleep(1000);
            printf("%d",code1);
            Sleep(2000);
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

void move_menu3(struct node* cur,struct khoone **maps)
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
	code=1+rand()%6;
    Sleep(1000);
    printf("%d",code);
    Sleep(2000);
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

