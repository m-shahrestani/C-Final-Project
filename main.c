#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include "show.h"
#include "linkedlist.h"

struct khoone** load_map(void)
{
    FILE* fp=fopen("map6.bin","rb");
    fread(&n,sizeof(int),1,fp);
    struct khoone **maps;
    //tarif araye dobodi
    maps = (struct khoone **)malloc(n*sizeof(struct khoone *));
    for(int i = 0; i < n; i++)
    {
        maps[i] = (struct khoone *)malloc(n*sizeof(struct khoone));
    }
    //rikhtan map dar araye
    for(int i=0;i< n ;i++)
    {
        for(int j=0;j<n;j++)
        {
            char c=fgetc(fp);
            maps[i][j].x=i;
            maps[i][j].y=j;
            maps[i][j].type=c-'0';
            maps[i][j].resource=0;
            if(maps[i][j].type==1)
            {
                maps[i][j].resource=100;
            }
            maps[i][j].IsFull=0;
        }
    }
    return maps;
}

void show_map(struct khoone **maps)
{
    int a[3 * n + 1][5 * n];
    for(int i = 0; i <= 3 * n; i ++)
        for(int j = 0; j < 5 * n; j ++)
            a[i][j] = 0;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
        {
            if(j % 2 == 0)
            {
                for(int k = 3 * i; k < 3 * i + 3; k ++)
                    for(int t = 5 * j; t < 5 * j + 5; t ++)
                    {
                        if(i % 2 == 0)
                            a[k][t] = 112;
                        else
                            a[k][t] = 48;
                    }
            }
            else
            {
                for(int k = 3 * i + 1; k <= 3 * i + 3; k ++)
                    for(int t = 5 * j; t < 5 * j + 5; t ++)
                    {
                        if(i % 2 == 0)
                            a[k][t] = 240;
                        else
                            a[k][t] = 128;
                    }
            }
        }
    for(int i = 0; i <= 3 * n; i ++)
    {
        for(int j = 0; j < 5 * n; j ++)
        {
            textcolor(a[i][j]);
            printf("  ");
        }
        printf("\n");
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i%2==0)
            {
                gotoxy(10*i,3*((n-1)-j));
                if(maps[i][j].type==1)
                {
                    textcolor(47);
                    printf("E-%d",maps[i][j].resource);
                }
                if(maps[i][j].type==2)
                {
                    textcolor(95);
                    printf("M");
                }
                if(maps[i][j].type==3)
                {
                    textcolor(207);
                    printf("F");
                }
            }
            if(i%2!=0)
            {
                gotoxy(10*i,3*((n-1)-j)+1);
                if(maps[i][j].type==1)
                {
                    textcolor(47);
                    printf("E-%d",maps[i][j].resource);
                }
                if(maps[i][j].type==2)
                {
                    textcolor(95);
                    printf("M");
                }
                if(maps[i][j].type==3)
                {
                    textcolor(207);
                    printf("F");
                }
            }
        }
    }
}

struct node*  first_menu(struct khoone **maps)
{
    system("CLS");
	printf("[1]Load\n");
	printf("[2]New single player game\n");
	printf("[3]New Multiplayer game\n");
	printf("[4]New single player game with PC\n");
	printf("[5]Map editor\n");
	printf("[6]Map convert to text file\n");
	printf("[7]Exit\n");
    int code=0;
    scanf("%d",&code);
    int ncell=0;
    switch(code)
    {
        case 1:
            loadmaps(maps);
            return loadcell();
        break;
        case 2:
            printf("Enter number of cells.");
            scanf("%d",&ncell);
            return new_cell(ncell,maps);

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        case 6:

        break;
        case 7:
            exit(0);
        break;
    }
}

/*print map
    for(int i=0;i< n ;i++)
   {
        for(int j=0;j<n;j++)
        {
          printf("x= %d ,y= %d ,type= %d ,resource= %d, IsFull= %d \n",maps[i][j].x,maps[i][j].y,maps[i][j].type,maps[i][j].resource,maps[i][j].IsFull);
        }
   }
*/
int main()
{
    srand(time(0));
    textcolor(10);
    struct khoone **maps=load_map();
    show_map(maps);
    struct node* head=first_menu(maps);
 //   struct node* head2=first_menu(maps);
    while(1)
    {
        system("cls");
        show_map(maps);
        show_cell(head);
        gotoxy(0,n*3+2);
        main_menu(head,maps);
    }
    getch();
    return 0;
}
