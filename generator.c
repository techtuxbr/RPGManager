/*
    Tool: RPG Manager 1.0V
    Author: Victor Lima
    License: MIT
    Github: github.com/techtuxbr/rpgmanager
*/
// Imports
    #include <stdio.h>
    #include <stdlib.h>
    #include "types/charName.h"
    #include "types/character.h"
    #include "types/dice.h"
    #include "types/item.h"
    #include "util/util.h"
    #include "generators/name/name.h"
    #include "generators/adventure/adventure.h"
    #include "generators/characters/characters.h"
    #include "generators/encounters/encounters.h"
    #include "dice/dice.h"
// Prototypes
    void nameGeneratorQuiz(NameList* firstNames,NameList* lastNames);
    void characterExporterQuiz(NameList* firstNames);
    void printCharInfo(Character c);
    void encounterGenerator();
    void adventureGenerator(NameList* firstNames);

int main(){
    /*
        Leitura da lista de nomes:
        Ao inicio do programa é feita uma leitura de todos os nomes nos arquivos names.csv e lastnames.csv
        em seguida estes nomes são adicionados à uma lista encadeada.
    */
        NameList* firstNames = newNameList();
        NameList* lastNames = newNameList();
        parseNames("./generators/name/names.csv",firstNames);
        parseNames("./generators/name/lastnames.csv",lastNames);
    /*
        Switch de opções:
        Abaixo está o switch de opções, aonde se mantem a maior parte "usável" do programa.
    */ 
        printf("\n================================\n");
        printf("\nRPGManager generator!\n");
        printf("\n================================\n");
        printf("\nBem vindo mestre! escolha uma opcao!\n");
        int option;
            do{
                // Inicializando variaveis, e textos de controle.
                    
                    printf("1 - Gerador de nomes\n2 - Gerador de personagens\n3 - Gerador de aventuras\n4 - Gerador de encontros\n5 - Dado\n6 - Exportar\n>> ");
                    scanf("%d",&option);
                    int amount;
                    Character myChar;
                switch(option){
                    case 0:
                        break;
                    case 1:
                            /* 
                                Primeira opcao: gerador de nomes
                                Chamada da função que é o quiz do gerador de nomes
                                que vai fazer alguns questionamentos para o usuário a respeito
                                de qual tipo de nome ele quer gerar.
                                ;////////////////////////
                                Recebe a lista de nomes para a gerção aleatória!
                            */
                            nameGeneratorQuiz(firstNames,lastNames);
                        break;
                    case 2:
                            /* 
                                Segunda opção -- Gerador de personagens
                                Recebe um nome aleatório gerado pela função getRandomName();
                            */ 
                            myChar = newCharacter(getRandomName(firstNames));
                            // Chamo o método clear para limpar a tela
                            clear();
                            // Apos o personagem ter sido gerado ele é exibido com o método printCharInfo
                            printCharInfo(myChar);
                        break;
                    case 3:
                        /* 
                            Terceira opção - Gerador de aventuras
                            Recebe a lista de nomes para gerar NPC's com nomes diferentes
                        */
                        adventureGenerator(firstNames);
                        break;
                    case 4:
                        /* 
                            Quarta opção - Gerador de encontros
                        */
                        encounterGenerator();
                        break;
                    case 5:
                        /* 
                            Quinta opção - Dados 
                        */
                        // Limpar tela
                        clear();
                        // Limpar buffer para evitar conflitos entre o fgets e o switch case.
                        clearBuffer();
                        dice();
                        break;
                    case 6:
                        // Sexta opção -- Exportar personagens
                        // Recebe uma lista de nomes firstNames
                        characterExporterQuiz(firstNames);
                        break;
                }
            }while(option != 0);

    return 0;
}

/*
    Função: Adventure Generator
    Descrição: Gera 5 aventuras aleatóriamente
    Parâmetros: NameList* firstNames
        Lista de nomes que o método recebe para gerar o nome dos NPCs
    Retorno:
        Nenhum!
*/
void adventureGenerator(NameList* firstNames){
    clear();
    printf("\n====== Aventuras geradas =======\n");
    int i;
    for(i = 0; i <= 5; i++){
        printf("\n %d - %s chamado(a) %s procura um grupo de aventureiros para %s. %s\n",i+1,getAdventureData("./generators/adventure/who.csv"),getRandomName(firstNames),getAdventureData("./generators/adventure/what.csv"),condition());
    }
    printf("\n================================\n");
}
/*
    Função: EncounterGenerator
    Descrição: Gera 5 encontros aleatorios
    Parâmetros: Nenhum
    Retorno:
        Nenhum!
*/
void encounterGenerator(){
    clear();
    printf("\n====== Encontros geradas ======\n");
    int i;
    for(i = 0; i <= 5; i++){
        printf("\n%d - %s %s apareceu %s\n",i+1,getEncounterData("./generators/encounters/who.csv"),
        getEncounterData("./generators/encounters/weapon.csv"),
        getEncounterData("./generators/encounters/where.csv")
    );
    }
    printf("\n================================\n");
}
/*
    Função: CharacterExporterQuiz
    Descrição: Faz uma lista de perguntas para gerar uma exporção de uma lista de personagens   
    Parâmetros: NameList* firstNames
        Lista de nomes para para poder gerar um nome aleatorio para cada personagem
    Retorno:
        Nenhum!
*/
void characterExporterQuiz(NameList* firstNames){
    clear();
    int op;
    int amount;
    int format;
    printf("\n================================\n");
    printf("\nRPGManager exporter!\n");
    printf("\n================================\n");
    printf("O que voce deseja exportar?\n");
    printf("\t1 - Personagem\n>> ");
    scanf("%d",&op);
    switch(op){
        case 1:
        clear();
        printf("Quantos personagens voce deseja exportar?\n>> ");  
        scanf("%d",&amount);
        clear();
        printf("Em qual formato?\n1 - CSV\n2 - JSON\n>> ");  
        scanf("%d",&format);
        exportCharacter(amount,format,firstNames);
        printf("\nExportado com sucesso!\n");
        break;
        default:
        break;
    } 
}
/*
    Função: PrintCharInfo
    Descrição: Exibe informações de um personagem   
    Parâmetros: Character c
        
    Retorno:
        Nenhum!
*/
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
    printf("\tDestreza: %d \n",c.dex);
    printf("\tConstituicao: %d \n",c.con);
    printf("\tInteligiencia: %d \n",c.intel);
    printf("\tSabedoria: %d \n",c.wis);
     printf("\n==========================\n");
}

void nameGeneratorQuiz(NameList* firstNames,NameList* lastNames){
    int sex, type;
    clear();
    printf("Gerador de nomes\n");
    printf("Qual o sexo?\n");
    printf("1 - Masculino\n2 - Feminino\n>> ");
    scanf("%d",&sex);
    clear();
    printf("Gerador de nomes\n");
    printf("Qual o tipo?\n");
    printf("1 - Fantasia\n2- Bestas\n3 - Oriental\n>> ");
    scanf("%d",&type);
    clear();
    char firstName[80];
    char lastName[80];
    strcpy(firstName,generateName(firstNames,sex,type));
    strcpy(lastName,getRandomName(lastNames));
    printf("========= Nome gerado ==========\n");
    printf(" Nome: %s %s \n",firstName,lastName);
    printf("================================\n");
}


