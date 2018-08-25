#include <stdio.h>
#include <stdlib.h>
#include "types/charName.h"
#include "types/character.h"
#include "util/util.h"
#include "generators/name/name.h"
#include "generators/characters/characters.h"

void nameGeneratorQuiz(int* sex, int* type);
void printCharInfo(Character c);

int main(){
    NameList* firstNames = newNameList();
    NameList* lastNames = newNameList();
    Character myChar;
    parseNames("./generators/name/names.csv",firstNames);
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
                        strcpy(firstName,generateName(firstNames,sex,type));
                        strcpy(lastName,getRandomName(lastNames));
                        printf("\n Nome: %s %s \n",firstName,lastName);
                        printf("\n================================\n");
                    break;
                case 2:
                        myChar = newCharacter(getRandomName(firstNames));
                        clear();
                        printCharInfo(myChar);
                    break;
            }
        }while(option != 0);

    return 0;
}

void printCharInfo(Character c){
    printf("\n==========================\n");
    printf("Personagem gerado");
    printf("\n==========================\n");
    printf("Informacoes\n");
    printf("\tNome: %s\n",c.name);
    switch(c.sex){
        case 1:
            printf("\tSexo: Masculino \n");
            break;
        case 2:
            printf("\tSexo: Feminino \n");
            break;
        default:
            printf("\tSexo: Feminino \n");
            break;
    }
    printf("\tRaca: %s \n",c.race);
    printf("\tClasse: %s \n", c.charClass);
    printf("\tKarma: %s \n",c.karma);
    printf("\tDefeito: %s \n",c.defects);
    printf("Atributos\n");
    printf("\tForca: %d \n",c.str);
    printf("\tDestresa: %d \n",c.dex);
    printf("\tConstituicao: %d \n",c.con);
    printf("\tInteligiencia: %d \n",c.intel);
    printf("\tSabedoria: %d \n",c.wis);
     printf("\n==========================\n");
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


