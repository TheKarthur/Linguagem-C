#include <stdio.h>
#include <stdlib.h>
#define cls system("cls")

int ordena(float * ord_correta, float * ord_aux, int x, char let)
{
    int i, j, posicao_maior, posicao_menor;

    if(let=='d'||let=='D'){

        for(i = 0; i < x; i++){
            * (ord_correta+i)=-10000;
        }

        for (i = 0; i < x; i++) { /// qtde de numeros
            for(j = 0; j < x; j++){
                if(* (ord_aux+j) > * (ord_correta+i)){
                    * (ord_correta+i)= * (ord_aux+j);
                    posicao_maior=j;
                  }
                }
            * (ord_aux+posicao_maior)=-10000;
        }
    }

    else if(let=='c'||let=='C'){

        for(i = 0; i < x; i++){
            * (ord_correta+i)=10000;
        }

        for (i = 0; i < x; i++) { /// qtde de numeros
            for(j = 0; j < x; j++){
                if(* (ord_aux+j)< * (ord_correta+i)){
                    * (ord_correta+i)= * (ord_aux+j);
                    posicao_menor=j;
                  }
                }
            * (ord_aux+posicao_menor)=10000;
        }
    }

    else{
         return -1;
    }

    return 0;
}

int main()
{
    int quant, i, j, posicao_maior;
    char letra, numeros_inseridos[20]="";

    for(;;){
        cls;
        printf("Quantos numeros voce quer ordenar?\n");
        scanf("%i", &quant);

        float numeros[quant],ordem_aux[quant],ordem_correta[quant];

        for(i=0; i<quant; i++){
            do{
            cls;
                for(j = 0; j < i; j++){
                    if(j==i-1){
                        printf("%.2f",numeros[j]);
                    }
                    else{
                        printf("%.2f - ",numeros[j]);
                    }
                }

                if(i>0){
                    printf("\n");
                }

                printf("Digite o numero %i\n", i+1);
                scanf("%f", &numeros[i]);
            }while(numeros[i]<=-10000 || numeros[i]>=10000);
        }
        cls;
        for(i = 0; i < quant; i++){
            ordem_aux[i]=numeros[i];
        }

        do{
            printf("De que maneira voce quer ordenar os numeros?\n");
            printf("Pressione \"C\" para ordem crescente ou \"D\" para decrescente\n");
            fflush(stdin);
            scanf("%c", &letra);


            if(ordena(&ordem_correta, &ordem_aux, quant, letra)==-1){
                cls;
                printf("Comando invalido\n");
                system("pause");
                cls;
            }
        }while(letra!='c' && letra!='C' && letra!='d' && letra!='D');

        printf("\n");

        printf("NUMEROS INSERIDOS:\n");
            for(j = 0; j < i; j++){
                if(j==i-1){
                    printf("%.2f",numeros[j]);
                }
                else{
                    printf("%.2f - ",numeros[j]);
                }
            }

        printf("\n\n");

        printf("NUMEROS ORDENADOS:\n");
        for(i = 0; i < quant; i++){
            printf("Numero %i: %.2f\n",i+1, ordem_correta[i]);
        }

        printf("\nArthur Rodrigues Padilha\n");
        system("pause");
    }

    return 0;
}
