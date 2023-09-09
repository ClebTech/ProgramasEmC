#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char frase[100];
    printf("Digite uma frase: ");
    scanf("%[^\n]s", frase);

    system("cls");
    printf("Frase original: %s\n\n", frase);
    printf("MAIUSCULO: %s\n", strupr(frase));
    printf("MINUSCULO: %s\n", strlwr(frase));

    int comprimento = strlen(frase);

    frase[0] = toupper(frase[0]);

    for(int i=0; i<comprimento; i++){
        if(frase[i-1] == ' '){
            frase[i] = toupper(frase[i]);
        }
    }

    printf("INICIAIS: %s", frase);

    return 0;
}