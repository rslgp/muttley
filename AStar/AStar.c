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

int** AStar(int fromKey, int toKey){
	int PathFound= 1;

	no *openlist=NULL,*closedlist=NULL;	

	int comecouLista=0;

	inserir(&openlist,fromKey);
	mapa[(fromKey/token)][(fromKey%token)].onOpenList=1;

	printf("%d\n", mapa[(fromKey/token)][(fromKey%token)].onOpenList);




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
