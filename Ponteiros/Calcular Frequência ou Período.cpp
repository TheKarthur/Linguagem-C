#include <stdio.h>
#include <stdlib.h>
#define cls system("cls")

int sinal(float * frequencia, float * periodo)
{

    if(*frequencia==0 && *periodo==0){
        return -1;
    }

    if(*frequencia!=0 && *periodo!=0){
        return 1;
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

    do{
    printf("Digite o valor do frequencia\n");
    scanf("%f", &freq);
    cls;
    printf("Digite o valor do periodo\n");
    scanf("%f", &per);
    cls;

    if(sinal(&freq, &per)!=0){
        printf("Valores invalidos\n");
        system("pause");
        cls;
    }

    printf("Codigo de erro: %i",sinal(&freq, &per));
    system("pause");
    cls;

    }while(sinal(&freq, &per)!=0);

    printf("Frequencia: %f\n", freq);
    printf("Periodo: %f\n", per);

    return 0;
}
