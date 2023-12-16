#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

#define TAM 9

enum DOS_COLORS {
        PRETO, AZUL, VERDE, CIANO ,VERMELHO, MAGENTA, MARROM,
        LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
        LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
        };

void gotoxy(int coluna, int linha)//coloca o cursor na posi��o x, y do plano da tela
{
        COORD point;
        point.X = coluna; point.Y = linha;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void textcolor(DOS_COLORS iColor)
{
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x00F0;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

// -------------------------------------------------------------------------

void backcolor (DOS_COLORS iColor)
{
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x000F;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}


char nome_do_arquivo[]="arthur_4312";

int cor_digito, cor_fundo, cor_painel;

int cor_fonte=0;

int numero_atual;

int numero_inicial=100;

int matriz[TAM][TAM]={0};

DOS_COLORS retorna_DOS_COLORS(int color){
    switch (color)
    {
    case 0:
        return PRETO;
        break;
    case 1:
        return AZUL;
        break;
    case 2:
        return VERDE;
        break;
    case 3:
        return CIANO;
        break;
    case 4:
        return VERMELHO;
        break;
    case 5:
        return MAGENTA;
        break;
    case 6:
        return MARROM;
        break;
    case 7:
        return LIGHT_GRAY;
        break;
    case 8:
        return DARK_GRAY;
        break;
    case 9:
        return LIGHT_BLUE;
        break;
    case 10:
        return LIGHT_GREEN;
        break;
    case 11:
        return LIGHT_CYAN;
        break;
    case 12:
        return LIGHT_RED;
        break;
    case 13:
        return LIGHT_MAGENTA;
        break;
    case 14:
        return YELLOW;
        break;
    case 15:
        return WHITE;
        break;
    }
}

int retorna(char param[]){
    char c;
    int i;
    int tam=strlen(param);
    char aux[tam+1]={};
    char arquivo_inteiro[100];
    FILE *fp;
    fp = fopen(nome_do_arquivo,"r");

    if (!fp)
        {
            fp = fopen(nome_do_arquivo, "w");
            fprintf(fp,"%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#", "N_ATUAL=", 100, "N_INICIAL=", 100, "COR_DIGITO=", 4, "COR_FUNDO=", 0, "COR_PAINEL=", 8);
            fclose(fp);
        }

    i=0;

    while(1){
        c = getc(fp);
        if(c==EOF)break;
        arquivo_inteiro[i]=c;
        i++;
    }
    arquivo_inteiro[i+1]='\0';

    int fim=i;
    int a=0;
    int gravar=0;
    char numero_string[10];

    for(i=0;i<fim;i++){
        if(gravar==1 && arquivo_inteiro[i]=='#'){
            numero_string[a]='\0';
            break;
        }

        if(gravar==1){
            numero_string[a]=arquivo_inteiro[i];
            a++;
        }

        for(int z=1;z<tam;z++){
            aux[z-1]=aux[z];
        }

        aux[tam-1]=arquivo_inteiro[i];
        aux[tam]='\0';

        if(strcmp(param,aux)==0){
            gravar=1;
        }

    }
    return atoi(numero_string);
}

void gravar_dados(){
    FILE *fp;
    fp= fopen(nome_do_arquivo,"r+");

    if (!fp)
    {
        fp = fopen(nome_do_arquivo, "w");
    }
    fprintf(fp,"%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#", "N_ATUAL=", numero_atual, "N_INICIAL=", numero_inicial, "COR_DIGITO=", cor_digito, "COR_FUNDO=", cor_fundo, "COR_PAINEL=", cor_painel);
    fclose(fp);
}

void ler_dados(){

    FILE *fp;
    fp = fopen(nome_do_arquivo,"r");

    if (!fp)
    {
        fp = fopen(nome_do_arquivo, "w");
        fprintf(fp,"%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#\n%s%03d#", "N_ATUAL=", 100, "N_INICIAL=", 100, "COR_DIGITO=", 4, "COR_FUNDO=", 0, "COR_PAINEL=", 8);
        fclose(fp);
    }
    fclose(fp);

    numero_atual=retorna("N_ATUAL=");
    numero_inicial=retorna("N_INICIAL=");
    cor_digito=retorna("COR_DIGITO=");
    cor_fundo=retorna("COR_FUNDO=");
    cor_painel=retorna("COR_PAINEL=");

    fp = fopen(nome_do_arquivo, "w");
    fclose(fp);
    gravar_dados();

}

void clear(){
    int i,j;
    for(i=0;i<TAM;i++)
        for(j=0;j<TAM;j++){
            matriz[i][j]=0;
        }
}

void numeros(int n){
    clear();
    int i;
    switch (n)
    {
    case 0: //numero 0
        for(i=0;i<7;i++){
            matriz[1][1+i]=1;
            matriz[7][1+i]=1;
            matriz[1+i][1]=1;
            matriz[1+i][7]=1;
        }
        break;
    case 1: //numero 1
        for(i=0;i<7;i++){
            matriz[6][1+i]=1;
            matriz[7][1+i]=1;
        }
        break;
    case 2: //numero 2
        for(i=0;i<7;i++){
            matriz[1+i][1]=1;
            matriz[1+i][7]=1;
            matriz[1+i][4]=1;
        }
        for(i=0;i<4;i++){
            matriz[7][1+i]=1;
            matriz[1][4+i]=1;
        }
        break;
    case 3: //numero 3
        for(i=0;i<7;i++){
            matriz[7][1+i]=1;
            matriz[1+i][1]=1;
            matriz[1+i][7]=1;
            matriz[1+i][4]=1;
        }
        break;
    case 4: //numero 4
        for(i=0;i<7;i++){
            matriz[7][1+i]=1;
            matriz[1+i][4]=1;
        }
        for(i=0;i<4;i++){
            matriz[1][1+i]=1;
        }
        break;
    case 5: //numero 5
        for(i=0;i<7;i++){
            matriz[1+i][1]=1;
            matriz[1+i][7]=1;
            matriz[1+i][4]=1;
        }
        for(i=0;i<4;i++){
            matriz[1][1+i]=1;
            matriz[7][4+i]=1;
        }
        break;
    case 6: //numero 6
        for(i=0;i<7;i++){
            matriz[1][1+i]=1;
            matriz[1+i][7]=1;
            matriz[1+i][4]=1;
        }
        for(i=0;i<4;i++){
            matriz[7][4+i]=1;
        }
        break;
    case 7: //numero 7
        for(i=0;i<7;i++){
            matriz[1+i][1]=1;
            matriz[7][1+i]=1;
        }
        break;
    case 8: //numero 8
        for(i=0;i<7;i++){
            matriz[1+i][1]=1;
            matriz[1+i][7]=1;
            matriz[1+i][4]=1;
            matriz[7][1+i]=1;
            matriz[1][1+i]=1;
        }
        break;
    case 9: //numero 9
        for(i=0;i<7;i++){
            matriz[7][1+i]=1;
            matriz[1+i][1]=1;
            matriz[1+i][4]=1;
        }
        for(i=0;i<4;i++){
            matriz[1][1+i]=1;
        }
        break;
    }
}

int anim[30][34]={
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2,2,2,1,2,2,2,2,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,3,1,1,3,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0,
    0,0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

int anim2[30][34]={
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2,2,1,1,2,2,2,2,1,1,1,1,2,2,2,2,1,1,2,2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2,2,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,2,2,2,2,2,2,2,2,0,
    0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,0,0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

int anim3[30][34]={
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,1,1,1,2,2,2,2,2,0,
    0,2,2,2,2,2,2,1,1,1,1,2,2,2,2,1,1,1,1,2,2,2,2,1,1,1,1,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,2,2,2,2,2,2,2,0,
    0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,2,2,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

void animacao_abertura(int * matriz){
    int j,x=0,y=0;

        for(j=0;j<1020;j++){
            gotoxy(x+68,y+5);
                if(* (matriz+j)==0){
                    textcolor(WHITE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==1){
                    textcolor(retorna_DOS_COLORS(cor_fundo));
                    printf("%c",219);
                }
                else if(* (matriz+j)==2){
                    textcolor(VERMELHO);
                    printf("%c",219);
                }
                else if(* (matriz+j)==3){
                    textcolor(WHITE);
                    printf("%c",219);
                }
                x++;
                if(x==34){
                    x=0;
                    y++;
                }
        }
    }

void abertura(){
    system("color F0");
    for(int k=0;k<5;k++){
        animacao_abertura(anim[0]);
        Sleep(10);
        animacao_abertura(anim2[0]);
        Sleep(10);
        animacao_abertura(anim3[0]);
        Sleep(10);
    }

}

void background(){
cor_fundo=retorna("COR_FUNDO=");

switch (cor_fundo)
    {
    case 0:
        system("color 0F");
        cor_fonte=0;
        break;
    case 1:
        system("color 1F");
        cor_fonte=0;
        break;
    case 2:
        system("color 2F");
        cor_fonte=0;
        break;
    case 3:
        system("color 3F");
        cor_fonte=0;
        break;
    case 4:
        system("color 4F");
        cor_fonte=0;
        break;
    case 5:
        system("color 5F");
        cor_fonte=0;
        break;
    case 6:
        system("color 6F");
        cor_fonte=0;
        break;
    case 7:
        system("color 7F");
        cor_fonte=1;
        break;
    case 8:
        system("color 8F");
        cor_fonte=0;
        break;
    case 9:
        system("color 9F");
        cor_fonte=0;
        break;
    case 10:
        system("color AF");
        cor_fonte=0;
        break;
    case 11:
        system("color BF");
        cor_fonte=0;
        break;
    case 12:
        system("color CF");
        cor_fonte=0;
        break;
    case 13:
        system("color DF");
        cor_fonte=0;
        break;
    case 14:
        system("color EF");
        cor_fonte=0;
        break;
    default:
        system("color F0");
        cor_fonte=1;
        break;
    }
}

void mostra_matriz(int ord){
    int x,y;
    for(x=0;x<TAM;x++)
        for(y=0;y<TAM;y++){
            gotoxy(x+(ord*10)+70,y+15);
                if(matriz[x][y]==0){
                    textcolor(retorna_DOS_COLORS(cor_painel));
                    printf("%c",219);
                }
                else if(matriz[x][y]==1){
                    textcolor(retorna_DOS_COLORS(cor_digito));
                    printf("%c",219);
                }
        }
}

void cronometro(){
    system("cls");
    clear();
    ler_dados();
    int valor=numero_atual;
    int unidade=(valor%100)%10, dezena=(valor%100)/10, centena=valor/100;
    int option, c;

    gotoxy(68,25);
    printf("- Pressione ESPA%cO para come%car -         ", 128, 135);
    numeros(unidade);
    mostra_matriz(2);
    numeros(dezena);
    mostra_matriz(1);
    numeros(centena);
    mostra_matriz(0);
    do{
        gotoxy(102,25);
        fflush(stdin);
        c=getch();
    }while(c!=32);

    if(cor_fonte==0){
        textcolor(WHITE);
    }
    else if(cor_fonte==1){
        textcolor(PRETO);
    }
    gotoxy(68,25);
    printf("- Pressione ESPA%cO para pausar -         ", 128);
    for(int k=unidade;k>=0;k--){
        numeros(unidade);
        mostra_matriz(2);
        numeros(dezena);
        mostra_matriz(1);
        numeros(centena);
        mostra_matriz(0);
        numero_atual=unidade+(dezena*10)+(centena*100);
        if(kbhit()){

            if(getch()==32){
                do{
                    if(cor_fonte==0){
                        textcolor(WHITE);
                    }
                    else if(cor_fonte==1){
                        textcolor(PRETO);
                    }
                    gotoxy(62,25);
                    printf("BACKSPACE - Menu             ESC - Continuar");
                    gotoxy(62,27);
                    printf("ESPA%cO    - Alterar Numero   R   - Recome%car ", 128, 135);
                    option=getch();
                    if(cor_fonte==0){
                        textcolor(WHITE);
                    }
                    else if(cor_fonte==1){
                        textcolor(PRETO);
                    }
                    gotoxy(47,25);              //limpar linha
                    printf("                                                                                 ");
                    gotoxy(47,27);              //limpar linha
                    printf("                                                                                 ");

                    if(option==32){
                        gotoxy(69,25);
                        printf("Digite um novo valor:                  ");
                        gotoxy(91,25);
                        scanf("%i", &valor);
                        unidade=((valor%100)%10)+1;
                        dezena=(valor%100)/10;
                        centena=valor/100;
                        k=unidade;
                    }

                    if(option==8){
                        do{
                        gotoxy(54,25);
                        printf("                                                                              ");
                        gotoxy(27,6);
                        printf(" -  M E N U  -");
                        gotoxy(24,9);
                        printf("O que deseja alterar?");
                        gotoxy(6,11);
                        printf("1 - Cor do Digito   2 - Cor do Fundo    3 - Cor do Painel");
                        gotoxy(46,9);
                        c=getch();
                        if(c=='1'){
                            gotoxy(6,9);
                            printf("               Digite a nova cor do digito:              ");
                            gotoxy(6,11);
                            printf("                                                         ");
                            gotoxy(6,11);
                            printf("0 - Preto");
                            gotoxy(6,12);
                            printf("1 - Azul");
                            gotoxy(6,13);
                            printf("2 - Verde");
                            gotoxy(6,14);
                            printf("3 - Verde-Agua");
                            gotoxy(6,15);
                            printf("4 - Vermelho");
                            gotoxy(6,16);
                            printf("5 - Roxo");
                            gotoxy(6,17);
                            printf("6 - Amarelo");
                            gotoxy(6,18);
                            printf("7 - Branco");
                            gotoxy(6,19);
                            printf("8 - Cinza");
                            gotoxy(6,20);
                            printf("9 - Azul Claro");
                            gotoxy(6,21);
                            printf("10 - Verde Claro");
                            gotoxy(6,22);
                            printf("11 - Verde-Agua Claro");
                            gotoxy(6,23);
                            printf("12 - Vermelho Claro");
                            gotoxy(6,24);
                            printf("13 - Lilas");
                            gotoxy(6,25);
                            printf("14 - Amarelo Claro");
                            gotoxy(6,26);
                            printf("15 - Branco Brilhante");
                            gotoxy(50,9);
                            fflush(stdin);
                            scanf("%i", &cor_digito);
                            gravar_dados();
                            gotoxy(50,6);
                            printf("                 ");
                            for(int t=0;t<23;t++){
                                gotoxy(6,6+t);
                                printf("                                                       ");
                            }
                            numeros(unidade);
                            mostra_matriz(2);
                            numeros(dezena);
                            mostra_matriz(1);
                            numeros(centena);
                            mostra_matriz(0);
                        }
                        if(c=='2'){
                            gotoxy(6,9);
                            printf("               Digite a nova cor do fundo:                  ");
                            gotoxy(6,11);
                            printf("                                                         ");
                            gotoxy(6,11);
                            printf("0 - Preto");
                            gotoxy(6,12);
                            printf("1 - Azul");
                            gotoxy(6,13);
                            printf("2 - Verde");
                            gotoxy(6,14);
                            printf("3 - Verde-Agua");
                            gotoxy(6,15);
                            printf("4 - Vermelho");
                            gotoxy(6,16);
                            printf("5 - Roxo");
                            gotoxy(6,17);
                            printf("6 - Amarelo");
                            gotoxy(6,18);
                            printf("7 - Branco");
                            gotoxy(6,19);
                            printf("8 - Cinza");
                            gotoxy(6,20);
                            printf("9 - Azul Claro");
                            gotoxy(6,21);
                            printf("10 - Verde Claro");
                            gotoxy(6,22);
                            printf("11 - Verde-Agua Claro");
                            gotoxy(6,23);
                            printf("12 - Vermelho Claro");
                            gotoxy(6,24);
                            printf("13 - Lilas");
                            gotoxy(6,25);
                            printf("14 - Amarelo Claro");
                            gotoxy(6,26);
                            printf("15 - Branco Brilhante");
                            gotoxy(49,9);
                            fflush(stdin);
                            scanf("%i", &cor_fundo);
                            gravar_dados();
                            background();
                            gotoxy(49,6);
                            printf("                 ");
                            for(int t=0;t<23;t++){
                                gotoxy(6,6+t);
                                printf("                                                       ");
                            }
                            numeros(unidade);
                            mostra_matriz(2);
                            numeros(dezena);
                            mostra_matriz(1);
                            numeros(centena);
                            mostra_matriz(0);
                        }
                        if(c=='3'){
                            gotoxy(6,9);
                            printf("               Digite a nova cor do painel:              ");
                            gotoxy(6,11);
                            printf("                                                         ");
                            gotoxy(6,11);
                            printf("0 - Preto");
                            gotoxy(6,12);
                            printf("1 - Azul");
                            gotoxy(6,13);
                            printf("2 - Verde");
                            gotoxy(6,14);
                            printf("3 - Verde-Agua");
                            gotoxy(6,15);
                            printf("4 - Vermelho");
                            gotoxy(6,16);
                            printf("5 - Roxo");
                            gotoxy(6,17);
                            printf("6 - Amarelo");
                            gotoxy(6,18);
                            printf("7 - Branco");
                            gotoxy(6,19);
                            printf("8 - Cinza");
                            gotoxy(6,20);
                            printf("9 - Azul Claro");
                            gotoxy(6,21);
                            printf("10 - Verde Claro");
                            gotoxy(6,22);
                            printf("11 - Verde-Agua Claro");
                            gotoxy(6,23);
                            printf("12 - Vermelho Claro");
                            gotoxy(6,24);
                            printf("13 - Lilas");
                            gotoxy(6,25);
                            printf("14 - Amarelo Claro");
                            gotoxy(6,26);
                            printf("15 - Branco Brilhante");
                            gotoxy(50,9);
                            fflush(stdin);
                            scanf("%i", &cor_painel);
                            gravar_dados();
                            gotoxy(50,6);
                            printf("                 ");
                            for(int t=0;t<23;t++){
                                gotoxy(6,6+t);
                                printf("                                                       ");
                            }
                            numeros(unidade);
                            mostra_matriz(2);
                            numeros(dezena);
                            mostra_matriz(1);
                            numeros(centena);
                            mostra_matriz(0);
                        }
                        if(cor_fonte==0){
                            textcolor(WHITE);
                        }
                        else if(cor_fonte==1){
                            textcolor(PRETO);
                        }
                        gotoxy(54,25);
                        printf("- Pressione ESPA%cO para continuar ou BACKSPACE para alterar -         ", 128);
                        do{
                            gotoxy(115,25);
                            fflush(stdin);
                            c=getch();
                        }while(c!=32 && c!=8);
                        }while(c==8);
                        gotoxy(54,25);
                        printf("              - Pressione ESPA%cO para pausar -                ", 128);
                    }

                    if(option=='r' || option=='R'){
                        unidade=1;
                        dezena=0;
                        centena=1;
                        k=unidade;
                    }
                    if(cor_fonte==0){
                        textcolor(WHITE);
                    }
                    else if(cor_fonte==1){
                        textcolor(PRETO);
                    }
                    gotoxy(68,25);
                    printf("- Pressione ESPA%cO para pausar -                              ", 128);
                }while(option!=32 && option!=27 && option!=8 && option!='r' && option!='R');
            }
        }
        if((numero_atual)==0){
            numero_atual=100;
            gravar_dados();
            break;
        }
        gravar_dados();
        unidade--;
        if(k==0){
            dezena--;
            k=10;
            unidade=9;
        }
        if(dezena==-1){
            centena--;
            dezena=9;
        }
        gotoxy(74,18);
        Sleep(1000);
    }
}

int anim_tartaruga1[8][21]={
    0,0,0,0,0,0,0,0,3,2,3,2,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,2,2,2,3,2,2,2,3,0,0,0,0,0,0,0,
    0,0,0,0,0,2,2,2,3,2,3,2,3,2,2,2,0,0,0,0,0,
    0,0,0,0,2,3,2,3,2,2,2,3,2,2,2,2,2,0,0,0,0,
    0,0,0,2,2,2,3,2,2,2,3,2,3,2,2,1,1,0,0,0,0,
    0,0,0,2,2,3,2,3,2,3,2,2,2,3,2,1,0,0,0,0,0,
    0,0,0,2,3,2,2,2,3,2,2,2,2,2,3,1,0,0,0,0,0,
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0
    };

int anim_tartaruga2[8][21]={
    0,0,0,0,0,0,0,0,2,3,2,3,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,3,2,2,2,3,2,2,2,0,0,0,0,0,0,0,
    0,0,0,0,2,2,2,3,2,3,2,3,2,2,2,0,0,0,0,0,0,
    0,0,0,2,2,2,2,2,3,2,2,2,3,2,3,2,0,0,0,0,0,
    0,0,0,1,1,2,2,3,2,3,2,2,2,3,2,2,2,0,0,0,0,
    0,0,0,0,1,2,3,2,2,2,3,2,3,2,3,2,2,0,0,0,0,
    0,0,0,0,1,3,2,2,2,2,2,3,2,2,2,3,2,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0
    };

int anim_tartaruga3[8][21]={
    0,0,0,0,0,0,0,0,3,2,3,2,0,0,0,0,4,1,1,0,0,
    0,0,0,0,0,0,2,2,2,3,2,2,2,3,0,0,4,1,5,0,0,
    0,0,0,0,0,2,2,2,3,2,3,2,3,2,2,2,4,4,4,4,0,
    0,0,0,0,2,3,2,3,2,2,2,3,2,2,2,2,4,4,4,4,0,
    0,0,0,2,2,2,3,2,2,2,3,2,3,2,2,1,1,4,4,0,0,
    0,0,0,2,2,3,2,3,2,3,2,2,2,3,2,1,4,4,4,0,0,
    0,0,0,2,3,2,2,2,3,2,2,2,2,2,3,1,4,4,0,0,0,
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0,0,0
    };

int anim_tartaruga4[8][21]={
    0,0,1,1,4,0,0,0,0,2,3,2,3,0,0,0,0,0,0,0,0,
    0,0,5,1,4,0,0,3,2,2,2,3,2,2,2,0,0,0,0,0,0,
    0,4,4,4,4,2,2,2,3,2,3,2,3,2,2,2,0,0,0,0,0,
    0,4,4,4,4,2,2,2,2,3,2,2,2,3,2,3,2,0,0,0,0,
    0,0,4,4,1,1,2,2,3,2,3,2,2,2,3,2,2,2,0,0,0,
    0,0,4,4,4,1,2,3,2,2,2,3,2,3,2,3,2,2,0,0,0,
    0,0,0,4,4,1,3,2,2,2,2,2,3,2,2,2,3,2,0,0,0,
    0,0,0,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
    };

void animacao_tartaruga(int * matriz, int movimento, int y_inicial){
    int j,x=0,y=0;

        for(j=0;j<168;j++){
            gotoxy(x+movimento,y+(y_inicial*8));
                if(* (matriz+j)==0){
                    textcolor(retorna_DOS_COLORS(cor_fundo));
                    printf("%c",219);
                }
                else if(* (matriz+j)==1){
                    textcolor(WHITE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==2){
                    textcolor(VERDE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==3){
                    textcolor(LIGHT_GREEN);
                    printf("%c",219);
                }
                else if(* (matriz+j)==4){
                    textcolor(MARROM);
                    printf("%c",219);
                }
                else if(* (matriz+j)==5){
                    textcolor(PRETO);
                    printf("%c",219);
                }
                x++;
                if(x==21){
                    x=0;
                    y++;
                }
        }
    }

void tartaruga_direita(int y_inicial){
    int conta_movimento=0;
    for(int l=0;l<20;l++){
    for(int g=0;g<10;g++){
    if(conta_movimento>=150){
        break;
    }
    animacao_tartaruga(anim_tartaruga2[0],conta_movimento,y_inicial);
    Sleep(1);
    conta_movimento+=2;
    animacao_tartaruga(anim_tartaruga1[0],conta_movimento,y_inicial);
    Sleep(1);
    conta_movimento+=2;
    }
    if(conta_movimento>=150){
        break;
    }
    animacao_tartaruga(anim_tartaruga3[0],conta_movimento,y_inicial);
    Sleep(300);
    conta_movimento+=2;
    }
    for(int u=0;u<8;u++){
    gotoxy(150,u+(y_inicial*8));
    printf("                     ");
    }
}

void animacao_tartaruga2(int * matriz, int movimento, int y_inicial){
    int j,x=150,y=0,cont=0;

        for(j=0;j<168;j++){
            gotoxy(x-movimento,y+(y_inicial*8));
                if(* (matriz+j)==0){
                    textcolor(retorna_DOS_COLORS(cor_fundo));
                    printf("%c",219);
                }
                else if(* (matriz+j)==1){
                    textcolor(WHITE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==2){
                    textcolor(VERDE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==3){
                    textcolor(LIGHT_GREEN);
                    printf("%c",219);
                }
                else if(* (matriz+j)==4){
                    textcolor(MARROM);
                    printf("%c",219);
                }
                else if(* (matriz+j)==5){
                    textcolor(PRETO);
                    printf("%c",219);
                }
                x++;
                cont++;
                if(cont==21){
                    x-=21;
                    y++;
                    cont=0;
                }
        }
    }

void tartaruga_esquerda(int y_inicial){
    int conta_movimento=0;
    for(int l=0;l<20;l++){
    for(int g=0;g<10;g++){
    if(conta_movimento>=150){
        break;
    }
    animacao_tartaruga2(anim_tartaruga1[0],conta_movimento,y_inicial);
    Sleep(1);
    conta_movimento+=2;
    animacao_tartaruga2(anim_tartaruga2[0],conta_movimento,y_inicial);
    Sleep(1);
    conta_movimento+=2;
    }
    if(conta_movimento>=150){
        break;
    }
    animacao_tartaruga2(anim_tartaruga4[0],conta_movimento,y_inicial);
    Sleep(300);
    conta_movimento+=2;
    }
    for(int u=0;u<8;u++){
    gotoxy(0,u+(y_inicial*8));
    printf("                     ");
    }

}

int bomb1[16][16]{
    0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,
    0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,2,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,4,4,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,4,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb2[16][16]{
    0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,
    0,0,0,0,0,0,0,0,0,2,2,0,0,0,3,3,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,4,4,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,4,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb3[16][16]{
    0,0,0,0,0,0,0,0,0,0,2,2,3,3,3,0,
    0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,4,4,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,4,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb4[16][16]{
    0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,
    0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,4,4,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,4,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb5[16][16]{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,3,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,4,4,1,1,0,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,4,4,4,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,4,1,1,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb6[16][16]{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,
    0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,
    0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,
    0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,
    0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,
    0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,
    0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,
    0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,
    0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,
    0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb7[16][16]{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,
    0,0,0,0,0,3,3,5,3,3,5,3,3,0,0,0,
    0,0,0,0,0,3,5,5,3,3,5,5,3,0,0,0,
    0,0,0,0,3,5,5,5,5,5,5,5,5,3,0,0,
    0,0,0,0,3,3,3,5,5,5,5,3,3,3,0,0,
    0,0,0,0,3,3,3,5,5,5,5,3,3,3,0,0,
    0,0,0,0,3,5,5,5,5,5,5,5,5,3,0,0,
    0,0,0,0,0,3,5,5,3,3,5,5,3,0,0,0,
    0,0,0,0,0,3,3,5,3,3,5,3,3,0,0,0,
    0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int bomb8[16][16]{
    0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,
    0,0,0,0,0,0,0,0,5,0,5,0,5,0,0,0,
    0,5,5,5,0,0,0,5,5,0,5,5,0,0,5,5,
    0,0,5,5,5,0,5,5,0,0,5,0,5,5,5,0,
    0,0,0,5,5,0,0,5,3,5,5,0,5,5,0,0,
    0,5,0,0,5,5,5,5,5,3,5,5,5,0,0,0,
    0,5,5,5,0,5,5,5,5,3,5,5,5,5,5,5,
    0,0,0,5,5,5,5,5,5,5,5,5,5,5,0,0,
    0,5,0,5,5,5,5,5,5,5,5,3,5,5,5,0,
    0,0,5,0,3,3,3,5,5,5,5,5,3,5,5,5,
    0,0,0,0,5,5,5,5,5,5,5,5,5,5,0,0,
    0,5,5,5,0,5,5,5,3,3,5,5,0,5,5,0,
    0,5,0,5,5,5,5,5,3,3,5,5,5,0,5,0,
    0,0,5,5,0,0,5,5,5,5,5,0,5,5,0,0,
    0,0,5,0,5,5,5,0,0,0,5,5,0,0,5,0,
    0,0,5,0,5,0,0,0,0,0,0,5,0,0,0,0
};

int bomb9[16][16]{
    0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,
    0,0,0,0,0,0,0,0,5,0,5,0,5,0,0,0,
    0,5,5,5,0,0,0,5,5,0,5,5,0,0,5,5,
    0,0,5,5,5,0,5,5,0,0,5,0,5,5,5,0,
    0,0,0,5,5,0,0,5,3,5,5,0,5,5,0,0,
    0,5,0,0,6,6,6,5,6,6,6,6,5,0,0,0,
    0,5,5,5,6,6,6,6,6,6,6,6,5,5,5,5,
    0,0,0,5,6,6,6,0,0,6,6,6,5,5,0,0,
    0,5,0,5,5,6,6,0,0,6,6,3,5,5,5,0,
    0,0,5,0,6,6,6,6,6,6,6,6,3,5,5,5,
    0,0,0,0,6,6,6,6,6,6,6,6,5,5,0,0,
    0,5,5,5,6,6,6,5,6,6,6,6,0,5,5,0,
    0,5,0,5,5,5,5,5,3,3,5,5,5,0,5,0,
    0,0,5,5,0,0,5,5,5,5,5,0,5,5,0,0,
    0,0,5,0,5,5,5,0,0,0,5,5,0,0,5,0,
    0,0,5,0,5,0,0,0,0,0,0,5,0,0,0,0
};

int bomb10[16][16]{
    0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,
    0,0,0,0,0,0,0,0,5,0,5,0,5,0,0,0,
    0,5,5,5,0,0,0,5,5,0,5,5,0,0,5,5,
    0,0,5,5,5,0,5,5,0,0,5,0,5,5,5,0,
    0,0,0,5,5,0,0,5,3,5,5,0,5,5,0,0,
    0,5,0,0,6,6,6,6,0,6,6,6,6,0,0,0,
    0,5,5,5,6,6,0,6,0,6,0,6,6,5,5,5,
    0,0,0,5,6,6,6,0,0,0,6,6,6,5,0,0,
    0,5,0,5,5,6,0,0,0,0,0,6,5,5,5,0,
    0,0,5,0,6,6,6,0,0,0,6,6,6,5,5,5,
    0,0,0,0,6,6,0,6,0,6,0,6,6,5,0,0,
    0,5,5,5,6,6,6,6,0,6,6,6,6,5,5,0,
    0,5,0,5,5,5,5,5,3,3,5,5,5,0,5,0,
    0,0,5,5,0,0,5,5,5,5,5,0,5,5,0,0,
    0,0,5,0,5,5,5,0,0,0,5,5,0,0,5,0,
    0,0,5,0,5,0,0,0,0,0,0,5,0,0,0,0
};

int bomb11[16][16]{
    0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,
    0,0,0,0,0,0,0,0,5,0,5,0,5,0,0,0,
    0,5,5,5,0,0,0,5,5,0,5,5,0,0,5,5,
    0,0,5,0,5,0,0,5,0,0,5,0,5,0,5,0,
    0,0,0,5,0,0,0,0,0,0,5,0,5,5,0,0,
    0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,5,5,5,0,0,0,0,0,0,0,0,0,5,5,5,
    0,0,0,5,0,0,0,0,0,0,0,0,0,5,0,0,
    0,5,0,5,0,0,0,0,0,0,0,0,0,5,5,0,
    0,0,5,0,0,0,0,0,0,0,0,0,0,0,5,5,
    0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,
    0,5,5,0,0,0,0,0,0,0,0,0,0,5,5,0,
    0,5,0,5,0,5,0,5,0,0,0,5,5,0,5,0,
    0,0,5,5,0,0,5,0,0,5,5,0,5,5,0,0,
    0,0,5,0,5,0,5,0,0,0,5,5,0,0,5,0,
    0,0,5,0,5,0,0,0,0,0,0,5,0,0,0,0
};

int bomb_zerada[16][16]{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void desenha_bomb(int * matriz){
    int j,x=0,y=0;

        for(j=0;j<256;j++){
            gotoxy(x+53+25,y+7+5);
                if(* (matriz+j)==0){
                    textcolor(retorna_DOS_COLORS(cor_fundo));
                    printf("%c",219);
                }
                else if(* (matriz+j)==1){
                    textcolor(DARK_GRAY);
                    printf("%c",219);
                }
                else if(* (matriz+j)==2){
                    textcolor(LIGHT_GRAY);
                    printf("%c",219);
                }
                else if(* (matriz+j)==3){
                    textcolor(VERMELHO);
                    printf("%c",219);
                }
                else if(* (matriz+j)==4){
                    textcolor(WHITE);
                    printf("%c",219);
                }
                else if(* (matriz+j)==5){
                    textcolor(MARROM);
                    printf("%c",219);
                }
                else if(* (matriz+j)==6){
                    textcolor(LIGHT_RED);
                    printf("%c",219);
                }
                x++;
                if(x==16){
                    x=0;
                    y++;
                }
        }
    }

void anima_bomb(){
    desenha_bomb(bomb1[0]);
    Sleep(10);
    desenha_bomb(bomb2[0]);
    Sleep(10);
    desenha_bomb(bomb3[0]);
    Sleep(10);
    desenha_bomb(bomb4[0]);
    Sleep(10);
    desenha_bomb(bomb5[0]);
    Sleep(10);
    desenha_bomb(bomb6[0]);
    Sleep(10);
    desenha_bomb(bomb7[0]);
    Sleep(10);
    desenha_bomb(bomb8[0]);
    Sleep(10);
    desenha_bomb(bomb9[0]);
    Sleep(10);
    desenha_bomb(bomb10[0]);
    Sleep(10);
    desenha_bomb(bomb11[0]);
    Sleep(10);
    desenha_bomb(bomb_zerada[0]);
    Sleep(10);
}

int main()
{
    system("MODE con cols=170 lines=44"); //Redimensiona a tela
    system("cls");
    abertura();
    background();
    cronometro();
    int contador=1;
    for(int h=0; h<2;h++){
    tartaruga_direita(contador);
    if(contador==3)break;
    contador++;
    tartaruga_esquerda(contador);
    contador++;
    }
    anima_bomb();
    textcolor(VERMELHO);
    for(int i=0;i<44;i++){
        gotoxy(0,i);
        for(int j=0;j<170;j++){
            printf("%c",219);
        }
    }
    gotoxy(0,0);

    system("pause > NULL");
    return 0;
}
