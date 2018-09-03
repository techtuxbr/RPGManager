#include "name.c"

void getFullName(char* firstName, char* lastName, char* endString);
char* getRandomName(NameList* list);
void createNewListByParameter( NameList* list,  NameList* newList, int par,int sex, int type);
char* generateName(NameList* nameList,int sex,int type);
void parseNames(char* path, NameList* nameList);
