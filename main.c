#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
#pragma omp task shared(i)
        i = fib(n - 1);
#pragma omp task shared(j)
        j = fib(n - 2);
#pragma omp taskwait
        return i + j;
    }
}
int main(int argc, char **argv)
{
    int n, result;
    char *a = argv[1];
    n = atoi(a);

#pragma omp parallel
    {
#pragma omp single
       for (int i=1; i<n+1; i++) {
          result = fib(i);
        printf("fibonacci of %d",i);
        printf(" is: %d\n", result);
        printf("factorization is: ");
        primerfactors(result, 2);
        printf("\n\n");
       }

    }



}

void primerfactors(int num){
    if(num < 0){
        return;
    }
    int count;
    int primero = num;
    printf("the factorization is: ");
    for(count = 2; num>1; count++){
        while(num % count == 0){
            if(primero!= num){
                printf(" x ");
            }
            printf("%d", count);
            num = num/count;
        }
    }
}
void primerfactors2(int num, int count){

    if(num <= 1){
        return;
    }
    if(num % count == 0){
        printf(" %d ",count);
        num = num/count;

    }else{
        count++;
    }
#pragma omp task shared(k)
    return primerfactors2(num,count);
}

int primerfactors3(int num, int count){
    int k;

    if(num <= 1){
        return 1;
    }
    if(num % count == 0){
        printf(" %d ",count);
        num = num/count;

    }else{
        count++;
    }
#pragma omp task shared(k)
    k = primerfactors3(num,count);
    #pragma omp taskwait
    return k;
}
