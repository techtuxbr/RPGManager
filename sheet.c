#include <stdio.h>
#include <stdlib.h>
#include "types/character.h"
#include "types/dice.h"
#include "types/item.h"
#include "types/charName.h"
#include "util/util.h"
#include <time.h>

typedef struct{
    int id;
    char name[80];
    char path[255];
    char itemsPath[255];
}SheetRef;

SheetRef G_CURRENT_SHEET;

void initializeRef();
Character createCharacter();
void saveSheet(Character c, char* sheetFileName);
void printCharacterInfo(Character c);
void createSheet(Character c);
void registerOnRefFile(char* name,char* sheetFileName, char* itemsFileName);
void inMode(Character c);
int refFileShowSaves();
Character loadCharacter();
void levelUp(Character *c);

int main(){
    initializeRef();
    Character sheet;
    int op = 0;
    int ok;
    printf("\n================================\n");
    printf("\nRPGManager virtual sheet!\n");
    printf("\n================================\n");
    printf("\nBem vindo jogador! escolha uma opcao!\n");
    printf("1 - Nova ficha\n2 - Carregar ficha\n>> ");
    scanf("%d",&op);
    switch(op){
        case 1:
            sheet = createCharacter();
            createSheet(sheet);
            ok = 1;
        break;
        case 2:
        ok = refFileShowSaves();
        if(ok){
            sheet = loadCharacter();
        }
        break;
        default:
        break;
    }
    if(ok){
        inMode(sheet);
    }
    return 0;
}

Item createItem(){
    clearBuffer();
    int d;
    Item i;
    printf("\n===== Criar item =====\n");
    printf("Nome: ");
    fgets(i.name,255,stdin);
    strtok(i.name,"\n");
    printf("Descricao: ");
    fgets(i.description,255,stdin);
    strtok(i.description,"\n");
    return i;
}

int refFileShowSaves(){
    printf("\n ======= Fichas salvas ======= \n");
    FILE* file = fopen("./sheet/ref.csv","r");
    char line[255];
    int i = -1;

    while(!feof(file)){
        fgets(line,255,file);
         i++;
    }

    rewind(file);

    SheetRef* refs = (SheetRef*)calloc(i,sizeof(SheetRef));
    
    int c;
    char *pch;
    for(c = 0; c < i;c++){
        refs[c].id = c;
        fgets(line,255,file);
        pch = strtok (line,",\n");
        int i = 1;
        while (pch != NULL)
        {   
            switch(i){
                case 1:
                    strcpy(refs[c].name,pch);
                    break;
                case 2:
                    strcpy(refs[c].path,pch);
                    break;
                case 3:
                    strcpy(refs[c].itemsPath,pch);
                    break;
            }
            i++;  
            pch = strtok (NULL, ",\n"); 
        }
    }
    fclose(file);
    if(i > 0){
        int d;
        for(d = 0; d < i;d++){
            printf("ID: %d - Name: %s\n",refs[d].id,refs[d].name);
        }
        int id;
        printf("Selecione um dos saves acima pelo seu ID: \n>> ");
        scanf("%d",&id);
        if(id <= i-1 && id >= 0){
            printf("\nOK\n");
            G_CURRENT_SHEET = refs[id];
        }else{
            printf("\nCOMO VC EH BURRO KRA\n");
            G_CURRENT_SHEET = refs[0];
        }
        return 1;
    }else{
        printf("Nenhum save criado\n");
        return 0;
    }
}

void registerOnRefFile(char* name,char* sheetFileName, char* itemsFileName){
    FILE* file = fopen("./sheet/ref.csv","a+");
    strcpy(G_CURRENT_SHEET.name,name);
    strcpy(G_CURRENT_SHEET.path,sheetFileName);
    strcpy(G_CURRENT_SHEET.itemsPath,itemsFileName);
    fprintf(file,"%s,%s,%s\n",name,sheetFileName,itemsFileName);
    fclose(file);
}

void saveSheet(Character c, char* sheetFileName){
    FILE* sheetFile = fopen(sheetFileName,"w");
    fprintf(sheetFile,"%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d",c.name,c.sex,c.charClass,c.race,c.karma,c.defects,c.str,c.dex,c.con,c.intel,c.wis,c.hp,c.mana,c.level);
    fclose(sheetFile);
}

void createSheet(Character c){
    char fileName[80];
    sprintf(fileName,"%ld",time(NULL));
    char sheetFileName[100];
    strcpy(sheetFileName,concat("s_",fileName));
    char itemsFileName[100];
    strcpy(itemsFileName,concat("i_",fileName));
    strcpy(sheetFileName,concat("./saves/",sheetFileName));
    strcpy(itemsFileName,concat("./saves/",itemsFileName));
    strcpy(sheetFileName,concat(sheetFileName,".csv"));
    strcpy(itemsFileName,concat(itemsFileName,".csv"));
    saveSheet(c,sheetFileName);
    FILE* itemsFile = fopen(itemsFileName,"w");
    registerOnRefFile(c.name,sheetFileName,itemsFileName);
}

void initializeRef(){
    FILE* file = fopen("./sheet/ref.csv","a+");
    fclose(file);
}

void printCharacterInfo(Character c){
    printf("\n==========================\n");
    printf("Ficha");
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
    printf("\tVida: %d || Magia: %d\n",c.hp,c.mana);
    printf("\tForca: %d \n",c.str);
    printf("\tDestreza: %d \n",c.dex);
    printf("\tConstituicao: %d \n",c.con);
    printf("\tInteligiencia: %d \n",c.intel);
    printf("\tSabedoria: %d \n",c.wis);
    printf("\n==========================\n");
}

Character createCharacter(){
    Character c;
    char wait;
    clear();
    clearBuffer();
    printf("\n================================\n");
    printf("\nCriacao de ficha!\n");
    printf("\n================================\n");
    printf("Digite o nome do personagem: ");
    fgets(c.name,255,stdin);
    strtok(c.name,"\n");
    clear();
    printf("Digite o sexo do personagem:\n 1 - Masculino\n 2 - Feminino\n");
    scanf("%d",&c.sex);
    clear();
    clearBuffer();
    printf("Digite a classe do personagem: ");
    fgets(c.charClass,80,stdin);
    strtok(c.charClass,"\n");
    clear();
    printf("Digite a raca do personagem: ");
    fgets(c.race,80,stdin);
    strtok(c.race,"\n");
    clear();
    printf("Digite o karma do personagem: ");
    fgets(c.karma,80,stdin);
    strtok(c.karma,"\n");
    clear();
    printf("Digite o defeito do seu personagem: ");
    fgets(c.defects,255,stdin);
    strtok(c.defects,"\n");
    clear();
    printf("Digite os seguintes atributos do seu personagem:\n");
    printf("================================================\n");
    printf("Forca: ");
    scanf("%d",&c.str);
    printf("Destreza: ");
    scanf("%d",&c.dex);
    printf("Constituicao: ");
    scanf("%d",&c.con);
    printf("Inteligencia: ");
    scanf("%d",&c.intel);
    printf("Sabedoria: ");
    scanf("%d",&c.wis);
    printf("Vida: ");
    scanf("%d",&c.hp);
    printf("Magia:");
    scanf("%d",&c.mana);
    clear();
    printf("Ficha gerada com sucesso!\n");
    clearBuffer();
    c.level = 1;
    printCharacterInfo(c);
    scanf("%c",&wait);
    clear();
    return c;
}

Character loadCharacter(){
    Character c;
    FILE* file = fopen(G_CURRENT_SHEET.path,"r");
    char *pch;
    char line[255];
    char temp[80];
    fgets(line,255,file);
    pch = strtok (line,",\n");
    int i = 1;
    //c.name,c.sex,c.charClass,c.race,c.karma,c.defects,c.str,c.dex,c.con,c.intel,c.wis,c.hp,c.mana
    while (pch != NULL)
    {   
        switch(i){
            case 1:
                strcpy(c.name,pch);
            break;
            case 2:
                strcpy(temp,pch);
                c.sex = atoi(temp);
            break;
            case 3:
                strcpy(c.charClass,pch);
                break;
            case 4:
                strcpy(c.race,pch);
            break;
            case 5:
                strcpy(c.karma,pch);
            break;
            case 6:
                strcpy(c.defects,pch);
            break;
            case 7:
                strcpy(temp,pch);
                c.str = atoi(temp);    
            break;
            case 8:
                strcpy(temp,pch);
                c.dex = atoi(temp);  
            break;
            case 9:
                strcpy(temp,pch);
                c.con = atoi(temp);  
            break;
            case 10:
                strcpy(temp,pch);
                c.intel = atoi(temp);  
            break;
            case 11:
                strcpy(temp,pch);
                c.wis = atoi(temp);  
            break;
            case 12:
                strcpy(temp,pch);
                c.hp = atoi(temp);  
            break;
            case 13:
                strcpy(temp,pch);
                c.mana = atoi(temp);  
            break;
            case 14:
                strcpy(temp,pch);
                c.level = atoi(temp);    
            break;
            }
            i++;  
            pch = strtok (NULL, ",\n"); 
        }
        return c;
}

void levelUp(Character *c){
    c->str  *= 1.5;
    c->con  *= 1.5;
    c->dex  *= 1.5;
    c->intel  *= 1.5;
    c->wis  *= 1.5;
    c->level++;
}

void readItemFile(tElemento* itemList){
    FILE* file = fopen(G_CURRENT_SHEET.itemsPath,"r");
    char line[255];
    char line2[255];
    int c = -1;

    while(!feof(file)){
        fgets(line2,255,file);
         c++;
    }
    rewind(file);
    char* pch;
    Item item;
    while(!feof(file) && c > 0){
        fgets(line,255,file);
        pch = strtok (line,",\n");
        int i = 1;
        while (pch != NULL)
        {   
            switch(i){
                case 1:
                    strcpy(item.name,pch);
                    break;
                case 2:
                    strcpy(item.description,pch);
                    break;
                }
                i++;  
            pch = strtok (NULL, ",\n"); 
        }
            inserirFim(itemList,item);
        }
    if(c>0){
        remover(itemList,tamanho(itemList));
    }
    fclose(file);
}

void backpack(Character c){
        int op;
        int op2;
        Item item;
        tElemento* itemList;
        do{
        itemList = inicializarListaComCabeca();
        readItemFile(itemList);
        printf("\n================================\n");
        printf("\nMochila de %s\n",c.name);
        printf("\n================================\n");  
        printf("\nBem vindo jogador! escolha uma opcao!\n");
        printf("1 - Ver\n2 - Adicionar\n3 - Remover\n0 - Sair e salvar\n>> ");
        scanf("%d",&op);
        switch(op){
                case 1:
                    if(estaVazia(itemList)){
                        clear();
                        printf("Mochila Vazia");
                    }else{
                        clear();
                        percorrer(itemList);
                    }
                break;
                case 2:
                    clear();
                    item = createItem();
                    inserirFim(itemList,item);  
                    salvarEmArquivo(itemList,G_CURRENT_SHEET.itemsPath);  
                break;
                case 3:
                    percorrer(itemList);
                    printf("\n=======================\nQual dos itens acima voce quer remover? ");
                    scanf("%d",&op2);
                    if(op2 >= 0 && op2 <= tamanho(itemList)){
                        remover(itemList,op2);
                    }
                    salvarEmArquivo(itemList,G_CURRENT_SHEET.itemsPath);  
                break;
            } 
        }while(op != 0);
}

void inMode(Character c){
    clear();
    int op;
    int op2;
    char wait;
    int value;
    do{
        printf("\n================================\n");
        printf("\nFicha de %s\n",c.name);
        printf("Vida: %d || Magia: %d",c.hp,c.mana);
        printf("\n================================\n");
        printf("\nBem vindo jogador! escolha uma opcao!\n");
        printf("1 - Informacoes\n2 - Alterar HP\n3 - Alterar Mana\n4 - Aumentar level\n5 - Mochila\n0 - Sair e salvar\n>> ");
        scanf("%d",&op);
        switch(op){
            case 1:
                printCharacterInfo(c);
                clearBuffer();
                scanf("%c",&wait);
                clear();
            break;
            case 2:
            clear();
            printf("Qual operacao voce quer fazer com o HP?\n1 - Diminuir\n2 - Aumentar\n>>");
            scanf("%d",&op2);
                if(op2 == 1){
                        clear();
                        printf("Digite o valor a ser decrementado do HP: ");
                        scanf("%d",&value);
                        if(value > c.hp){
                            c.hp = 0;
                        }else{
                            c.hp -= value;
                        }
                }else if(op == 2){
                        clear();
                        printf("Digite o valor a ser incrementado no HP: ");
                        scanf("%d",&value);
                        c.hp += value;
                }else{
                        clear();
                        printf("Digite o valor a ser incrementado no HP: ");
                        scanf("%d",&value);
                        c.hp += value;
                }
                break;
            case 3:
            clear();
            printf("Qual operacao voce quer fazer com a Magia?\n1 - Diminuir\n2 - Aumentar\n>>");
            scanf("%d",&op2);
                if(op2 == 1){
                        clear();
                        printf("Digite o valor a ser decrementado da Magia: ");
                        scanf("%d",&value);
                        if(value > c.mana){
                            c.mana = 0;
                        }else{
                            c.mana -= value;
                        }
                }else if(op == 2){
                        clear();
                        printf("Digite o valor a ser incrementado na Magia: ");
                        scanf("%d",&value);
                        c.mana += value;
                }else{
                        clear();
                        printf("Digite o valor a ser incrementado na Magia: ");
                        scanf("%d",&value);
                        c.mana += value;
                }   
            break;
            case 4:
                levelUp(&c);
                printf("Level UP!\nAgora seu nivel eh: %d",c.level);
            break;
            case 5:
                backpack(c);
            break;
            case 0:
            break;
        }
        saveSheet(c,G_CURRENT_SHEET.path);
    }while(op != 0);
}