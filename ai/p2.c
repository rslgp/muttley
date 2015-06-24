#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "contador.c"
//#include "buscarAlcance.c"

#define esquerda " 0 2 0"
#define direita " 0 4 0"
#define cima " 0 1 0"
#define baixo " 0 3 0"

#define porBomba " 1 0 0"
#define detonar " 0 0 1"

#define vago "----"
#define mato "MMMM"
#define fogo "FFFF"
#define destruido "FF--"
#define bonusBomba "--+B"
#define bonusRange "--+F"

#define strSabotagem1 "0 0 0 0 0 0 0 0 0 0 0 0 0 "

//declarando variaveis
int ident, id, i;
char pixelJogador[3];
//otimizar leitura do mapa (ignorar as pedras quando possivel) if(strcmp("XXXX",temp)==0){  printf("{%d,%d},",i,j);} notepadpp count {
static const int pedras[30][2]={{1,1},{1,3},{1,5},{1,7},{1,9},{1,11},{3,1},{3,3},{3,5},{3,7},{3,9},{3,11},{5,1},{5,3},{5,5},{5,7},{5,9},{5,11},{7,1},{7,3},{7,5},{7,7},{7,9},{7,11},{9,1},{9,3},{9,5},{9,7},{9,9},{9,11}};

typedef struct posicao
{
	int i;
	int j;
}posicao;

posicao posicaoAtualJogador;

//se o mapa fosse um grid de ---- essa struct (doisPixeis) seria um elemento desse grid, onde -- eh 1 pixel
typedef struct doisPixeis
{
	char pixel1[3],pixel2[3];
}doisPixeis;

//um array 11 x 13 de doisPixeis
doisPixeis nossoMapa[11][13];
//cada elemento do mapa possui dois pixeis, -- --
//P1 representa 1 pixel

//funcao de leitura do mapa txt para nosso mapa
void leituraMapatxt()
{
	int i, j;
  char temp[5];

	for(i = 0; i<11; i++)
	{
		for(j = 0; j<13; j++)
		{

			scanf("%s", temp);

      nossoMapa[i][j].pixel1[0] = temp[0];
      nossoMapa[i][j].pixel1[1] = temp[1];

      nossoMapa[i][j].pixel2[0] = temp[2];
      nossoMapa[i][j].pixel2[1] = temp[3];
		}
	}
}

//funcoes para imprimir a saida
void left(){
  printf("%d%s\n",ident,esquerda);
}
void right(){
  printf("%d%s\n",ident,direita);
}
void up(){
  printf("%d%s\n",ident,cima);
}
void down(){
  printf("%d%s\n",ident,baixo);
}

void cBomb(){
  printf("%d%s\n",ident,porBomba);
}
void dBomb(){
  printf("%d%s\n",ident,detonar);
}

//lista as funcoes de movimento em um array de funcoes
void (*acao[6])()= {left, right, up, down, cBomb, dBomb};

posicao posicaoAtual(char* pixelJogador)
{
	posicao posicaoEncontrada;
  if(((strcmp(nossoMapa[0][0].pixel1,"P1"))==0) && ((strcmp(nossoMapa[10][12].pixel1,"P2"))==0))
  {
    //se percebeu que ambos estao na posicao inicial, entao ta no inicio da partida, e nao precisa ler todo o mapa
    (strcmp(pixelJogador,"P1")==0) ? (posicaoEncontrada.i=0,posicaoEncontrada.j = 0) : (posicaoEncontrada.i=10,posicaoEncontrada.j = 12);

  }else{
    int i,j, indiceOtimizacao=0;
  	for(i = 0; i < 11; i++)
  		for(j = 0; j < 13; j++)
  		{
        if(i!=pedras[indiceOtimizacao][0] && j!=pedras[indiceOtimizacao][1])
        {
          //corrigido um erro no strcmp com B3 (B3 fica no pixel2)
    			if(strcmp(nossoMapa[i][j].pixel1, pixelJogador) == 0 || strcmp(nossoMapa[i][j].pixel2, "B3") == 0 )
    			{
            posicaoEncontrada.i = i;
            posicaoEncontrada.j = j;

    				return posicaoEncontrada;

    			}

        }else{
          indiceOtimizacao++;
        }

  		}
  }


}
void interacaoPlataforma(char *argv[])
{
  //void interacaoPlataforma(){

  //atoi retorna um int e recebe um const char *str
  id = atoi(argv[1]);
  //id = 2;

  //definindo se eh p1 ou p2, (boolean) ? true : false
  ( id==1 ) ? strcpy(pixelJogador,"P1") : strcpy(pixelJogador,"P2");

  leituraMapatxt();

  posicaoAtualJogador = posicaoAtual(pixelJogador); //para nao precisar varrer o mapa todo

  ident = atoi(argv[2]);
    //ident = 10;
    //ident=10;

}

//int main(){
  //freopen("entrada.txt","r",stdin);
  //interacaoPlataforma();

int estaAqui(int i, int j){ //se retornar 1 eh true, qlqr coisa eh false
  return (posicaoAtualJogador.i==i && posicaoAtualJogador.j==j);
}

int temBomba(int i, int j){
  char temp[2]="B";
  return (strncmp(nossoMapa[i][j].pixel2,temp,1)==0);
}

//passa um array com 3 posicoes do local do player, passa o local da bomba e a orientacao da bomba em relacao ao player
//void explodirBomba(int localPlayer[3][2], int localBomba[2], int orientacaoBomba)
void explodirBomba(int orientacaoBomba)
{
  //se nao tiver nada obstruido orientacao-> 0 norte, 1 east, 2 sul, 3 west (oeste leste -> we)
  void (*temp[2])();
	//a segunda funcao depende do quadrante do mapa, ou se eh p1 ou p2
  void (*norte[2])()={down,left};
  void (*west[2])()={right, up};
  void (*east[2])()={left, up};
  void (*sul[2])()={up, left};
  switch(orientacaoBomba){
    case 0:
      *temp= *norte;
    break;
    case 1:
      *temp= *east;
    break;
    case 2:
      *temp= *sul;
    break;
    case 3:
      *temp= *west;
    break;

  }

  //if((estaAqui(localPlayer[0][0],localPlayer[0][1]) && temBomba(localBomba[0],localBomba[1])))
	temp[0]();
  //if((estaAqui(localPlayer[1][0],localPlayer[1][1]) && temBomba(localBomba[0],localBomba[1])))
	temp[1]();
//  if((estaAqui(localPlayer[2][0],localPlayer[2][1]) && temBomba(localBomba[0],localBomba[1])))
	dBomb();
}
/*void explodirBombaEsquerda(){
  if((estaAqui(9,12) && temBomba(9,12)) right();
  if((estaAqui(10,12) && temBomba(9,12)) up();
  if((estaAqui(10,11) && temBomba(9,12)) dBomb();
}*/

void receitaTeste(){//movimento de gangorra inicial do bomberman
	  //posicao 10 e 12
	  //int tempLocalPlayer[3][2];
	  //int tempLocalBomba[2];
/*
		FILE * sabotagem1;
		sabotagem1 = fopen ("1alcancebombas.txt", "w");
		if(!sabotagem1){//se ele mudou o nome do arquivo (aumenta o custo)
			rodarSabotagem1();
		}else{//se nao melhor pra gente
			fprintf(sabotagem1, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1,strSabotagem1);
			fclose(sabotagem1);
		}*/
		//busca o alcance idependente do nome, ele acha

	int op = rodarContador()%11;
	switch(op){
		case 0:
			left();
		break;
		case 1:
			cBomb();
		break;
		case 2:
			right();
		// {
		// 	//int tempLocalPlayer[3][2]={{9,12},{10,12},{10,11}};
		// 	//int tempLocalBomba[2]={9,12};
	  //   //explodirBomba(tempLocalPlayer, tempLocalBomba, 3);
	  //   explodirBomba(3);
		// }
		break;
		case 4:
				up();
	//	{
			//int tempLocalPlayer[3][2]={{10,11},{10,12},{9,12}};
			//int tempLocalBomba[2]={10,11};
	    //explodirBomba(tempLocalPlayer, tempLocalBomba, 0);
	    //explodirBomba(0);
		//}
		break;
		case 5:
			dBomb();
		break;
		case 6:
			cBomb();
		break;
		case 7:
			down();
		break;
		case 8:
			left();
		break;
		case 9:
			dBomb();
		break;
		case 10:
			right();
		break;
	}
}

int main(int argc, char *argv[]){
  interacaoPlataforma(argv);

  //configurar Controle
      void (*g)() = (*acao[5]);
      void (*f)() = (*acao[4]);
      void (*s)() = (*acao[3]);
      void (*w)() = (*acao[2]);
      void (*d)() = (*acao[1]);
      void (*a)() = (*acao[0]);
  //fim configurar controle

  //para se mover tem que se localizar no mapa, pq o main so recebe id do jogador e id partida
  //w();
  receitaTeste();
  return 0;

}
