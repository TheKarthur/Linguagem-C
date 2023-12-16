#include <stdio.h>
#include <stdlib.h>
#define cls system("cls")

int verifica(float * cateto_a, float * cateto_b, float * hipotenusa,int * cont, int * aux)
{
    *cont=0;
    *aux=0;

    if(*cateto_a!=0){
        *cont+=1;
    }
    if(*cont<1){
        *aux=1;
    }

    if(*cateto_b!=0){
        *cont+=1;
    }
    if(*cont<2){
        *aux=2;
    }

    if(*hipotenusa!=0){
        *cont+=1;
    }
    if(*cont<3){
        *aux=3;
    }

    return 0;
}

int triangulo_retangulo(float * cateto_a, float * cateto_b, float * hipotenusa, int * aux){

    float result=0;

    if(*aux==1){
       result=sqrt(pow(*hipotenusa,2)-pow(*cateto_b,2));
       printf("O cateto A eh: %f", result);
    }

    if(*aux==2){
       result=sqrt(pow(*hipotenusa,2)-pow(*cateto_a,2));
       printf("O cateto B eh: %f", result);
    }

    if(*aux==3){
       result=sqrt(pow(*cateto_a,2)+pow(*cateto_b,2));
       printf("A hipotenusa eh: %f", result);
    }

}


int main()
{
    float cateto_a, cateto_b, hipotenusa;

    int contador=0, aux=0;

    do{
    printf("Digite o valor do cateto A (Envie 0 se deseja calcular o parametro)\n");
    scanf("%f", &cateto_a);
    cls;
    printf("Digite o valor do cateto B\n");
    scanf("%f", &cateto_b);
    cls;
    printf("Digite o valor do hipotenusa\n");
    scanf("%f", &hipotenusa);
    cls;
    verifica(&cateto_a, &cateto_b, &hipotenusa, &contador, &aux);

    if(contador!=2){
        printf("Valores invalidos\n");
        system("pause");
        cls;
    }
    }while(contador!=2);

    triangulo_retangulo(&cateto_a,&cateto_b,&hipotenusa,&aux);
  
    return 0;
}
