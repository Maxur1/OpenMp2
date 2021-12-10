#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
#pragma omp taks shared(i)
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
        result = fib(n);
    }
    printf("result is %d\n", result);
    primerfactors(result);


}

void primerfactors(int num){
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
