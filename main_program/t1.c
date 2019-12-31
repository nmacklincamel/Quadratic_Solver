/*
* t1.c
* Unit tests for quad_roots()
* solves a * x^2 + b x + c = 0
*   for the roots
* x1 and x2
* *
* This uses the qsolve_sqrt() which calls the system sqrt()
*/
#include <stdlib.h>
#include "cunit.h"
#include "qsolve.h"


int main() {
double a;
double b;
double c;

double x1; //first root
double x2; //second root

double initialX1;
double initialX2;

int	ret;     // return value from qsolve


// initialize the unit testing framework
cunit_init();

// A "good" unit test, need to allow for round off!
// qsolve_roots() passes this one. ;-)
// This allows about one base 10 least significant digit of error
// (x - x1)*(x - x2) = 0
initialX1 = 3.1;
initialX2 = 3.3;
a = 1.0;
b = -initialX1 + -initialX2;
c = initialX1*initialX2;
ret = qsSolve(a,b,c,&x1,&x2);
assert_eq("ret",ret,0);
assert_feqrerr("x1",x1, initialX2, 10.0*cunit_dmacheps );
assert_feqrerr("x2",x2, initialX1, 10.0*cunit_dmacheps );

initialX1 = 0.436;
initialX2 = 0.541;
a = 1.0;
b = -initialX1 + -initialX2;
c = initialX1*initialX2;
ret = qsSolve(a,b,c,&x1,&x2);
assert_eq("ret",ret,0);
assert_feqrerr("x1",x1, initialX2, 10.0*cunit_dmacheps );
assert_feqrerr("x2",x2, initialX1, 10.0*cunit_dmacheps );


a = 1.0;
b = 3.0;
c = -9.0;
ret = qsSolve(a,b,c,&x1,&x2);
assert_eq("ret",ret,0);
assert_feq("x1",x1,1.8541019662496847);
assert_feq("x2",x2,-4.8541019662496847);

a = 1.0;
b = 1.867598426542545338265;
c = -2.645116468741768724468;
ret = qsSolve(a,b,c,&x1,&x2);
assert_eq("ret",ret,0);
assert_feqrerr("x1",x1,0.94159340, 10.0*cunit_dmacheps);
assert_feqrerr("x2",x2,-2.80919182, 10.0*cunit_dmacheps);

exit(0);
}
