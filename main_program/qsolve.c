#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "qsolve.h"
#include <errno.h>
#include <ctype.h>
#include <float.h>

#define NLINE 1024 
#define MINVALUE 0
int enableLogs = 0;

int qsMain(){
  double *a = malloc(sizeof(double));
  double *b = malloc(sizeof(double));
  double *c = malloc(sizeof(double));
  double *x1 = malloc(sizeof(double));
  double *x2 = malloc(sizeof(double));
  char *line = malloc(NLINE);
  int getLineError;
  int solveError;
  int validateError;
  qsHello();
  getLineError = qsGetline(line, NLINE);
  while(strcmp(line, "quit") != 0) {		//program runs and repeats until user inputs "quit" into terminal
    if (strcmp(line, "help") == 0) {		//if help is entered qsHelp() is called and info inside qsHelp() is displayed
      qsHelp();
	} else if (strcmp(line, "log") == 0) {	//if user input is log, the log bit is switched to a 1 and the log is enabled. 
	  qsLogEnable();
    } else {
      validateError = qsValidate(line, NLINE, a, b, c); //variable validateError is equal to the result of qsValidate function and user input
	  if(validateError == 0 || validateError == -1) {	//if validateError is equal to 0 or -1 no errors and SolveError is initalized
        solveError = qsSolve(*a,*b,*c, x1, x2);			//solveError is set to the result of the equation 
	  }
	  if (getLineError == 1 || validateError == 1 || solveError == 1) {	 //if any of these variables equal 1 then qsErrors is called
        qsErrors(getLineError, validateError, solveError);				 // and the correct error is printed based on which variable is 1
        getLineError = 0;												 //else all variables are set to 0, no errors 
        validateError = 0;
        solveError = 0;
      }
      else {
        qsResults(*x1, *x2, solveError);	//if no errors are reported, the equation is executed and the results displayed. 
      }    
	}

    qsPutline(line, NLINE); //calls qsPutline which starts the whole program over asking for new user input. 
  }

  free(a);		//frees allocated space for dynamic variable 
  free(b);
  free(c);
  free(x1);
  free(x2);
  free(line);
  return 0;		//return zero, no errors
}

//informational method called upon at load to show commands to the user. returns 0
int qsHello() {
  printf("Welcome to the !False Software Quadratic Equation Solver v1.0\n");
  printf("For help type \"help\" into the interface\n");
  printf("To enable logging type \"log\" into the interface\n");
  printf("To exit type \"quit\" into the interface\n");
  return 0;
}

//method that asks for and receives input "a,b,c" from the terminal, if the end of file is reached returns 1 which prints an error
//else returns zero and the program continues. 

int qsGetline(char *line, int nline) {
	printf("Please enter a,b,c values separated only by a comma\n");
	if(scanf("%s", line) == EOF)
	  return 1;
	return 0;
}

//function that validates the input that was received from the user in qsGetline
int qsValidate(char *line, int nline, double *a, double *b, double *c) {
  char lineArray[NLINE];
  strncpy(lineArray, line, NLINE);
  char *ptr;
  ptr = strtok(lineArray, ",");		//seperates the line "input" entered by user and makes 3 seperate values to be parsed for a,b and c
  if (NULL == ptr){					//if ptr equals NULL, print an error message in the log, returns 1 and an error message
  									//is printed printed in the terminal. 
    qsLog("You did not enter a a: %s\n", ptr);
    return 1;
  }
  for(int i = 0; i < strlen(ptr); i++){
    if(isdigit(ptr[i]) == 0 && ptr[i] != '.' && ptr[i] != '-'){ //checks to see if user input for a is a digit, if not an error message
      qsLog("a is not a number a: %s\n", ptr);					//is input into the log and an error message to the terminal,returns 1 for error
      return 1;
    }
  }
  *a = atof(ptr);										//converts ptr "string" to a double
  if(*a > FLT_MAX || *a < -FLT_MAX || *a == MINVALUE){	//checks to see that user input for a is between the IEEE designated range for float
    return 1;											//returns 1 for invalid argument error to the terminal
  }
  qsLog("a: %f\n", *a);									//if all tests pass for a, a is printed to the log 
  ptr = strtok(NULL, ",");

  if (NULL == ptr){										//the process for a, lines 84 - 99 is repeated for user input b and c in lines
    qsLog("You did not enter b b: %s\n", ptr);			// 102 - 132, line 133 returns a zero because all tests for a,b,c have passed, no error
    return 1;
  }
  for(int i = 0; i < strlen(ptr); i++){
    if(isdigit(ptr[i]) == 0 && ptr[i] != '.' && ptr[i] != '-'){
      qsLog("b is not a number b: %s\n", ptr);
      return 1;
    }
  }
  *b = atof(ptr);
  if(*b > FLT_MAX || *b < -FLT_MAX){
    return 1;
  }
  qsLog("b: %f\n", *b);
  ptr = strtok(NULL, ",");
  if (NULL == ptr){
    qsLog("You did not enter c c: %s\n", ptr);
    return 1;
  }
  for(int i = 0; i < strlen(ptr); i++){
    if(isdigit(ptr[i]) == 0 && ptr[i] != '.' && ptr[i] != '-'){
      qsLog("c is not a number c: %s\n", ptr);
      return 1;
    }
  }
  *c = atof(ptr);
  if(*c > FLT_MAX || *c < -FLT_MAX){
    return 1;
  }
  qsLog("c: %f\n", *c);
  return 0;
}

int qsSolve(double a, double b, double c, double *x1, double *x2) {
  double discriminant = pow(b, 2) - (4 * a * c);
  double radical = sqrt(discriminant);
  if (discriminant < 0) //if discriminant is negative then there are only complex sol'ns
    return 1;
  qsLog("Value under the radical: %f\n", radical);
  double plus = (-1 * b) + radical;
  double minus = (-1 * b) - radical;
  *x1 = plus / (2 * a);
  *x2 = minus / (2 * a);
  qsLog("x1: %f\n", *x1);
  qsLog("x2: %f\n", *x2);
  if (discriminant == 0) //if discriminant is 0 then there is only 1 root
	return -1;
  return 0; //if discriminant is positive then there are 2 roots
}

//function for turning on and off the log bit, if log is entered into the terminal at start up the bit is set to 1 and logging turned on
//if log is typed again into the terminal bit is set back to zero and logging turned off
int qsLogEnable() {
	if (enableLogs == 1) {
		enableLogs = 0;
	} else {
  	enableLogs = 1;
	}  
	return 0;				//returns 0 no errors are printed. 
}

//function for printing the user input and value input if logging is enabled by the user 
int qsLog(char *string, double value) {
  if (enableLogs == 1)
    printf(string, value);
  return 0;					//returns 0 no errors are printed
}

//function that asks the user for another set of input to run the equation on starting the whole process again. 
int qsPutline(char *line, int nline) {
  printf("Please enter a,b,c values separated only by a comma\n");
	scanf("%s", line);
  return 0; //returns a zero, no errors
}

//function that prints a different error based on what each function return value is, if any of these 3 functions return a 1 that error
//is printed to the terminal, eg. validateError() returns a 1 then "your inputs are not valid is printed to terminal"
int qsErrors(int getLineError, int validateError, int solveError) {
  if (getLineError == 1){
    printf("There was an error reading your input\n");
  }
  if (validateError == 1){
    printf("Your inputs are not valid\n");
  }
  if (solveError == 1){
    printf("There are only complex solutions to this problem\n");
  }
  return 0; //returns a zero, no errors are printed
}

//function that prints the roots or root to the terminal after all inputs have been validated and ran through the equation
int qsResults(double x1, double x2, int solveError) {
  if(solveError == 0){												//if solveError equals zero "no errors" the roots are printed to terminal
    printf("First root:\t %5.8f\nSecond root:\t %5.8f\n", x1, x2);
  }
  if(solveError == -1){												//if solveError equals -1 there is only 1 real root which is printed 
	  printf("Only root:\t %5.8f\n", x2);
  }
  return 0;		//returns zero no errors are printed
}

//function to displays "help" to the user when help is entered into the command line 
int qsHelp() { 
  printf("\nEnter three decimal numbers seperated by a comma\nExample: \"1.23,3.54,-9.83\"\n"); 
  printf("Some set of numbers will give NO solution\n"); 
  printf("Good input: 1,3,-9 ---> This is good input because all of the values are numbers and do NOT contain any letter or quotations\n"); 
  printf("Good input: 2,-4,-3 ---> This is good input because the (b^2 -4ac) will not be negative and a is not 0\n"); 
  printf("Bad input: 1e300,2,9 ---> This is bad input because the 'a' value contains e which is not accepted as a number in C\n"); 
  printf("Bad input: 1,2,3,4 ---> This is bad input because there are 4 values instead of 3 values\n"); 
  printf("Bad input: '1',3,-9 ---> This is bad input because the 'a' value is put into quotations, which is not accepted as a number in C\n\n"); 
  return 0; //returns zero no errors are printed 
}
