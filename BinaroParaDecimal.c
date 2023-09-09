#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char binario[100];

    system("cls");
    
    printf("Digite um numero binario: ");
    scanf("%s", binario);
    
    int tamanho = strlen(binario);
    int decimal = 0;
    int valido = 1;
    
    for (int i = 0; i < tamanho; i++) {
        if (binario[i] != '0' && binario[i] != '1') {
            valido = 0;
            break;
        }
        
        if (binario[i] == '1') {
            decimal += pow(2, tamanho - 1 - i);
        }
    }
    
    if (valido) {
        printf("O valor binario %s em decimal: %d\n", binario, decimal);
    } else {
        printf("Valor invalido! Digite um numero binario.\n");
    }
    
    return 0;
}