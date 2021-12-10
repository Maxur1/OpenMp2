#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//codigo fibonacci, recursivo
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
//se crea un for para que se evaluen todos los fibonacci desde i hasta n (n siendo argumento del programa)
       for (int i=1; i<n+1; i++) {
          result = fib(i);
        printf("fibonacci of %d",i);
        printf(" is: %d\n", result);
        printf("factorization is: ");
        factorization(result, 2);
        printf("\n\n");
       }

    }



}
//codigo factorizacion
void factorization(int num){
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
//intento de hacer la factorizacion recursiva para agregar pragma, funciona el codigo pero pragma causa problemas
void factorizator(int num, int count){

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
    return factorizator(num,count);
}

//intento de hace la factorizacion en un int, causa los mismos problemas que el intento anterior de recursividad
int factorisando(int num, int count){
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
    k = factorisando(num,count);
    #pragma omp taskwait
    return k;
}
