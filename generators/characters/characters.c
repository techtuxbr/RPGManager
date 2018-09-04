#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char classes[40][80] = {"Guerreiro","Mago","Bruxo","Necromancer","Cacador de bruxas","Paladino","Barbaro","Bardo","Clerigo","Cavaleiro","Druida","Lutador","Monge","Ninja","Nobre","Ranger","Samurai","Samamritano"};
char races[7][80] = {"Humano","Orc","Elf","Dwarf","Argoniano","Khajiht","Hobbit"};
char karma[10][80] = {"Santo","Puro","Bondoso","Bom","Indecente","Mal","Perverso","Caotico","Caoticamente mal"};
char defects[15][80] = {"Medo de escuro","Arrogante","Egostia","Medo de altura","Ignorante","Odeia pessoas","Odeia Elfos","Odeia outras racas","Cego","Surdo","Mudo","Narcolepsia","Assombrado","Sem medo de nada","Azarado"}; 

int randomNumber(int max,int plus){
    srand(time(NULL) + plus + rand());
    return (rand() % max);
}

Character newCharacter(char* name){
    Character ch;
    strcpy(ch.name,name);
    ch.sex = randomNumber(2,3);
    strcpy(ch.charClass,classes[randomNumber(17,1)]);
    strcpy(ch.race,races[randomNumber(6,2)]);
    strcpy(ch.karma,karma[randomNumber(9,3)]);
    strcpy(ch.defects,defects[randomNumber(15,4)]);

    ch.str = randomNumber(10,5);
    ch.dex = randomNumber(10,6);
    ch.con = randomNumber(10,7);
    ch.intel = randomNumber(10,8);
    ch.wis = randomNumber(10,9);

    return ch;
}

void exportCharacter(int amount,int type,NameList* list){
    FILE* file;
    int i;
    switch(type){
        case 1:
            file = fopen("./chars.csv","w");
            fprintf(file,"Nome, Sexo, Classe, Raça,Karma,Defeito,Força,Destreza,Constituição,Inteligência,Sabedoria\n");
            for(i=0;i < amount;i++){
                Character c = newCharacter(getRandomName(list));
                fprintf(file,"%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d\n",c.name,c.sex,c.charClass,c.race,c.karma,c.defects,c.str,c.dex,c.con,c.intel,c.wis);
             }
        break;
        case 2:
            file = fopen("./chars.json","w");
            fprintf(file,"[");
            for(i=0;i < amount;i++){
                Character c = newCharacter(getRandomName(list));
                fprintf(file,"\n\t{\n");
                fprintf(file,"\t\t\"Nome\":\"%s\",\n\t\t\"Sexo\":%d,\n\t\t\"Classe\":\"%s\",\n\t\t\"Raca\":\"%s\",\n\t\t\"Karma\":\"%s\",\n\t\t\"Defeito\":\"%s\",\n\t\t\"Forca \": %d,\n\t\t\"Destreza\": %d,\n\t\t\"Constituicao\":%d,\n\t\t\"Inteligencia\":%d,\n\t\t\"Sabedoria\":%d",c.name,c.sex,c.charClass,c.race,c.karma,c.defects,c.str,c.dex,c.con,c.intel,c.wis);
                if(i == amount-1){
                    fprintf(file,"\n\t}");
                }else{
                    fprintf(file,"\n\t},");
                }
                
             }            
            fprintf(file,"\n]");
        break;
        default:
            file = fopen("./chars.csv","w");
            fprintf(file,"Nome, Sexo, Classe, Raça,Karma,Defeito,Força,Destreza,Constituição,Inteligência,Sabedoria\n");
            for(i=0;i < amount;i++){
                Character c = newCharacter(getRandomName(list));
                fprintf(file,"%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d\n",c.name,c.sex,c.charClass,c.race,c.karma,c.defects,c.str,c.dex,c.con,c.intel,c.wis);
             }
        break;
    }
    fclose(file);
}
