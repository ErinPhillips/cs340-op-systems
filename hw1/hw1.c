// ------------------------------------------------------
// CSCI 340 - Operating Systems I 
// Fall 2022 Erin Phillips
// hw1.c main implementation
// Homework Assignment 1
//
// I certify that this work is entirely my own
// ------------------------------------------------------

// ------------------------------------------------------
// These are the ONLY libraries that can be 
// used. UNDER NO CIRCUMSTANCES can additional 
// libraries be included!
#include <stdio.h>	// I/O functions
#include <stdlib.h> 	// atof() function
#include <math.h>	// math functions (eg. sin(), cos())
#include "utils.h"	// user defined functions, constants, and data types

// ------------------------------------------------------
// Define constants
#define TOTAL_VECS 10	// constant that defines the total number 
			// of vectors, i.e. magnitude,direction
			// pairs, in the vectors text file. DON'T
			// CHANGE!

// ------------------------------------------------------
// Main function 
// Arguments:	argc --- number of arguments suppled by user
//		argv --- array of argument values
int main(int argc, char** argv) 
{
  // Define variables
  v_struct vecArr[TOTAL_VECS];
  v_struct *p = vecArr;
  int numVecs;
  int i;

  // Read vectors defined in the text file specified in argc[1]
  numVecs = read(argv[1], p, TOTAL_VECS);

  // Loop through array of vector structs and print to console
  for (i = 0; i < numVecs; i++)
  {
    // using two print statements as to not have a long string
    // of code. 
    printf("r = %6.2f, theta = %6.2f deg, %5.2f rad, ",
      vecArr[i].r, vecArr[i].theta, vecArr[i].theta * PI /180);
    printf("x_comp = %6.2f, y_comp = %6.2f\n", 
      x_component(&p[i]), y_component(&p[i]));
  }
  return 0;
}