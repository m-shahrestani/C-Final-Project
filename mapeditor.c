#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "mapeditor.h"
#include "linkedlist.h"

void makemap(void)
{
    int m,code;
    char str[20];
    printf("[1]Making map\n[2]Edit Map\n");
    scanf("%d",&code);
    if(code==1)
    {
        printf("Enter name of map:");
        scanf("%s",&str);
        strcat(str,".bin");
        printf("Enter n:");
        scanf("%d",&m);
        FILE* fp=fopen(str,"wb");
        fwrite(&m,sizeof(int),1,fp);
        for(int i=0;i< m ;i++)
        {
            for(int j=0;j<m;j++)
            {
                char c;
                printf("Enter type of block (%d, %d)\n",i,j);
                printf("[1]Enrgy\n[2]Mitosis\n[3]Forbidden\n[4]Normal\n");
                fflush(stdin);
                scanf("%c",&c);
                fputc(c,fp);
            }
        }
        fclose(fp);
        printf("%s has been maked.",str);
        if(getch())
            exit(0);
    }
    if(code==2)
    {
        printf("Enter name of map:");
        scanf("%s",&str);
        strcat(str,".bin");
        FILE* fp=fopen(str,"rb");
        if(fp == NULL)
        {
            printf("Cannot find file.\n");
            return -1;
        }
        fread(&m,sizeof(int),1,fp);
        struct khoone **maps;
        //tarif araye dobodi
        maps = (struct khoone **)malloc(m*sizeof(struct khoone *));
        for(int i = 0; i < m; i++)
        {
            maps[i] = (struct khoone *)malloc(m*sizeof(struct khoone));
        }
        //rikhtan map dar araye
        for(int i=0;i< m ;i++)
        {
            for(int j=0;j<m;j++)
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
        fclose(fp);
        while(1)
        {
            system("cls");
            gotoxy(0,0);
            for(int i=0;i<m ;i++)
            {
                for(int j=0;j<m;j++)
                {
                  printf("x= %d ,y= %d ,type= %d ,resource= %d\n",maps[i][j].x,maps[i][j].y,maps[i][j].type,maps[i][j].resource);
                }
            }
            gotoxy(0,m+2);
            printf("Enter C key for continue F key for finish\n");
            if(getch()=='f')
                break;
            int i,j,t;
            printf("Enter x:\n");
            scanf("%d",&i);
            printf("Enter y:\n");
            scanf("%d",&j);
            if(0<=i&&i<n&&0<=j&&j<n)
            {
                printf("Enter new type of block (%d, %d)\n",i,j);
                printf("[1]Enrgy\n[2]Mitosis\n[3]Forbidden\n[4]Normal\n");
                scanf("%d",&t);
                maps[i][j].type=t;
                if(maps[i][j].type==1)
                {
                    maps[i][j].resource=100;
                }
                else
                {
                    maps[i][j].resource=0;
                }
            }
            else
            {
                printf("not exist.\n");
                getch();
                continue;
            }
        }

        fp=fopen(str,"wb");
        if(fp == NULL)
        {
            printf("Cannot make file.\n");
            return -1;
        }
            fwrite(&m,sizeof(int),1,fp);
        for(int i=0;i< m ;i++)
        {
            for(int j=0;j<m;j++)
            {
                char c;
                c=maps[i][j].type+'0';
                fputc(c,fp);
            }
        }
        fclose(fp);
        printf("%s has been edit.",str);
        if(getch())
            exit(0);
    }
}
