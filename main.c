#include <stdio.h>
#include <stdlib.h>
#include "types/charName.h"
#include "util/util.h"
#include "generators/name/name.h"

void nameGeneratorQuiz(int* sex, int* type);

int main(){

    NameList* firstNames = newNameList();
    NameList* lastNames = newNameList();

    parseNames("./generators/name/names.csv",firstNames);
    printf("\n");
    parseNames("./generators/name/lastnames.csv",lastNames);

    int option;
        do{
            printf("\nBem vindo mestre! escolha uma opcao!\n");
            printf("1 - Gerador de nomes\n2 - Gerador de personagens\n3 - Gerador de NPC's\n");
            scanf("%d",&option);

            int sex;
            int type;

            switch(option){
                case 0:
                    break;
                case 1:
                        nameGeneratorQuiz(&sex,&type);
                        printf("\n================================");
                        char firstName[80];
                        char lastName[80];
                        char generatedName[255];
                        strcpy(firstName,generateName(firstNames,sex,type));
                        strcpy(lastName,getRandomName(lastNames));
                        printf("\n Nome: %s %s \n",firstName,lastName);
                        printf("\n================================\n");
                    break;
            }
        }while(option != 0);

    return 0;
}

void nameGeneratorQuiz(int* sex, int* type){
    clear();
    printf("Gerador de nomes\n");
    printf("Qual o sexo?\n");
    printf("1 - Masculino\n2 - Feminino\n");
    scanf("%d",sex);
    clear();
    printf("Gerador de nomes\n");
    printf("Qual o tipo?\n");
    printf("1 - Fantasia\n2- Bestas\n3 - Oriental\n");
    scanf("%d",type);
    clear();
}


