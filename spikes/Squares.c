#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//gcc -o squares Squares.c -lm

int main(int argc,const char * argv[]) {
    int a = atoi(argv[1]);//a in line
    int b = atoi(argv[2]);//b in line
    int c = atoi(argv[3]);//c in line

	float inTheRoot=b*b-(4*a*c);//what's under the square root in the equation
    if (inTheRoot>0.0) {//real roots
        float negative=(-b - sqrt(inTheRoot))/(2*a);
        float positive=(-b + sqrt(inTheRoot))/(2*a);
        printf("The negative root is: %f and postive root is: %f\n",negative,positive);
    } 
	else if (inTheRoot<0.0) {//not real roots
		float imaginaryNumber= sqrt(-inTheRoot);		
		float real=-b/(2*a);
        printf("The imaginary root is: %f and real root is: %f\n",imaginaryNumber,real);
	} 
	else {//for the single root
		float singleRoot=-b/(2*a);
        printf("The singleRoot root is: %f\n",singleRoot);	
	}

	return 0;
}
