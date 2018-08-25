#include "util.c"
#include "nameList.c"
void clear();
NameList* newNameList();
void addName(CharName data, NameList* list);
void listNames(NameList* list);
int isEmpty(NameList* list);
NameNode* findNameById(NameList* list, int id);