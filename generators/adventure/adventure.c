#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct adventureNode{
	char data[255];
}AdventureNode;

char* getAdventureData(char* dir){
	FILE* file = fopen(dir,"r");
	char whoPart[255];
    int i = -1;
    
    while(!feof(file)){    
		fgets(whoPart,255,file);
		i++;
	}
	
	rewind(file);
	
	AdventureNode* whoList = calloc(i,sizeof(AdventureNode));
	
	int c = 0;
	
	while(c<i){    
		fgets(whoPart,255,file);
		strcpy(whoList[c].data,whoPart);
		c++;
	}
	
	/*
	int d;
	for(d = 0; d < i;d++){
		printf("\n\nElemento: %s \n\n",whoList[d].data);	
	}*/
	
	srand(time(NULL));
	int randNum = (rand() % (i-1));
	
	return whoList[randNum].data;
}

char* condition(){
	char conditionList[5][255] = {"Porem, esta missao eh uma armadilha",
					"Alem disso, o grupo precisa concluir esta missao em ate cinco dias",
					"Porem, o grupo nao podem usar itens magicos nessa missao, pois existem serios riscos em relacao a mana.",
					"Alem disso, durante a missao, o grupo vai conhecer um velho mago que ira perseguir todos durante toda a missao",
					"Tambem, durante a missao, o grupo vai se encontrar com um velho conhecido."
					};				
	srand(time(NULL)+20);
	int randNum = (rand()%10);
	if(randNum >= 5){
		char* sentence = (char*) calloc(255,sizeof(char));
		srand(time(NULL)+220);
		randNum = (rand()%4);
		strcpy(sentence,conditionList[randNum]);
		return sentence;
	}else{
		return " ";
	}
}
