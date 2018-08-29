#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int roll(int size,int amount){
    int result = 0;
    int i;
    for(i = 0;i < amount;i++){
        srand(time(NULL)+rand());
        result = result + (rand() % size);
    }

    return result;
}

void dice(){
    char input[255];
    printf("\n=====================================\n");
    printf("\nRPG MANAGER Dicer!\n");
    printf("\n=====================================\n");
    printf("Quais dados voce quer jogar? Ex: 2d12 || Padrao: NdS || N: Numero de dados || S: Lado dos dados\n");
    printf(">> ");
    fgets(input,255,stdin);

    DiceList* dices = newDiceList();

    char * pch;
    char* ch;

    pch = strtok (input,"\n (),{}[]");
    while (pch != NULL)
    {   
        Dice d;
        strcpy(d.name,pch);
        addDice(d,dices);
        pch = strtok (NULL, "\n (),{}[]");   
    }

    int i;
    for(i = 0;i < dices->counter;i++){
        DiceNode* tempD = findDiceById(dices,i);
        char diceName[50];
        strcpy(diceName,tempD->data.name);
        ch = strtok(diceName,"\n d,");
        tempD->data.amount = atoi(ch);
        ch = strtok(NULL,"\n d,");
        tempD->data.size = atoi(ch);
        printf("\n Aleatorio foi: %d \n",roll(tempD->data.size,tempD->data.amount));
    }
    listDices(dices);
}

