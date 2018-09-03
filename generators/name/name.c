#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void parseNames(char* path, NameList* nameList){
    char nameJsonPart[255];
    FILE* nameFile = fopen(path,"r");
    char * pch;
    while(!feof(nameFile)){
        CharName nameNode;
        fgets(nameJsonPart,255,nameFile);
        pch = strtok (nameJsonPart,"\n(),{}[]");
        int i = 1;
        while (pch != NULL)
        {   
            switch(i){
                case 1:
                    strcpy(nameNode.name,pch);
                    break;
                case 2:
                    nameNode.sex = atoi(pch);
                    break;
                case 3:
                    nameNode.type = atoi(pch);
                    break;
            }
            i++;  
            pch = strtok (NULL, "\n(),{}[]");
            
        }
        //printf("\n Nome: %s - Sex: %d - Type: %d \n",nameNode.name,nameNode.sex,nameNode.type);
        addName(nameNode,nameList);
    }
    //listNames(nameList);
}

char* getRandomName(NameList* list){
    srand(time(NULL)+rand());    
    int max = list->counter;
    int id = (rand() % max);
    char* returnedName = (char*)calloc(80,sizeof(char));
    NameNode* name = findNameById(list,id);
    strcpy(returnedName,name->name.name);
    return returnedName;
}


void createNewListByParameter( NameList* list,  NameList* newList, int par,int sex, int type){
        NameNode* tempElement = list->first;
        while(tempElement != NULL){
            //printf("ID: %d - Nome: %s - Sexo: %d - Tipo: %d\n",tempElement->id,tempElement->name.name,tempElement->name.sex,tempElement->name.type);
            
            switch(par){
                case 0:
                    if(tempElement->name.sex == sex){
                        addName(tempElement->name,newList);
                    }
                break;
                case 1:
                    if(tempElement->name.type == type){
                        addName(tempElement->name,newList);
                    }
                break;
                default:
                    addName(tempElement->name,newList);
                break;
            }

            tempElement = tempElement->next;
        }
}

char* generateName(NameList* nameList,int sex,int type){
    NameList* namesBySex = newNameList();
    NameList* namesByType = newNameList();

    char* firstName = (char*)calloc(80,sizeof(char));

    if(sex != 0){

        switch(sex){
            case 1:
                createNewListByParameter(nameList,namesBySex,0,sex,type);
            break;
            case 2:
                createNewListByParameter(nameList,namesBySex,0,sex,type);
            break;
            default:
                createNewListByParameter(nameList,namesBySex,0,1,type);
            break;
        }

        if(type != 0){
            createNewListByParameter(namesBySex,namesByType,1,0,type);
        }

    }else{
        if(type != 0){
            createNewListByParameter(namesBySex,namesByType,1,0,type);
        }    
    }

    
    if(isEmpty(namesBySex)){
        if(isEmpty(namesByType)){
            firstName = getRandomName(nameList);
        }else{
            firstName = getRandomName(namesByType);
        }
    }else{
        if(isEmpty(namesByType)){
            firstName = getRandomName(namesBySex);
        }else{
            firstName = getRandomName(namesByType);
        }
    }

    return firstName;
}

void getFullName(char* firstName, char* lastName, char* endString){
    strcat(endString,firstName);
    strcat(endString," ");
    strcat(endString,lastName);
}

