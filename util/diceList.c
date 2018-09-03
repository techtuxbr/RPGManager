#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sDiceNode{
    int id;
    Dice data;
    struct sDiceNode* next;
}DiceNode;

typedef struct sDiceHeader{
    DiceNode* first;
    int counter;
}DiceList;

DiceList* newDiceList(){
    DiceList* tnl = (DiceList*)malloc(sizeof(DiceList));
    tnl->first = NULL;
    tnl->counter = 0;
    return tnl;
}

void addDice(Dice data, DiceList* list){

    DiceNode* allocatedData = (DiceNode*)malloc(sizeof(DiceNode));
    allocatedData->id = list->counter;
    allocatedData->data = data;
    allocatedData->next = NULL;
    
    if(list->first == NULL){
        list->first = allocatedData;
    }else if(list->first != NULL && list->first->next == NULL){
        list->first->next = allocatedData;
    }else{
        DiceNode* tempElement = list->first;
        DiceNode* lastElement = list->first;
        while(tempElement != NULL){
            lastElement = tempElement;
            tempElement = tempElement->next;
        }
        lastElement->next = allocatedData;
    }

    list->counter++;
}


void listDices(DiceList* list){
        DiceNode* tempElement = list->first;
        while(tempElement != NULL){
            printf("ID: %d - Nome: %s - Lados: %d - Quantidade: %d - Resultado: %d\n",tempElement->id,tempElement->data.name,tempElement->data.size,tempElement->data.amount,tempElement->data.result);
            tempElement = tempElement->next;
        }
}

/*
int isEmpty(NameList* list){
    if(list->first == NULL){
        return 1; 
    }else{
        return 0;
    }
}*/

DiceNode* findDiceById(DiceList* list, int id)
{
    DiceNode* tempElement = list->first;
    while(tempElement != NULL){
        if(tempElement->id == id){
            return tempElement;
        }
        tempElement = tempElement->next;
    }
    
    return NULL;
}
