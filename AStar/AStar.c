#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fila.c"

#define maxX 11
#define maxY 13
#define barreira 0
#define token 100


typedef struct Custo {
	int cost;//x e y eh o indice do mapa (ja ta no mapa)
	int key;//x*100+y
	int onOpenList,onClosedList;

	int acumulado;

}Custo;

	//const int maxX=11, maxY=13, barreira=0; 
	Custo mapa[maxX][maxY];	
	int mapaPeso[maxX][maxY]={
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
/*
int getTamanho(no *head,int key) {
	if(!head) return 0;
	 no* temp;
	 int i=0;
	for(temp = head; temp; temp = temp->next, i++) {
		if(temp->key == key) return i;
	}
	return 0;
}
void queueToArray(int* a, int tamanho, no *head){
	int i;
	a[0]=head->key;
	no *temp;
	for(temp=head->next, i=1;i<=tamanho;i++, temp=temp->next){
		a[i]=temp->key;
	}

}

void radixsort(int vetor[], int tamanho) {
    int i;
    int b[tamanho];
    int maior = vetor[0];
    int exp = 1;
 
    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }
 
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++; 
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }
}*/

//atualiza um valor dos atributos da coordenada
void atualizar(int key, int opcao){
	switch(opcao){
		case 1:
			mapa[(key/token)][(key%token)].onOpenList= !mapa[(key/token)][(key%token)].onOpenList;
		break;
		case 2:
			mapa[(key/token)][(key%token)].onClosedList= !mapa[(key/token)][(key%token)].onClosedList;
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

int verifyPontos(int a, int b){ //euclides quadratico, distancia de dois pontos
	int startX= a/100, endX= b/100, startY=a%100, endY=b%100;
	return abs((float) sqrt(pow(startX - endX, 2) + pow(startY - endY, 2)))==1;
}

no *openlist=NULL,*closedlist=NULL, *listaCaminho=NULL;	//tudo fifo queue
int** AStar(int fromKey, int toKey){
	int PathFound= 1;

	int comecouLista=0;

	add(&openlist,fromKey,1); //adiciona fromKey na lista de verificacao (eu acho), a oficial é closedlist 
	//o 1 significa atualizar a info de q o no esta na openlist

	add(&openlist,toKey,1);

	while(get(toKey,3)==0){//enquanto a coordenada final nao estiver na lista oficial (closedlist faça...)
		if(eh_vazia(&openlist)==0)//se nao eh vazia
		{
			no current = remover(&openlist);//pega e remove o primeiro elemento da queue (FIFO)
            
            
			if(comecouLista==0){ //eu preciso dessa lista pra pegar o caminho ordenado e sem pulos
				inserir(&listaCaminho,current.key);
				comecouLista++;
			}else if(verifyPontos(getLastKey(&listaCaminho), current.key) == 1){
				inserir(&listaCaminho,current.key);

			}

			add(&closedlist,current.key,2);//adiciona a coordenada atual na lista fechada

			getVizinhosDoPonto(current.key);//coloca os ponto de cima, baixo, esquerda, direita. nessa ordem em global vizinhos[4]

			int i;
			for(i=0;i<=4;i++)
			{
				if(vizinhos[i].cost > barreira && !vizinhos[i].onClosedList) //barreira == 0
				{
					if(!vizinhos[i].onOpenList){
						vizinhos[i].acumulado= vizinhos[i].cost + getNoCost(current.key); //o acumulado do vizinho eh a soma do custo do vizinho + custo do atual
						add(&openlist,vizinhos[i].key,1);
					}
					else
					{
						if(getNoAcumulado(current.key) > vizinhos[i].acumulado + getNoCost(current.key)){ // se acumulado do atual > vizinho acumulado + custo do atual
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

	}
	printf("%s\n", "-------------- aberta");
	imprimir(&openlist);
	printf("%s\n", "-------------- fechada");
	imprimir(&closedlist);
	printf("%s\n", "-------------- listaCaminho");
	imprimir(&listaCaminho);

/*
	int tamanho = getTamanho(closedlist,toKey);
	int a[tamanho];
	queueToArray(a,tamanho,closedlist);
	//printf("o primeiro item do array: %d\n", a[0]);
	radixsort(&a,tamanho+1);
	printf("%s\n", "elementos");
	int kk;
	for(kk=0;kk<=tamanho;kk++){
		printf("%04d\n", a[kk]);
	}*/

	//radixsort(closedlist)
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

	int i=2,j=3, x=0,y=4;
	printf("%s%d\n", "saindo daqui ",mapa[i][j].key);
	printf("%s%d\n", "quero chegar aqui ",mapa[x][y].key);
	AStar(mapa[i][j].key,mapa[x][y].key);
}
