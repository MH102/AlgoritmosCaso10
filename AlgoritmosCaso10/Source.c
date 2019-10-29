#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MATROIDA_ARR_SIZE 2
#define MATROIDB_ARR_SIZE 4
#define STRING_SIZE_MAX 10
#define MATROID_NUM_ARR_SIZE 30
int solCount;
typedef struct matroid{
    int * arrNum;
    int * solNum;
    char ** arrStr;
    char ** solStr;
    char * fun;
    int size;
    int type;
} matroid;


void initNumMatroid(matroid * mtr){
    if(omp_in_parallel()){
        srand(time(NULL)+omp_get_thread_num());
        for(int i = 0; i < MATROID_NUM_ARR_SIZE; i++){
            int randNum = rand() % 15;
            mtr->arrNum[i] = randNum;
        }
        return;
    }
    srand(time(NULL));
    for(int i = 0; i < MATROID_NUM_ARR_SIZE; i++){
        int randNum = rand() % 101;
        mtr->arrNum[i] = randNum;
    }
}
void initStrMatroid(matroid mtr){
    mtr.arrStr[0] = "ama";
    mtr.arrStr[1] = "casa";
    mtr.arrStr[2] = "test";
    mtr.arrStr[3] = "ojo";
    mtr.arrStr[4] = "ala";
    mtr.arrStr[5] = "toro";
    mtr.arrStr[6] = "carro";
    mtr.arrStr[7] = "tasa";
    mtr.arrStr[8] = "oro";
    mtr.arrStr[9] = "hoja";
}
void printMatroid(matroid mtr){
    if(mtr.type == 0){
        printf("S: [");
        for(int i = 0; i < mtr.size-1; i++){
            printf("%d, ",mtr.arrNum[i]);
        }
        printf("%d]\n",mtr.arrNum[mtr.size-1]);
        printf("Function: %s\n",mtr.fun);
    }
    else{
        if(mtr.type == 1){
            printf("S: [");
            for(int i = 0; i < mtr.size-1; i++){
                printf("%s, ",mtr.arrStr[i]);
            }
            printf("%s]\n",mtr.arrStr[mtr.size-1]);
            printf("Function: %s\n",mtr.fun);
        }
    }
}
void printMatroidSolutions(matroid mtr){
    if(mtr.type == 0){
        printf("%d soluciones: [",solCount);
        for(int i = 0; i < solCount-1; i++){
            printf("%d, ",mtr.solNum[i]);
        }
        printf("%d]\n\n",mtr.solNum[solCount-1]);
    }
    else{
        if(mtr.type == 1){
            printf("%d soluciones: [",solCount);
            for(int i = 0; i < solCount-1; i++){
                printf("%s, ",mtr.solStr[i]);
            }
            printf("%s]\n\n",mtr.solStr[solCount-1]);
        }
    }
}
int isEven(int num){
    return num%2==0;
}
int isPalindrome(char * cadena){
    int length = strlen(cadena);
    int flag = 1;
    for(int i=0;i < length ;i++){
        if(cadena[i] != cadena[length-i-1]){
            flag = 0;
            break;
        }
    }
    return flag;
}
int getSolCount(matroid M){
    solCount = 0;
    if(M.fun == "even"){
        for(int i = 0; i < M.size; i++){
            if(isEven(M.arrNum[i])){
                solCount++;
            }
        }
        return solCount;
    }
    if(M.fun == "odd"){
        for(int i = 0; i < M.size; i++){
            if(!isEven(M.arrNum[i])){
                solCount++;
            }
        }
        return solCount;
    }
    if(M.fun =="true"){
        for(int i = 0; i < M.size; i++){
            if(M.arrNum[i] == 1){
                solCount++;
            }
        }
        return solCount;
    }if(M.fun =="false"){
        for(int i = 0; i < M.size; i++){
            if(M.arrNum[i] == 0){
                solCount++;
            }
        }
        return solCount;
    }
    if(M.fun == "palindrome"){
        for(int i = 0; i < M.size; i++){
            if(isPalindrome(M.arrStr[i])){
                solCount++;
            }
        }
        return solCount;
    }
}
void evaluateMatroid(matroid M){
    solCount = 0;
    if(M.fun == "even"){
        for(int i = 0; i < M.size; i++){
            if(isEven(M.arrNum[i])){
                M.solNum[solCount] = M.arrNum[i];
                solCount++;
            }
        }
        return;
    }
    if(M.fun == "odd"){
        for(int i = 0; i < M.size; i++){
            if(!isEven(M.arrNum[i])){
                M.solNum[solCount] = M.arrNum[i];
                solCount++;
            }
        }
        return;
    }
    if(M.fun =="true"){
        for(int i = 0; i < M.size; i++){
            if(M.arrNum[i] == 1){
                M.solNum[solCount] = M.arrNum[i];
                solCount++;
            }
        }
        return;
    }if(M.fun =="false"){
        for(int i = 0; i < M.size; i++){
            if(M.arrNum[i] == 0){
                M.solNum[solCount] = M.arrNum[i];
                solCount++;
            }
        }
        return;
    }
    if(M.fun == "palindrome"){
        for(int i = 0; i < M.size; i++){
            if(isPalindrome(M.arrStr[i])){
                M.solStr[solCount] = M.arrStr[i];
                solCount++;
            }
        }
        return;
    }
}
void evaluateMatroidArray(matroid *matroids, int size, char type){
    if(type == 'A'){
        printf("Solving individual matroids in parallel\n");
        for(int i = 0; i < size; i++){
            printf("Solving matroid number %d\n",i+1);
            #pragma omp parallel
            {
                printf("Thread %d used",omp_get_thread_num());
                evaluateMatroid(matroids[i]);
                printf("\n");
            }
        }
        printf("\n");
        for(int i = 0; i < size; i++){
            printf("Matroid %d:\n",i+1);
            printMatroid(matroids[i]);
            printMatroidSolutions(matroids[i]);
        }
    }
    else{
        if(type =='B'){
            printf("Solving individual matroids and intersecting in parallel\n");
            #pragma omp parallel for
            for(int i = 0; i < size; i++){
                printf("Solving matroid number %d on thread %d\n",i+1,omp_get_thread_num());
                evaluateMatroid(matroids[i]);
            }
            printf("\n");
            for(int i = 0; i < size; i++){
                printf("Matroid %d:\n",i+1);
                printMatroid(matroids[i]);
                printMatroidSolutions(matroids[i]);
            }
            int counter = 0;
            int intersections;
            int * arrA = matroids[counter].solNum;
            int * arrB = matroids[counter+1].solNum;
            int numberOfSol = getSolCount(matroids[counter]);
            int * arrI[MATROID_NUM_ARR_SIZE];
            while(counter+1!=size){
                intersections = 0;
                for(int i = 0; i < numberOfSol; i++){
                    int breaker = 0;
                    #pragma omp parallel for
                    for(int j = 0; j < getSolCount(matroids[counter+1]); j++){
                        //if(arrA[i] == matroids[counter+1].solNum[j]){
                        if(arrA[i] == arrB[j] && breaker == 0){
                            //arrI[intersections] = matroids[counter+1].solNum[j];
                            //matroids[counter+1].solNum[j] = -1;
                            arrI[intersections] = arrB[j];
                            arrB[j] = -1;
                            intersections++;
                            breaker = 1;
                        }
                    }
                }
                counter++;
                arrA = arrI;
                arrB = matroids[counter+1].solNum;
                numberOfSol = intersections;
            }
            printf("Intersection of solutions: [");
            if(intersections!=0){
                for(int i = 0; i < intersections-1; i++){
                    printf("%d, ",arrI[i]);
                }
                printf("%d",arrI[intersections-1]);
            }
            printf("]\n");
        }
    }
}

int main(){
    matroid matroidsA[MATROIDA_ARR_SIZE];
    matroid matroidsB[MATROIDB_ARR_SIZE];
    //INICIALIZACION DEL ARREGLO DE MATROIDS A

    //MATROID 1 ENTEROS
    matroidsA[0].arrNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
    matroidsA[0].solNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
    matroidsA[0].size = MATROID_NUM_ARR_SIZE;
    matroidsA[0].type = 0;
    matroidsA[0].fun = "even";
    initNumMatroid(&matroidsA[0]);

    //MATROID 2 BOOLEANOS
    matroidsA[1].arrNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
    matroidsA[1].solNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
    matroidsA[1].size = MATROID_NUM_ARR_SIZE;
    matroidsA[1].type = 0;
    matroidsA[1].fun = "true";
    srand(time(NULL));
    for(int i = 0; i < MATROID_NUM_ARR_SIZE; i++){
        matroidsA[1].arrNum[i] = rand() % 2;
    }

    //MATROID 2 STRINGS
    matroidsA[2].arrStr = malloc(10 * sizeof(char*));
    matroidsA[2].solStr = malloc(10 * sizeof(char*));
    matroidsA[2].size = 10;
    matroidsA[2].type = 1;
    matroidsA[2].fun = "palindrome";
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        matroidsA[2].arrStr[i] = malloc((STRING_SIZE_MAX + 1) * sizeof(char));
        matroidsA[2].solStr[i] = malloc((STRING_SIZE_MAX + 1) * sizeof(char));
    }
    initStrMatroid(matroidsA[2]);

    //INICIALIZACION DEL ARREGLO DE MATROIDS B
    #pragma omp parallel for
    for(int i = 0; i <= MATROIDB_ARR_SIZE; i++){
        matroidsB[i].arrNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
        matroidsB[i].solNum = malloc(MATROID_NUM_ARR_SIZE*sizeof(int));
        matroidsB[i].size = MATROID_NUM_ARR_SIZE;
        matroidsB[i].type = 0;
        matroidsB[i].fun = "odd";
        initNumMatroid(&matroidsB[i]);
    }


    //EVALUACION DEL ARREGLO DE MATROIDS A
    printf("----------------------------------------ARRAY A----------------------------------------\n");
    evaluateMatroidArray(matroidsA,MATROIDA_ARR_SIZE+1,'A');
    printf("---------------------------------------------------------------------------------------\n\n");
    //EVALUACION DEL ARREGLO DE MATROIDS B
    printf("----------------------------------------ARRAY B----------------------------------------\n");
    evaluateMatroidArray(matroidsB,MATROIDB_ARR_SIZE+1,'B');
    printf("---------------------------------------------------------------------------------------\n\n");

    return 0;
}
