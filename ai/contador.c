#include<stdio.h>

#define arquivoPosicaoBin "dado1.bin"

	/* Our structure */
	struct estruturaContador
	{
		int x;
	};

  int rodarContador(){
    FILE *arquivoPosicao;
		struct estruturaContador contador;

    arquivoPosicao=fopen(arquivoPosicaoBin,"rb");
		if (!arquivoPosicao)
		{
    	arquivoPosicao=fopen(arquivoPosicaoBin,"wb");
      contador.x=0;
      fwrite(&contador, sizeof(struct estruturaContador), 1, arquivoPosicao);
      fclose(arquivoPosicao);
      return contador.x;
		}else{
  		fread(&contador,sizeof(struct estruturaContador),1,arquivoPosicao);

  		fclose(arquivoPosicao);

      contador.x+=1;

  		arquivoPosicao=fopen(arquivoPosicaoBin,"wb");

  		fwrite(&contador, sizeof(struct estruturaContador), 1, arquivoPosicao);

  		fclose(arquivoPosicao);
  		return contador.x;
    }
  }

	// int main()
	// {
    // while(1){
    //   printf("%d\n",rodarContador());
    // }


		// FILE *arquivoPosicao;
		// struct estruturaContador contador;
    //
    // arquivoPosicao=fopen(arquivoPosicaoBin,"rb");
		// if (!arquivoPosicao)
		// {
    // 	arquivoPosicao=fopen(arquivoPosicaoBin,"wb");
    //   contador.x=1;
    //   fwrite(&contador, sizeof(struct estruturaContador), 1, arquivoPosicao);
    //
		// }else{
  	// 	fread(&contador,sizeof(struct estruturaContador),1,arquivoPosicao);
  	// 	printf("%d\n",contador.x);
    //
  	// 	fclose(arquivoPosicao);
    //
    //   contador.x+=1;
    //
  	// 	arquivoPosicao=fopen(arquivoPosicaoBin,"wb");
    //
  	// 	fwrite(&contador, sizeof(struct estruturaContador), 1, arquivoPosicao);
    //
  	// 	fclose(arquivoPosicao);
    // }

	// 	return 0;
	// }
