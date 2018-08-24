#include <stdio.h>
#include <stdlib.h>
#include "util/util.h"
#include "generators/name/name.h"

void playerMode();
void masterMode();


int main(){
    parseNames();
    int option;
    printf("\nBem vindo ao RPGManager aventureiro, Escolha um modo!\n");
    printf("1 - Modo jogador\n2 - Modo mestre");
    scanf("%d",&option);

        switch(option){
            case 1:
                playerMode();
                break;
            case 2:
                masterMode();
                break;
            default:
                playerMode();
                break;
        }


    return 0;
}

void playerMode(){

}

void masterMode(){
    clear();
    int option;
    do{
        printf("\nBem vindo mestre! escolha uma opcao!\n");
        printf("1 - Gerador de nomes\n2 - Gerador de personagens\n3 - Gerador de NPC's\n");
        scanf("%d",&option);

        switch(option){
            case 0:
                break;
            case 1:
                break;
        }
    }while(option != 0);
    
}


