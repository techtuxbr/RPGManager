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
    fflush(stdin);
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
        tempD->data.result = roll(tempD->data.size,tempD->data.amount);
    }


    Dice* diceVector = (Dice*)calloc(dices->counter,sizeof(Dice));
    
    for(i = 0; i < dices->counter;i++){
        DiceNode* tempD = findDiceById(dices,i);
        diceVector[i] = tempD->data;
    }

    int x = 0, y = 0;

    Dice aux; 

    // coloca em ordem crescente (1,2,3,4,5...)  
    for( x = 0; x < dices->counter; x++ )
    {
        for( y = x + 1; y < dices->counter; y++ ) // sempre 1 elemento à frente
        {
            // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
            if ( diceVector[x].result < diceVector[y].result )
            {
                //printf("%s")
                aux = diceVector[x];
                diceVector[x] = diceVector[y];
                diceVector[y] = aux;
            }
        }
    }


    printf("\n ============================================ \n");
    printf("\n Resultados: \n");
    printf("\n ============================================ \n");
    for(i = 0; i < dices->counter;i++){
        printf("\n Dado: %s - Resultado: %d \n",diceVector[i].name,diceVector[i].result);
    }


    //listDices(dices);
}

