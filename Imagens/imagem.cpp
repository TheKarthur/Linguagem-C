#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define _WIN32_WINNT 0x0500


typedef struct CabecalhoArquivo{
unsigned short tipo_arquivo;//tipo do arquivo
unsigned int tam_arquivo;//Tamanho do arquivo (cabeçalho)
unsigned short esp_reservado1;//espaço reservado
unsigned short esp_reservado2;//espaço reservado
unsigned int deslocamento_de_bits;//especifica o deslocamento em bytes do início
//do arquivo até onde começa a área da imagem.
} CABECALHO;

typedef struct info_cabecalho{
unsigned int tam_imagem;
unsigned int largura_imagem;
unsigned int altura_imagem;
unsigned short BiPlanes;
unsigned short contador_bit;
unsigned int compressor_imagem;
unsigned long int tam_imagemImag;
unsigned int BiXPPMeter;
unsigned int BiYPPMeter;
unsigned int BiClrUsed;
unsigned int BiClrImpor;

} INFO;

void gotoxy(int coluna, int linha)//coloca o cursor na posi��o x, y do plano da tela
{
        COORD point;
        point.X = coluna; point.Y = linha;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

int main()
{
//    HWND hWnd = GetConsoleWindow();
//    ShowWindow( hWnd, SW_MINIMIZE );  //won't hide the window without SW_MINIMIZE
//    ShowWindow( hWnd, SW_HIDE );

system("MODE con cols=80 lines=20"); //Redimensiona a tela

unsigned long int size_i;
CABECALHO cab;
INFO inf;

FILE *pa;//Ponteiro de arquivo

char nome_da_imagem[]="gremio_c.bmp";
char nome_da_imagem_nova[]="gremio_new.bmp";
//char nome_da_imagem2[]="gremio_c2.bmp";

pa = fopen(nome_da_imagem,"rb");//abre a imagem e indica um
//endereço(ponteiro) para o arquivo
if(pa==NULL)
{
printf("\n\nErro, A imagem não pode ser aberta, o programa será fechado\n\n");
return 1;
}

fread(&cab,14,1,pa);//le dados do arquivo e armazena em cab
fread(&inf,40,1,pa);
//Os 14 bytes lido serao colocados no endereço da struct cab
printf("\nTipo do arquivo 0x%X",cab.tipo_arquivo);

//informação da imagem
printf("\ntamanho das informacoes de cabecalho: %d",inf.tam_imagem);
printf("\n\nLargura: %d",inf.largura_imagem);
printf("\n\nAltura: %d",inf.altura_imagem);

int desloc=inf.contador_bit/8;

size_i = (inf.largura_imagem * inf.altura_imagem * desloc);//o 4 é por causa da quantidade de Bytes por pixel
printf("\nTamanho em bytes da imagem: %d\n\n", size_i);

unsigned char *pixels = (unsigned char*) malloc(size_i);//reserva espaço na mémória para a imagem
fread(pixels,size_i,1,pa);

fclose(pa);//fecha o arquivo

pa = fopen(nome_da_imagem,"rb");

fread(&cab,14,1,pa);//le dados do arquivo e armazena em cab
fread(&inf,40,1,pa);
unsigned char *pixels2 = (unsigned char*) malloc(size_i);//reserva espaço na mémória para a imagem
fread(pixels2,size_i,1,pa);

fclose(pa);//fecha o arquivo

unsigned char *media_pixels = (unsigned char*) malloc(size_i/desloc);//reserva espaço na mémória para a imagem

system("pause");
int op, op2, op3;
do{
system("cls");
printf("Digite o que deseja fazer:\n\n");
printf("1 - imagem original    2 - imagem cinza    3 - borrar imagem cinza\n");
printf("\n4 - borrar imagem colorida    5 - filtro de borda    6 - Achar objeto\n");
printf("\n7 - retirar cor\n\n");

scanf("%i", &op);
}while(op < 1 || op > 7);

int red, green, blue, red2, green2, blue2;
int pixel_mais_abaixo=0, pixel_mais_acima=0, pixel_mais_a_direita=0, pixel_mais_a_esquerda=0;
int cont_pixel=0;
int ajuda=0;

if(op==3){
    do{
        system("cls");
        printf("Escolha a matriz utilizada para o efeito borrar imagem cinza\n");
        printf("Borrar 3x3 - 1    Borrar 9x9 - 2\n");
        scanf("%i", &op2);
    }while(op2 < 1 || op2 > 2);
}

if(op==4){
    do{
        system("cls");
        printf("Escolha a matriz utilizada para o efeito borrar imagem colorida\n");
        printf("Borrar 3x3 - 1\n");
        scanf("%i", &op2);
    }while(op2 < 1 || op2 > 1);
}

if(op==5){
    do{
        system("cls");
        printf("Escolha a matriz utilizada para o efeito de borda\n");
        printf("Filtro de borda 3x3 - 1    Filtro de borda 5x5 - 2\n");
        scanf("%i", &op2);
    }while(op2 < 1 || op2 > 2);
}

if(op==6){
    system("cls");
    printf("Digite a cor do objeto:\n");
    printf("RED:        \n");
    printf("GREEN:      \n");
    printf("BLUE:       \n");

    do{
        gotoxy(5,1);
        printf("                                                  ");
        gotoxy(5,1);
        scanf("%i", &red);
        fflush(stdin);
    }while(red<0 || red>255);
    do{
        gotoxy(7,2);
        printf("                                                  ");
        gotoxy(7,2);
        scanf("%i", &green);
        fflush(stdin);
    }while(green<0 || green>255);
    do{
        gotoxy(6,3);
        printf("                                                  ");
        gotoxy(6,3);
        scanf("%i", &blue);
        fflush(stdin);
    }while(blue<0 || blue>255);

}


if(op==7){
    do{
    system("cls");
    printf("Digite Quantas cores deseja retirar da imagem?");
    printf("\n\n1 ou 2?\n");
    scanf("%i", &ajuda);
    }while(ajuda < 1 || ajuda > 2);
    op2=0;
    op3=0;
    do{
        ajuda--;
        system("cls");
        printf("Digite a cor que sera retirada: \n");
        printf("\n1 - RED     2 - GREEN     3 - BLUE     \n");
        scanf("%i", &op2);
        if(op2==1)op3|=1;
        if(op2==2)op3|=2;
        if(op2==3)op3|=4;

        if(op2<1 || op2>3)ajuda++;

    }while(((op3 < 0b1 || op3 > 0b111) && (op2 < 1 || op2 > 3)) || ajuda > 0);
}

FILE *ponteiro_imagem = fopen(nome_da_imagem_nova,"wb");

if(ponteiro_imagem == NULL)
{
printf("\nNao foi possivel abrir imagem para escrita\n\n");
return 2;
}

//copiando os cabeçalhos na nova imagem
fwrite(&cab,14,1,ponteiro_imagem);//escreve o cabeçalho no arquivo
fwrite(&inf,40,1,ponteiro_imagem);//escreve as informações da imagem no arquivo
unsigned int media;


//fseek(ponteiro_imagem,(inf.largura_imagem*desloc)+4,SEEK_CUR);
int aux=0,cont=0,aux2=0, aux3, aux4=-1, aux5=inf.altura_imagem+1;
int media_vermelho,media_azul,media_verde;

for (int i = 0; i < size_i; i+=desloc){//vendo a imagem com editor hexa vi que cada pixel tem 32 bits ou 4 bytes
if(i>0)aux++;
media_pixels[aux] =  (pixels2[i]+pixels2[i+1]+pixels2[i+2])/3;
}

aux=0;
for (int i = 0; i < size_i; i+=desloc){

if(i>0)aux++;

if(op==1){
    if(!(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc)))){
        pixels[i] = 0;   // blue *Pixels;
        pixels[i+1] = 0; // green *pixels(i+1);
        pixels[i+2] = 0; // red *pixels(I+2);
    }
}

if(op==2){ // imagem cinza
    if(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc))){
        pixels[i] = media_pixels[aux];// blue *Pixels;
        pixels[i+1] = media_pixels[aux];// green *pixels(i+1);
        pixels[i+2] = media_pixels[aux];// red *pixels(I+2);
    }
    else{
        pixels[i] = 0;// blue *Pixels;
        pixels[i+1] = 0;// green *pixels(i+1);
        pixels[i+2] = 0;// red *pixels(I+2);
    }
}

if(op==3 && op2==1){ // borrar imagem cinza 3x3
    if(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc))){
        //size_i
        media= media_pixels[aux]; //pixel do meio
        media+= media_pixels[aux+1]; //pixel meio direita
        media+= media_pixels[aux-1]; // pixel meio esquerda
        media+= media_pixels[aux+inf.largura_imagem]; // pixel meio cima
        media+= media_pixels[aux-inf.largura_imagem]; // pixel meio baixo
        media+= media_pixels[aux+inf.largura_imagem+1]; // cima direita
        media+= media_pixels[aux+inf.largura_imagem-1]; // cima esquerda
        media+= media_pixels[aux-inf.largura_imagem+1]; // pixel baixo direita
        media+= media_pixels[aux-inf.largura_imagem-1]; // pixel baixo esquerda

        media /= 9;

        pixels[i] = media;// blue *Pixels;
        pixels[i+1] =media;// green *pixels(i+1);
        pixels[i+2] = media;// red *pixels(I+2);
    }
    else{
        pixels[i] = 0;// blue *Pixels;
        pixels[i+1] =0;// green *pixels(i+1);
        pixels[i+2] = 0;// red *pixels(I+2);
    }
}

if(op==3 && op2==2){ // borrar imagem cinza 9x9
    if(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc))){

        media=0;

        for(int z=0; z<9; z++){
            media+= media_pixels[aux-4+z]; // pixels do meio
            if(i<size_i - (inf.largura_imagem*(desloc))){
                media+= media_pixels[aux-4+z+(inf.largura_imagem)]; // pixels 1 acima do meio
            }
            if(i<size_i - (inf.largura_imagem*(desloc)*2)){
                    media+= media_pixels[aux-4+z+(inf.largura_imagem*2)]; // pixels 2 acima do meio
            }
            if(i<size_i - (inf.largura_imagem*(desloc)*3)){
                    media+= media_pixels[aux-4+z+(inf.largura_imagem*3)]; // pixels 3 acima do meio
            }
            if(i<size_i - (inf.largura_imagem*(desloc)*4)){
                    media+= media_pixels[aux-4+z+(inf.largura_imagem*4)]; // pixels 4 acima do meio
            }
            if(i>inf.largura_imagem*desloc){
                    media+= media_pixels[aux-4+z-(inf.largura_imagem)]; // pixels 1 abaixo do meio
            }
            if(i>inf.largura_imagem*desloc*2){
                    media+= media_pixels[aux-4+z-(inf.largura_imagem*2)]; // pixels 2 abaixo do meio
            }
            if(i>inf.largura_imagem*desloc*3){
                media+= media_pixels[aux-4+z-(inf.largura_imagem*3)]; // pixels 3 abaixo do meio

            }
            if(i>inf.largura_imagem*desloc*4){
                    media+= media_pixels[aux-4+z-(inf.largura_imagem*4)]; // pixels 4 abaixo do meio
            }

        }

        //

        media/=81;
        pixels[i] = media;// blue *Pixels;
        pixels[i+1] =media;// green *pixels(i+1);
        pixels[i+2] = media;// red *pixels(I+2);
    }
    else{
        pixels[i] = 0;// blue *Pixels;
        pixels[i+1] =0;// green *pixels(i+1);
        pixels[i+2] = 0;// red *pixels(I+2);
    }
}



if(op==4 && op2==1){ // borrar imagem colorida
if(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc))){

media_azul=pixels2[i];
media_azul+=pixels2[i+desloc]+pixels2[i-desloc]+pixels2[i+(inf.largura_imagem*desloc)]+pixels2[i-(inf.largura_imagem*desloc)]+pixels2[i+(inf.largura_imagem*desloc)+desloc]+pixels2[i+(inf.largura_imagem*desloc)-desloc]+pixels2[i-(inf.largura_imagem*desloc)+desloc]+pixels2[i-(inf.largura_imagem*desloc)-desloc];
media_azul/=9;

media_verde=pixels2[i+1];
media_verde+=pixels2[i+desloc+1]+pixels2[i-desloc+1]+pixels2[i+1+(inf.largura_imagem*desloc)]+pixels2[i+1-(inf.largura_imagem*desloc)]+pixels2[i+desloc+1+(inf.largura_imagem*desloc)]+pixels2[i-desloc+1+(inf.largura_imagem*desloc)]+pixels2[i+desloc+1-(inf.largura_imagem*desloc)]+pixels2[i-desloc+1-(inf.largura_imagem*desloc)];
media_verde/=9;

media_vermelho=pixels2[i+2];
media_vermelho+=pixels2[i+desloc+2]+pixels2[i-desloc+2]+pixels2[i+2+(inf.largura_imagem*desloc)]+pixels2[i+2-(inf.largura_imagem*desloc)]+pixels2[i+desloc+2+(inf.largura_imagem*desloc)]+pixels2[i-desloc+2+(inf.largura_imagem*desloc)]+pixels2[i+desloc+2-(inf.largura_imagem*desloc)]+pixels2[i-desloc+2-(inf.largura_imagem*desloc)];
media_vermelho/=9;


pixels[i] = media_azul;// blue *Pixels;
pixels[i+1] =media_verde;// green *pixels(i+1);
pixels[i+2] = media_vermelho;// red *pixels(I+2);
}
else{
pixels[i] = 0;// blue *Pixels;
pixels[i+1] =0;// green *pixels(i+1);
pixels[i+2] = 0;// red *pixels(I+2);
}
}

if(op==5 && op2==1){ // filtro de borda 3x3
    if(i>inf.largura_imagem*desloc && i<size_i - (inf.largura_imagem*(desloc))){

    media= (media_pixels[aux])*(8); //pixel do meio
    media+= (media_pixels[aux+1])*(-1); //pixel meio direita
    media+= (media_pixels[aux-1])*(-1); // pixel meio esquerda
    media+= (media_pixels[aux+inf.largura_imagem])*(-1); // pixel meio cima
    media+= (media_pixels[aux-inf.largura_imagem])*(-1); // pixel meio baixo
    media+= (media_pixels[aux+inf.largura_imagem+1])*(-1); // cima direita
    media+= (media_pixels[aux+inf.largura_imagem-1])*(-1); // cima esquerda
    media+= (media_pixels[aux-inf.largura_imagem+1])*(-1); // pixel baixo direita
    media+= (media_pixels[aux-inf.largura_imagem+1])*(-1); // pixel baixo esquerda

    if(media>(-50)||media<50){
        pixels[i] = 255;// blue *Pixels;
        pixels[i+1] =255;// green *pixels(i+1);
        pixels[i+2] = 255;// red *pixels(I+2);
    }
   else{
        pixels[i] = 0;// blue *Pixels;
        pixels[i+1] = 0;// green *pixels(i+1);
        pixels[i+2] = 0;// red *pixels(I+2);
    }
}
else{
pixels[i] = 0;// blue *Pixels;
pixels[i+1] =0;// green *pixels(i+1);
pixels[i+2] = 0;// red *pixels(I+2);
}
}


if(op==5 && op2==2){ // filtro borda 5x5
    if(i>(inf.largura_imagem*desloc)*2 && i<size_i - ((inf.largura_imagem*(desloc))*2)){

        media= (media= media_pixels[aux])*(16); //pixel do meio
        media+= (media_pixels[aux+1])*(-2); //pixel meio direita
        media+= (media_pixels[aux-1])*(-2); // pixel meio esquerda
        media+= (media_pixels[aux+inf.largura_imagem])*(-2); // pixel meio cima
        media+= (media_pixels[aux-inf.largura_imagem])*(-2); // pixel meio baixo
        media+= (media_pixels[aux+inf.largura_imagem+1])*(-1); // cima direita
        media+= (media_pixels[aux+inf.largura_imagem-1])*(-1); // cima esquerda
        media+= (media_pixels[aux-inf.largura_imagem+1])*(-1); // pixel baixo direita
        media+= (media_pixels[aux-inf.largura_imagem+1])*(-1); // pixel baixo esquerda

        media+= (media_pixels[aux-2])*(-1); // pixel meio e 2 pra esquerda
        media+= (media_pixels[aux+2])*(-1); // pixel meio e 2 pra direita

        media+= (media_pixels[aux+(2*inf.largura_imagem)])*(-1); // pixel meio 2 pra cima
        media+= (media_pixels[aux-(2*inf.largura_imagem)])*(-1); // pixel meio 2 pra baixo

        //getchar();
        if(media>(-50)||media<50){
            pixels[i] = 255;// blue *Pixels;
            pixels[i+1] =255;// green *pixels(i+1);
            pixels[i+2] = 255;// red *pixels(I+2);
        }
        else{
            pixels[i] = 0;// blue *Pixels;
            pixels[i+1] = 0;// green *pixels(i+1);
            pixels[i+2] = 0;// red *pixels(I+2);
        }
    }
    else{
    pixels[i] = 0;// blue *Pixels;
    pixels[i+1] =0;// green *pixels(i+1);
    pixels[i+2] = 0;// red *pixels(I+2);
    }
}
if(op==6){ // achar objeto || distancia entre dois objetos
    if(i>(inf.largura_imagem*desloc)*2 && i<size_i - ((inf.largura_imagem*(desloc))*2)){

    if(pixels2[i]==blue && pixels2[i+1]==green && pixels2[i+2]==red){
    aux2=(((i/desloc)+1)/inf.largura_imagem); //linha atual - 1
    if(cont_pixel==0){
        pixel_mais_abaixo=(i/desloc)+1;
        pixel_mais_a_esquerda=(i/desloc)+1;
        pixel_mais_a_direita=(i/desloc)+1;
        cont_pixel++;
    }
    pixel_mais_acima=(i/desloc)+1;
    aux3=((i/desloc)+1)-(aux2*inf.largura_imagem); // pixel atual da linha

    if(aux3>aux4){
        aux4=aux3;
        pixel_mais_a_direita=(i/desloc)+1;
    }
    if(aux3<aux5){
        aux5=aux3;
        pixel_mais_a_esquerda=(i/desloc)+1;
    }

    pixels[i] = blue;// blue *Pixels;
    pixels[i+1] =green;// green *pixels(i+1);
    pixels[i+2] = red;// red *pixels(I+2);
    }
    else{
    pixels[i] = 255;// blue *Pixels;
    pixels[i+1] = 255;// green *pixels(i+1);
    pixels[i+2] = 255;// red *pixels(I+2);
    }
    }

    else{
    pixels[i] = 0;// blue *Pixels;
    pixels[i+1] = 0;// green *pixels(i+1);
    pixels[i+2] = 0;// red *pixels(I+2);
    }
}
    if(op==7){ // retirar cores
        if(op3 == 1){
            pixels[i+2] = 0; // red *pixels(I+2);
        }
        if(op3 == 2){
            pixels[i+1] = 0; // green *pixels(i+1);
        }
        if(op3 == 3){
            pixels[i+2] = 0; // red *pixels(I+2);
            pixels[i+1] = 0; // green *pixels(i+1);
        }
        if(op3 == 4){
            pixels[i] = 0;   // blue *Pixels;
        }
        if(op3 == 3){
            pixels[i+2] = 0; // red *pixels(I+2);
            pixels[i+1] = 0; // green *pixels(i+1);
        }
        if(op3 == 5){
            pixels[i+2] = 0; // red *pixels(I+2);
            pixels[i] = 0;   // blue *Pixels;
        }
        if(op3 == 6){
            pixels[i+1] = 0; // green *pixels(i+1);
            pixels[i] = 0;   // blue *Pixels;
        }

    }

}

if(op==6){
    int altura;//altura do objeto
    aux= pixel_mais_abaixo / inf.largura_imagem; // linha pixel mais abaixo
    aux2= pixel_mais_acima / inf.largura_imagem; // linha pixel mais acima
    altura=aux2-aux+1;

    int largura; // largura do objeto
    largura= aux4 - aux5 + 1;
    printf("\n\nAltura do objeto: %i\nLargura do objeto: %i\n", altura, largura);
}

fwrite(pixels,size_i,1,ponteiro_imagem);//escreve os dados de pixels no arquivo

fclose(ponteiro_imagem);

printf("\n\n");

return 0;
}
