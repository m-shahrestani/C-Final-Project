#include <stdio.h>
#include <stdlib.h>
#include "mapeditor.h"

void makemap(void)
{
    int m;
    printf("Enter n:");
    scanf("%d",&m);
    FILE* fp=fopen("maped.bin","wb");
    fwrite(&m,sizeof(int),1,fp);

//    struct khoone **makemaps;
//    //tarif araye dobodi
//    makemaps = (struct khoone **)malloc(m*sizeof(struct khoone *));
//    for(int i = 0; i < m; i++)
//    {
//        makemaps[i] = (struct khoone *)malloc(m*sizeof(struct khoone));
//    }
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
    printf("map maked.");
    if(getch())
        exit(0);
}
