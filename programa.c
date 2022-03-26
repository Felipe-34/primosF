#include <stdio.h>
#include <stdlib.h>
#define tamanhoMax 18446744073709551615
// Tenho que criar uma lógica para pular os numeros terminados em 5 porque todo o número terminado em 5 é divisivel por 5.

typedef unsigned long long int ull;
FILE *listaDePrimos;
FILE *listaDeCompostos;
FILE *ondeParou;

int Eprimo(ull numeroTeste);
void checkfopen(FILE *Fptr);

int main(){

    int numeroDeTestes, testePrimo;
    ull numeroTeste[1];

    ondeParou = fopen("ondeParou.bin", "rb");
    checkfopen(ondeParou);
    fread(numeroTeste, sizeof(ull), 1, ondeParou); 
    fclose(ondeParou);

    while(1){
        
        puts("Quantos numeros quer testar? Digite -1 para encerar o programa.");
        scanf("%d", &numeroDeTestes);
        
        if(numeroDeTestes == -1){

            return 0;
        }

        for(size_t i = 0; i < numeroDeTestes; i++)
        {
            numeroTeste[0] = numeroTeste[0] + 2;
            if (numeroTeste[0] > tamanhoMax)
            {
                puts("O programa nao pode mais executar porque o numero a ser testado ultrapassou o tamanho limite.");
            }
            testePrimo = Eprimo(numeroTeste[0]);

            if (testePrimo == 1)
            {
                listaDePrimos = fopen("lista de primos.bin", "ab");
                checkfopen(listaDePrimos);
                fwrite(numeroTeste, sizeof(ull), 1, listaDePrimos);
                fclose(listaDePrimos);
            }else{

                listaDeCompostos = fopen("lista de compostos.bin", "ab");
                checkfopen(listaDeCompostos);
                fwrite(numeroTeste, sizeof(ull), 1, listaDeCompostos);
                fclose(listaDeCompostos);
            }
            
            if (i == numeroDeTestes - 1)
            {
                ondeParou = fopen("ondeParou.bin", "wb");
                checkfopen(ondeParou);
                fwrite(numeroTeste, sizeof(ull), 1, ondeParou);
                fclose(ondeParou);
        
            }
            
        }
        
    }

    return 0;
}

int Eprimo(ull numeroTeste){// se primo return 1 senao 2

    ull divisores[1];
    ull resto;
    ull quociente;

    listaDePrimos = fopen("lista de primos.bin", "rb");
    checkfopen(listaDePrimos);

    do
    {
        fread(divisores, sizeof(ull), 1, listaDePrimos);

        resto = numeroTeste % divisores[0];
        quociente = numeroTeste / divisores[0];

        if (resto == 0)
        {
            fclose(listaDePrimos);
            return 2;
        }
        
    } while (divisores[0] < quociente); //talvez precise acrescentar  && !feof(listaDePrimos);
    
    fclose(listaDePrimos);

    return 1;

}

void checkfopen(FILE *Fptr){

    if (Fptr == NULL)
    {
        puts("erro ao abrir o arquivo.");// posso substituir por perror.
        exit(EXIT_FAILURE);
    }
}