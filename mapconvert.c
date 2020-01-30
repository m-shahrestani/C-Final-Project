#include "stdio.h"
#include "mapconvert.h"
#include "linkedlist.h"

void mapconverter(struct khoone **maps)
{
    FILE *fp;
    fp=fopen("textmap.txt","w");
    for(int i=0;i< n ;i++)
    {
        for(int j=0;j<n;j++)
        {
            fprintf(fp,"(%d, %d)\t",maps[i][j].x,maps[i][j].y);
            if(maps[i][j].type==1)
                fprintf(fp,",type= Energy\t,resource= %d\n",maps[i][j].resource);
            if(maps[i][j].type==2)
                fprintf(fp,",type= Mitosis\n");
            if(maps[i][j].type==3)
                fprintf(fp,",type= Forbidden\n");
            if(maps[i][j].type==4)
                fprintf(fp,",type= Normal\n");
        }
    }
    fclose(fp);
    printf("map converted.");
    if(getch())
        exit(0);
}
