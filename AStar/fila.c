#include <stdio.h>
#include <stdlib.h>
 
// FILA (QUEUE)
typedef struct no {
  int key;
  struct no *next;
} no;
 
//no *head = NULL, *aux;
no *aux;

void inserir(no **head, int key) // push
{
  no *novo = (no*) malloc(sizeof(no));
  novo->key = key;
  novo->next = NULL;
  if(!(*head)) { aux = *head = novo; }
  else {
    aux->next = novo;
    aux = aux->next;
  }

}
 
void pop(no **head) { // pop (erase)
  if((*head)) {
    no *temp = (*head)->next;
    free((*head));
    *head = temp;
  }
}

no remover(no **head){ 
 if((*head)) {
  no *retorno = (no*) malloc(sizeof(no));
  retorno->key = (*head)->key;
  retorno->next = (*head)->next;
    pop(head);
    return *retorno;
  }

}
 
int eh_vazia(no **head) { // empty, is_empty
  return *head == NULL;
}

void imprimir(no **head) {
	if(*head) {
		no* temp;
		for(temp = *head; temp; temp = temp->next)
			printf("%d \n", temp->key);
		printf("\n");
	} else printf("VAZIA\n\n");
}
 
/* 
int main() {
	no *head=NULL;
  inserir(head,1);
  inserir(head,2);
  inserir(head,3);
  inserir(head,4);
  pop(head);
  pop(head);  
  pop(head);
  pop(head);    
  return 0;
}*/