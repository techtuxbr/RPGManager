#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct encounterNode{
	char data[255];
}EncounterNode;

char* getEncounterData(char* dir){
	FILE* file = fopen(dir,"r");
	char whoPart[255];
    int i = -1;
    
    while(!feof(file)){    
		fgets(whoPart,255,file);
		i++;
	}
	
	rewind(file);
	
	EncounterNode* whoList = calloc(i,sizeof(EncounterNode));
	
	int c = 0;
	
	while(c<i){    
		fgets(whoPart,255,file);
		strtok(whoPart,"\n");
		strcpy(whoList[c].data,whoPart);
		c++;
	}
	

	srand(time(NULL)+rand());
	int randNum = (rand() % (i-1));
	
	return whoList[randNum].data;
}