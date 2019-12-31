#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
//gcc -o minmax MinMax.c -lm

int main(int argc, const char * argv[]) {
	printf("The double single-precision accuracy is: %zu\n",sizeof(double));
	printf("The double double-precision accuracy is: %d\n",DBL_DIG);	
	printf("The double min size is: %.10e\n", DBL_MIN);	
	printf("The double max size is: %.10e\n", DBL_MAX);
	
	return 0;
}
