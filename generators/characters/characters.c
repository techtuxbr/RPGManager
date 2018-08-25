#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char classes[6][80] = {"Guerreiro","Mago","Bruxo","Necromancer","Cacador de bruxas","Paladino"};
char races[7][80] = {"Humano","Orc","Elf","Dwarf","Argoniano","Khajiht","Hobbit"};
char karma[10][80] = {"Santo","Puro","Bondoso","Bom","Indecente","Mal","Perverso","Caotico","Caoticamente mal"};
char defects[15][80] = {"Medo de escuro","Arrogante","Egostia","Medo de altura","Ignorante","Odeia pessoas","Odeia Elfos","Odeia outras racas","Cego","Surdo","Mudo","Narcolepsia","Assombrado","Sem medo de nada","Azarado"}; 

int randomNumber(int max,int plus){
    srand(time(NULL) + plus);
    return (rand() % max);
}

Character newCharacter(char* name){
    Character ch;
    strcpy(ch.name,name);
    ch.sex = randomNumber(2,3);
    strcpy(ch.charClass,classes[randomNumber(5,1)]);
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
