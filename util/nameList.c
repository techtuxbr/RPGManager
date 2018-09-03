#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNameNode{
    int id;
    CharName name;
    struct sNameNode* next;
}NameNode;

typedef struct sNameHeader{
    NameNode* first;
    int counter;
}NameList;

NameList* newNameList(){
    NameList* tnl = (NameList*)malloc(sizeof(NameList));
    tnl->first = NULL;
    tnl->counter = 0;
    return tnl;
}

void addName(CharName data, NameList* list){
    // Alocando elemento
    NameNode* allocatedData = (NameNode*)malloc(sizeof(NameNode));
    allocatedData->id = list->counter;
    allocatedData->name = data;
    allocatedData->next = NULL;
    
    /*
    printf("\nTeste para ver se foi alocado com sucesso!\n");
    printf("\nID: %d - Conteudo[ name: %s - sex: %d - type: %d ]\n",allocatedData->id,allocatedData->name.name,allocatedData->name.sex,allocatedData->name.type);
    */

    if(list->first == NULL){
        list->first = allocatedData;
    }else if(list->first != NULL && list->first->next == NULL){
        list->first->next = allocatedData;
    }else{
        NameNode* tempElement = list->first;
        NameNode* lastElement = list->first;
        while(tempElement != NULL){
            lastElement = tempElement;
            tempElement = tempElement->next;
        }
        lastElement->next = allocatedData;
    }

    list->counter++;
}

void listNames(NameList* list){
        NameNode* tempElement = list->first;
        while(tempElement != NULL){
            printf("ID: %d - Nome: %s - Sexo: %d - Tipo: %d\n",tempElement->id,tempElement->name.name,tempElement->name.sex,tempElement->name.type);
            tempElement = tempElement->next;
        }
}

int isEmpty(NameList* list){
    if(list->first == NULL){
        return 1; 
    }else{
        return 0;
    }
}

NameNode* findNameById(NameList* list, int id)
{
    NameNode* tempElement = list->first;
    while(tempElement != NULL){
        if(tempElement->id == id){
            return tempElement;
        }
        tempElement = tempElement->next;
    }
    
    return NULL;
}

