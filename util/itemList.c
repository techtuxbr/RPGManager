#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Autor: Bruno Monteiro
// Objetivo: Lista encadeada com elemento cabeça

// Tipo do Elemento
typedef struct sElemento
{
    int id;                     // ID
	Item item;   
	struct sElemento* pProx;    // Ponteiro para próximo elemento
} tElemento;

tElemento* inicializarListaComCabeca()
{
	// Aloca espaço para elemento CABEÇA
    tElemento* p = (tElemento*) calloc( 1, sizeof(tElemento) );
	// Inicializa campos do elemento
	
	strcpy(p->item.name, "");
    strcpy(p->item.description, "");
	p->id = 1;
    p->pProx = NULL;

    return p;
}


void inserirInicio(tElemento* pInicio, Item i)
{
	// Aloca espaço para elemento NOVO
	tElemento* pNovo = (tElemento*) calloc( 1, sizeof(tElemento) );
	// Inicializa campos do elemento
	strcpy(pNovo->item.name, i.name);
    strcpy(pNovo->item.description, i.description);
    pNovo->id = pInicio->id;
	pNovo->pProx = NULL; 
    
	// Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
    pInicio->id = pInicio->id + 1; 

	// Anexa elemento NOVO (cuidado com a ordem! Dica: comece atribuindo os campos NULL)
	pNovo->pProx = pInicio->pProx;
	pInicio->pProx = pNovo;
}

int percorrer(tElemento* pInicio)
{
	// Inicializações
    int i = 0;						// Quantidade de elementos
    tElemento* p = pInicio->pProx; 	// Ponteiro temporario. Pulo o elemento cabeça.

	// Verifico se Lista é vazia
	if(p == NULL) {
		printf("OPS! LISTA VAZIA!!! \n");
		return 0;
	}

	// Percorro lista
	while (p != NULL)
	{
        i++;
        printf("\n");
        /*printf("i: %d\n", i);
		printf("p: %d \n", p);*/
        printf("ID: %d\n", p->id);
        printf("Nome: %s\n", p->item.name);
        printf("Descricao: %s\n", p->item.description);
        //printf("pProx: %d\n", p->pProx);
        printf("\n");
        p = p->pProx;
	}

	//printf("Quantidade de Elementos = %d \n", i);
    return i; // Bônus: retorna a quantidade de elementos da lista
}

int tamanho(tElemento* pInicio)
{
	// Inicializações
    int i = 0;						// Quantidade de elementos
    tElemento* p = pInicio->pProx; 	// Ponteiro temporario. Pulo o elemento cabeça.

	// Verifico se Lista é vazia
	if(p == NULL) {
		return 0;
	}

	// Percorro lista
	while (p != NULL)
	{
        i++;

        p = p->pProx;
	}

	//printf("Quantidade de Elementos = %d \n", i);
    return i; // Bônus: retorna a quantidade de elementos da lista
}


void salvarEmArquivo(tElemento* pInicio,char* path){

    tElemento* p = pInicio->pProx;	// Ponteiro temporario. Pulo o elemento cabeça.	
		// Percorro lista
	FILE* file = fopen(path,"w");
	while (p != NULL)
	{
        fprintf(file,"%s,%s\n",p->item.name,p->item.description);
        p = p->pProx;
	}
	fclose(file);
}

tElemento* buscar(tElemento* pInicio, int id)
{
	// Inicializações
    tElemento* p = pInicio->pProx; 	// Ponteiro temporario. Pulo a cabeça da lista. 

    while (p != NULL) 	// verifica se já chegou no final da lista
    {
        if (p->id == id) {
           return p;
        }

        p = p->pProx; // vai para o pProxio elemento
    }
    
    return NULL;
}


void inserirFim(tElemento* pInicio, Item i)
{
	// Aloca espaço para elemento NOVO
	tElemento* pNovo = (tElemento*) calloc(1, sizeof(tElemento) );
	// Inicializa campos do elemento
	strcpy(pNovo->item.name, i.name);
    strcpy(pNovo->item.description, i.description);
    pNovo->id = pInicio->id;
    pNovo->pProx = NULL; 

    // Atualiza elemento CABEÇA (incrementa o próximo valor do ID)
    pInicio->id = pInicio->id + 1;

	// Percorre ate o ultimo elemento
    tElemento* p = pInicio;

    while (p->pProx != NULL) {
        p = p->pProx;
    }
    
    // Anexa elemento NOVO
    p->pProx = pNovo;
}

tElemento* buscarAnterior(tElemento* pInicio, int id)
{
	// Inicializações
    tElemento* p 	  = pInicio; 	// Ponteiro temporario. NÃO ignoro o elemento inicial!
	tElemento* result = NULL;

	if(pInicio->pProx == NULL) 	// Verifica se lista é vazia
	{
		result = NULL;
	}	
	else
	{
        result = pInicio;

		while (p != NULL)
    	{
	        if (p->id == id) {
	           return result;
	        }

			result = p;		// Armazena o ponteiro anterior
        	p = p->pProx;
    	}
	}

    return NULL;
}

tElemento* remover(tElemento* pInicio, int id)
{
	// Inicializações
    tElemento* anterior = buscarAnterior(pInicio, id);
    tElemento* p = NULL;
    
    if(anterior == NULL)
    {
    	printf("anterior NULL. Nao existe elemento com esse id \n");
    	return NULL;
    }
    else
    {
    	p = anterior->pProx;
    	
        anterior->pProx = p->pProx;
        p->pProx = NULL;
        // OBS: se quiser remover sem retornar, usar free() para liberar memória
    }
	
	return p;
}

int estaVazia(tElemento* pInicio)
{
	// Inicializações
    int i = 0;						// Quantidade de elementos
    tElemento* p = pInicio->pProx; 	// Ponteiro temporario. Pulo o elemento cabeça.

	// Verifico se Lista é vazia
	if(p == NULL) {
		return 1;
	}else{
		return 0;
	}
}
