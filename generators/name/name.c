#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SCharName{
    char name[80];
    int sex;
    int type;
}CharName;

void parseNames(){
    char nameJsonPart[255];
    FILE* nameFile = fopen("./generators/name/names.csv","r");

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
        printf("\n Nome: %s - Sex: %d - Type: %d \n",nameNode.name,nameNode.sex,nameNode.type);
        
    }

}