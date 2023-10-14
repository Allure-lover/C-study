#include<stdio.h>
#include<iostream>
using namespace std;

void test(){
    FILE* fp;
    int i,a[6]={1,2,3,4,5,6};
    fp =fopen("da.dat", "w+");
    for(int i=0; i<6;i++) fprintf(fp, "%d\n", a[i]);
    rewind(fp);
    for(int i=0; i<6;i++) fscanf(fp, "%d", &a[5-i]);
    fclose(fp);
    for(int i=0; i<6; i++){
        printf("%d", a[i]);
    }
}

int main(){
    FILE* fp;
    int a[10]={1,2,3}, i, n;
    fp=fopen("d1.dat", "w");
    for(int i=0;i<3;i++) fprintf(fp, "%d", a[i]);
    fprintf(fp,"\n");
    fclose(fp);
    fp=fopen("d1.dat", "r");
    fscanf(fp, "%d", &n);
    fclose(fp);
    printf("%d\n",n);

    test();
    system("pause");
    return 0;
}