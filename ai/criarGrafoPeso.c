#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(){
  freopen("entrada.txt","r",stdin);
  freopen("saida.txt","w",stdout);

  int i, j;
  char temp[5];

	for(i = 0; i<11; i++)
	{
		for(j = 0; j<13; j++)
		{

			scanf("%s", temp);
			
			int op=3;
			
			if(strcmp("XXXX",temp)==0){
				printf("0,",i,j);
			}else if(strcmp("MMMM",temp)==0){
				printf("2,");
			}else{
				printf("1,");				
			}
		}
		printf("\n");
	}

return 0;
}
