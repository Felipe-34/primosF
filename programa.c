#include <stdio.h>
#include <stdlib.h>

// atualização fazer tudo em binário para as leituras
// Dicas úteis posso usar o modo de abertura w no onde parou pq o w sempre sobre escreve o conteúdo.
//

typedef unsigned long long int ull;
FILE *listaDePrimos;
FILE *listaDeCompostos;
FILE *ondeParou;

void Eprimo(ull numeroTeste);


int main(){

    int numeroDeTestes;
    ull numeroTeste[1];

    ondeParou = fopen("ondeParou.bin", "rb");

    if(ondeParou == NULL){

        puts("Nao foi possivel abrir o arquivo.");
        return 0; // estudar exit() e perror.
    }

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
            numeroTeste = numeroTeste + 2;
            Eprimo(numeroTeste);

        }
        
    }

    return 0;
}

void Eprimo(ull numeroTeste){

    ull divisores[10]; 
    ull resto;
    ull quociente;

   listaDePrimos = fopen("lista de primos.bin", "rb");

    while((fread(divisores, sizeof(ull), 10, listaDePrimos)) != EOF){

        resto = numeroTeste % divisor;

        if(resto == 0){

            //colocar o numero nos compostos
            listaDeCompostos = fopen("lista de compostos.txt", "a");

            if(listaDeCompostos == NULL){

                puts("erro ao abrir arquivo.");
                exit(-1);
            }

            fprintf(listaDeCompostos, "%llu\n");
            fclose(listaDeCompostos);
            break; //para sair do loop
        }
        if(quociente <= divisor){

            //colocar o numero nos primos
            listaDePrimos = fopen("lista de primos.txt", "a");

            if(listaDePrimos == NULL){

                puts("erro ao abrir arquivo.");
                exit(-1);
            }

            fprintf(listaDePrimos, "%llu\n");
            fclose(listaDePrimos);
            break;
        }
    }

    fclose(listaDePrimos);
}






// O onde parou deve receber o número incrementado em 2.