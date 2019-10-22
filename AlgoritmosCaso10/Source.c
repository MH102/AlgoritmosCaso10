#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MATROID_ARR_SIZE 2
#define STRING_SIZE_MAX 10
typedef struct matroid{
    int * arrNum;
    int * solNum;
    char ** arrStr;
    char ** solStr;
    char * fun;
    int size;
    int type;
    int solCount;
} matroid;

struct matroid matroids[MATROID_ARR_SIZE];
void initNumMatroid(matroid mtr){
    srand(time(NULL));
    for(int i = 0; i < 20; i++){
        int randNum = rand() % 101;
        mtr.arrNum[i] = randNum;
    }
}
void printMatroid(matroid mtr){
    printf("------------------------------\n");
    if(mtr.type == 0){
        for(int i = 0; i < mtr.size; i++){
            printf("%d\n",mtr.arrNum[i]);
        }
    }
    else{
        for(int i = 0; i < mtr.size; i++){
            printf("%s\n",mtr.arrStr[i]);
        }
    }
}
int main(){

    for(int m = 0; m < MATROID_ARR_SIZE; m++){
        matroids[m].arrNum = malloc(20*sizeof(int));
        matroids[m].size = 20;
        matroids[m].type = 0;
        initNumMatroid(matroids[m]);
        printMatroid(matroids[m]);
    }
    matroids[MATROID_ARR_SIZE].arrStr = malloc(10 * sizeof(char*));
    matroids[MATROID_ARR_SIZE].size = 10;
    matroids[MATROID_ARR_SIZE].type = 1;
    for(int i = 0; i < 10; i++){
        matroids[MATROID_ARR_SIZE].arrStr[i] = malloc((STRING_SIZE_MAX + 1) * sizeof(char));
        matroids[MATROID_ARR_SIZE].arrStr[i] = "tester";
    }
    printMatroid(matroids[MATROID_ARR_SIZE]);

    #pragma omp parallel
    {
        printf("Hello World!\n");
    }
    system("PAUSE");
    return 0;
}
