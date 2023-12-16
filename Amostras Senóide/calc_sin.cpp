#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n;
    const float pi=3.1415;
    printf("Digite o numero de amostras desejado: ");
    scanf("%d", &n);
    for(int i=1;i<n+1;i++){
        printf("%.3f\n",(sin((2*pi/n)*i)/2)+0.5);
    }
    system("pause");
    return 0;
}
