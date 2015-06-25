#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fila.c"

typedef struct Custo {
	int cost;//x e y eh o indice do mapa (ja ta no mapa)
	int key;//x*100+y
	int onOpenList,onClosedList;

	int acumulado;

}Custo;

	const int maxX=11, maxY=13, barreira=0; 
	Custo mapa[11][13];	
	int mapaPeso[11][13]={
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,0,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,0,0,0},
				{1,1,1,1,1,1,1,0,1,1,1,1,1}
		};	
	int token =100;

//atualiza um valor dos atributos da coordenada
void atualizar(int key, int opcao){
	switch(opcao){
		case 1:
			mapa[(key/token)][(key%token)].onOpenList= !mapa[(key/token)][(key%token)].onOpenList;
		break;
		case 2:
			mapa[(key/token)][(key%token)].onClosedList= !mapa[(key/token)][(key%token)].onOpenList;
		break;

	}

}

//retorna um dos atributos da coordenada (custo, esta na lista)
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

//cria um ponto configurando a chave das coordenadas
void setPonto(Custo *ponto, int x, int y){
	*ponto = mapa[x][y];
	ponto->key= 100*x+y;
}

Custo vizinhos[4];

//pega os vizinhos de uma chave
void getVizinhosDoPonto(int key){
	int x=(key/token),y=(key%token);

	setPonto(&vizinhos[0],x-1,y);//up
	setPonto(&vizinhos[1],x+1,y);//down
	setPonto(&vizinhos[2],x,y-1);//left
	setPonto(&vizinhos[3],x,y+1);//right
	/*
	vizinhos[0]= mapa[x-1][y]; //x - 1 >= 0
	vizinhos[1]= mapa[x+1][y]; //(x + 1 < mWidth)
	vizinhos[2]= mapa[x][y-1]; //(y - 1 >= 0)
	vizinhos[3]= mapa[x][y+1]; //(y + 1 < mHeight)
	*/
	/*
	int i;
	for(i=0;i<4;i++){
		printf("%03d\n", vizinhos[i].key);
	}
	*/
}

int verifyPontos(int a, int b){
	int startX= a/100, endX= b/100, startY=a%100, endY=b%100;
	return abs((float) sqrt(pow(startX - endX, 2) + pow(startY - endY, 2)))==1;
}

void add(no **lista, int key, int opcao){
	inserir(lista,key);
	atualizar(key,opcao);
}

int getNoCost(int key){
	return mapa[key/token][key%token].cost;
}

int getNoAcumulado(int key){
	return mapa[key/token][key%token].acumulado;
}

void setNoAcumulado(int key, int value){
	mapa[key/token][key%token].acumulado=value;
}
no *openlist=NULL,*closedlist=NULL, *listaCaminho=NULL;	
int** AStar(int fromKey, int toKey){
	int PathFound= 1;

	int comecouLista=0;

	//inserir(&openlist,fromKey);
	//atualizar(fromKey,2,1); //Start.onOpenList = true;
	printf("%d\n", eh_vazia(&openlist));
	add(&openlist,fromKey,1);
	printf("%d\n", eh_vazia(&openlist));

	add(&openlist,toKey,1);

	int loop=0;
	//while(get(toKey,3)==0){
	while(loop!=5){
		//printf("%d\n", eh_vazia(&openlist));
		if(eh_vazia(&openlist)==0)//nao eh vazia
		{
			no current = remover(&openlist);
			//printf("%d\n", current.key);
			//printf("%d\n", eh_vazia(&openlist));
			if(comecouLista==0){
				inserir(&listaCaminho,current.key);
				comecouLista++;
			}else if(verifyPontos(listaCaminho->key, current.key))
				inserir(&listaCaminho,current.key);

			add(&closedlist,current.key,2);
			//printf("%d\n", current.key);
			getVizinhosDoPonto(current.key);

			int i;
			for(i=0;i<=4;i++)
			{
				if(vizinhos[i].cost > barreira && !vizinhos[i].onClosedList)
				{
					if(!vizinhos[i].onOpenList){
						vizinhos[i].acumulado= vizinhos[i].cost + getNoCost(current.key); //acumulado
						add(&openlist,vizinhos[i].key,1);
					}
					else
					{
						if(getNoAcumulado(current.key) > vizinhos[i].acumulado + getNoCost(current.key)){
							setNoAcumulado(current.key,getNoCost(current.key) + vizinhos[i].cost);
							add(&openlist,current.key,1);
						}


					}
				}
			}

		}
		else
		{
			PathFound= 0;
			break;
		}

		loop++;
	}
	printf("%s\n", "-------------- aberta");
	imprimir(&openlist);
	printf("%s\n", "-------------- fechada");
	imprimir(&closedlist);
}

	//}

	//printf("%d\n", get(fromKey,2));

//configura as chaves de cada coordenada
void setKey(int i,int j){
	mapa[i][j].key = i*100+j;
}
void setCost(int i, int j, int cost){
	mapa[i][j].cost = cost;

} 

void setAllKeyPeso(){
	int i,j;
	for(i=0;i<=maxX;i++){
		for(j=0;j<=maxY;j++){
			setKey(i,j);
			setCost(i,j, mapaPeso[i][j]);
		}
	}
}

//retorna a coordenada apartir da chave
Custo* getCoord(int key){
	//a[0]=key/token;
	//a[1]=key%token;

	return &mapa[(key/token)][(key%token)];
}

int main(){
	//Custo mapa[11][13];

	//setKey(i,j);
	//getVizinhosDoPonto(mapa[i][j].key);
	//getVizinhosDoPonto(mapa[5][10].key);


	//mapa[i][j].key=setKey(mapa[i][j]);
	/*
	printf("%d\n", mapa[i][j].key);
*/
	//AStar(mapa,mapa[i][j].key,mapa[i][j].key+1);		
	setAllKeyPeso();

	int i=1,j=3;
	printf("%s%d\n", "saindo daqui ",mapa[i][j].key);
	printf("%s%d\n", "quero chegar aqui ",mapa[i][j].key+2);
	AStar(mapa[i][j].key,mapa[i][j].key+2);
}
