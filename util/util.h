#include "util.c"
#include "nameList.c"
#include "diceList.c"
#include "itemList.c"

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
void clearBuffer();
char* concat(const char *s1, const char *s2);
tElemento* inicializarListaComCabeca();
void inserirInicio(tElemento* pInicio, Item i);
int percorrer(tElemento* pInicio);
tElemento* buscar(tElemento* pInicio, int id);
void inserirFim(tElemento* pInicio, Item i);
tElemento* remover(tElemento* pInicio, int id);
int estaVazia(tElemento* pInicio);
void salvarEmArquivo(tElemento* pInicio,char* path);
int tamanho(tElemento* pInicio);