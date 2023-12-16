#include <stdio.h>
#include <stdlib.h>
#define cls system("cls")

int sinal(float * frequencia, float * periodo, int * contador)
{
    *contador=0;

    if(*frequencia==0){
        *contador+=1;
    }

    if(*periodo==0){
        *contador+=1;
    }

    if(*contador!=1){
        return -1;
    }

    if(*frequencia==0){
        *frequencia= 1 / *periodo;
    }

    if(*periodo==0){
        *periodo= 1 / *frequencia;
    }
    return 0;
}

int main()
{
    float freq, per;
    int cont, aux;

    do{
    printf("Digite o valor do frequencia\n");
    scanf("%f", &freq);
    cls;
    printf("Digite o valor do periodo\n");
    scanf("%f", &per);
    cls;
    aux=sinal(&freq, &per, &cont);

    if(aux==-1){
        printf("Valores invalidos\n");
        printf("Valor do erro : %i\n", aux);
        system("pause");
        cls;
    }

    }while(aux==-1);

    printf("Frequencia: %f Hz\n", freq);
    printf("Periodo: %f s\n", per);
    printf("\nArthur Rodrigues Padilha - Turma 4212\n");

    return 0;
}
