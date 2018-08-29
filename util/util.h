#include "util.c"
#include "nameList.c"
#include "diceList.c"

void clear();
NameList* newNameList();
void addName(CharName data, NameList* list);
void listNames(NameList* list);
int isEmpty(NameList* list);
NameNode* findNameById(NameList* list, int id);
DiceList* newDiceList();
void addDice(Dice data, DiceList* list);
void listDices(DiceList* list);
DiceNode* findDiceById(DiceList* list, int id);