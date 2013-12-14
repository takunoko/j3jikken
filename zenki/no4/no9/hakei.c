#include<stdio.h>
#include<math.h>

int main(void){
	int i;
	for(i=0; i<31; i++){
		printf("%d : %f\n",i,125+125*sin(i*3.14159265358979323846264338/15));
	}

	return 0;
}

