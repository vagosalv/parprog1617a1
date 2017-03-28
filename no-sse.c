// your C program without sse instructions

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 100
#define M 100
//gcc -O2 no-sse.c -o no-sse
void getWallTime(double *wct){
	struct timeval tp;//domh tou system
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+(tp.tv_usec/1000000.0));
	}

int main()
{
	float *p , *np;//oi 2 pinakes , o palios kai o kainourios 
	double timeStart , timeEnd;

	p = (float *) malloc(N*M* sizeof(float));//desmeush mnhmhs kai elenxos
	if(p == NULL){
		exit(1);
	}

	np = (float *) malloc(N*M* sizeof(float));//desmeush mnhmhs kai elenxos
	if(np == NULL){
		exit(1);
	}


	int i,j;//oi metavlhtes gia thn epanalhpsh
	int k1 = 0.5;//h metavlhth gia ton pollaplasiasmo me ta guro pixel
	int k2 = 5.0;//h metavlhth gia ton pollaplasiasmo me to mesaio pixel
	
	for(i=0;i<N*M;i++){//arxikopoihsh pinakwn
		p[i] =  (float) rand();
		np[i] = p[i];
	}

	getWallTime(&timeStart);
	
	//h parakatw praksh prosthetei ta aparaithta pixel kai tautoxrona ta pollaplasiazei me thn katallhlh metavlhth (0.5 h 5.0)
	for (j=0;j<M-2;j++){ 
		for (i=0;i<N-2;i++){
		np[(j+1)*N+(i+1)]= (p[(j+1)*N+(i+1)]*k2)+ (p[(j+1)*N+i]*k1) +(p[(j+1)*N+(i+2)]*k1) +(p[(j+2)*N+(i+1)]*k1) +(p[(j+2)*N+(i+2)]*k1) +(p[(j+2)*N+i]*k1) +(p[j*N+(i+1)]*k1) +(p[j*N+i]*k1) + (p[j*N+(i+2)]*k1);  
		}
	}


	getWallTime(&timeEnd);

	
	printf("Done with %f time\n",timeEnd-timeStart);
	free(p);
	free(np);

return 0;
}
