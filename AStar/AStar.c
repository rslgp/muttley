#include <stdio.h>
#include <stdlib.h>

#include "fila.c"

typedef struct Custo {
	int cost;//x e y eh o indice do mapa (ja ta no mapa)
	int key;//x*100+y
	int onOpenList,onClosedList;

}Custo;

	int coord[2]; 
	Custo mapa[11][13];	
	int token =100;

void atualizar(int key, int opcao, int value){
	switch(opcao){
		case 1:		
			mapa[(key/token)][(key%token)].cost=value;
		break;
		case 2:
			mapa[(key/token)][(key%token)].onOpenList=value;
		break;
		case 3:
			mapa[(key/token)][(key%token)].onClosedList=value;
		break;

	}

}
int get(int key, int opcao){
	switch(opcao){
		case 1:		
			return mapa[(key/token)][(key%token)].cost;
		break;
		case 2:
			return mapa[(key/token)][(key%token)].onOpenList;
		break;
		case 3:
			return mapa[(key/token)][(key%token)].onClosedList;
		break;

	}

}

int** AStar(int fromKey, int toKey){
	int PathFound= 1;

	no *openlist=NULL,*closedlist=NULL, *listaCaminho=NULL;	
	int comecouLista=0;

	inserir(&openlist,fromKey);
	atualizar(fromKey,2,1);

	//while(!(get(toKey,3)==1)){
		printf("%d\n", eh_vazia(&openlist));
		if(eh_vazia(&openlist)==0)//nao eh vazia
		{
			no current = remover(&openlist);
			//printf("%d\n", current.key);
			//printf("%d\n", eh_vazia(&openlist));

		}

	//}

	printf("%d\n", get(fromKey,2));




}

int setKey(int x,int y){
	return x*100+y;
}

Custo* getCoord(int key){
	//a[0]=key/token;
	//a[1]=key%token;

	return &mapa[(key/token)][(key%token)];
}

int main(){
	//Custo mapa[11][13];

	int i=1,j=2;
	mapa[i][j].key=setKey(i,j);
	//mapa[i][j].key=setKey(mapa[i][j]);
	/*
	printf("%d\n", mapa[i][j].key);
	int coord[2];
	getCoord(coord,mapa[i][j].key);
	printf("%d\n", coord[0]);
	printf("%d\n", coord[1]);
*/
	//AStar(mapa,mapa[i][j].key,mapa[i][j].key+1);
	AStar(mapa[i][j].key,mapa[i][j].key+1);
}
