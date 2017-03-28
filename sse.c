#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h> 
#define N 400
#define M 400
//gcc -O2 -msse2 sse.c -o sse

void getWallTime(double *wct){
	struct timeval tp;
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+(tp.tv_usec/1000000.0));
	}


int main(){
	float *p , *np;//orismos twn pinakwn tou paliou kai tou kainouriou
	float c1, c2;//counter metavlhtes
	int i,j;//metavlhtes gia tis epanalhpseis
	double timeStart , timeEnd;	
	__m128 *vp, *vnp;
        __m128 tp1;//prosorinh metavlhth
  	__m128 tp2;//prosorinh metavlhth
  
	i = posix_memalign( (void **)&p, 16, N*M*sizeof(float) );
	if (i!=0) {
		printf ("Error\n");
		exit(1);
	}
	
	j = posix_memalign( (void **)&np, 16, M*N*sizeof(float) );
	if (j!=0) {
		free(p);
		printf ("Error\n");
		exit(1);
	}

	vp = (__m128 *)p;
	vnp = (__m128 *)np;


	int k1 = 0.5;// h metavlhth gia ton katallhlo pollaplasiasmo
	int k2 = 5.0;// h metavlhth gia ton katallhlo pollaplasiasmo
  	c1=0.0;//arxikopoihsh twn counter
	c2=0.0;//arxikopoihsh twn counter
  
	for(i=0;i<(N*M);i++){//arxikopoihsh twn 2 pinakwn
		p[i] = (float) rand();
		np[i] = 0.5;
	}

	
	
	getWallTime(&timeStart);
	
	for (j=0;j<M-2;j++){ 
		for (i=0;i<N-2;i++){
      
			tp1 = _mm_set_ps(p[(j+1)*N+i],p[(j+1)*N+(i+2)],p[(j+2)*N+(i+1)],p[(j+2)*N+(i+2)]);	//vazoume tis times twn 4 geitonikwn pixel	
			tp1 = _mm_mul_ps(tp1, *vnp);//pollaplasiazoume ta geitonika pixel me ton pinaka pou exei thn timh 0.5
    			c1 = c1 + tp1[x];//meta ton pollaplasiasmo prosthetoume tis times etsi wste na tis xrhsimopoihsoume meta 
      
    			tp2 =  _mm_set_ps(p[(j+2)*N+i],p[j*N+(i+1)],p[j*N+i],p[j*N+(i+2)]);	//vazoume tis times twn teleutaiwn 4 geitonikwn pixel
    			tp2 = _mm_mul_ps(tp2, *vnp);//pollaplasiazoume ta geitonika pixel me ton pinaka pou exei thn timh 0.5
	  		c2 = c2 + tp2[x];//meta ton pollaplasiasmo prosthetoume tis times etsi wste na tis xrhsimopoihsoume meta 
      
    			np[(j+1)*N+(i+1)]=(p[(j+1)*N+(i+1)] * 5.0) + c1 + c2 ;//vrhskoume thn timh tou mesaiou pixel , to pollaplasiazoume me to 5.0 kai prosthetoume ta counter

		}
	}
	getWallTime(&timeEnd);

printf("Done with %f time\n",timeEnd-timeStart);
printf("ola komple\n");
return 0;
}
