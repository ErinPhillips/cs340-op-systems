// -----------------------------------
// CSCI 340 - Operating Systems I 
// Fall 2022 Erin Phillips
// utils.c implementation file
// Homework Assignment 1
//
// I certify that this work is entirely my own
// ------------------------------------------------------

// ------------------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <stdio.h>	   // standard I/O functions
#include <stdlib.h> 	 // atof()
#include <math.h>	     // math functions
#include "utils.h"	   // user defined functions

// -------------------- BEGIN read() --------------------
// Function implementation for reading a text file that defines 
// vectors. See assignment for format of this file.
// Arguments:   file_name   --- file name of vector text file
//              p_vec_array --- pointer to an array of v_structs
//              n           --- size of p_vec_array
// Return: The number (int type) of vectors read-in by function
int read(char* file_name, v_struct* p_vec_array, int n)
 {
  // define variables
  FILE *file;
  v_struct tempVec;
  double mag[n];
  double dir[n];
  int lineAcc = 0;
  char *line = NULL;
  char *cline;
  char *token;
  size_t m = 0;
  ssize_t len;

  // opening file 
  file = fopen(file_name, "r");
  if(file == NULL)
  { 
    fprintf(stderr, "Err opening %s\n", file_name);
    return 1;
  }

  // split by comma, convert to double, store in array
  while (lineAcc < n && (len = getline(&line, &m, file)) != -1)
  {
    line[len-1] = '\0';
    cline = strdup(line);
    if (cline[0] != '\0')
    {
      while ((token = strsep(&cline, ", ")))
      {
        if (token[0] != '\0')
        {
          //token holds the value of first field (magnitude)
          if (cline != NULL) mag[lineAcc] = atof(token);

          // token holds the value of the second field (direction)
          if (cline == NULL)
          {
            if (atof(token) < -360) dir[lineAcc] = atof(token) + 360;
            else if (atof(token) > 360) dir[lineAcc] = atof(token) - 360;
            else dir[lineAcc] = atof(token);
          }
        }
      }
    }

    lineAcc++;
    free(cline);
  }
    // store in v_struct
  for (int i = 0; i < n; i++)
  {
    tempVec.r = mag[i];
    tempVec.theta = dir[i];
    p_vec_array[i] = tempVec;

  }
  fclose(file);
  return lineAcc;
}

// -------------------- BEGIN x_component() --------------------
// Function implementation that uses the magnitude and direction values in
// the vector structure to compute the x component, i.e. r*cos(theta)
// Arguments:   p_vec_ptr --- points to a v_struct
// Return: The value (double type) that represents x component
double x_component(v_struct* p_vec_ptr)
{
  v_struct aVector;
  
  aVector = *p_vec_ptr;
  return (aVector.r * cos(aVector.theta * PI / 180));
}

// -------------------- BEGIN y_component() --------------------
// Function implementation that uses the magnitude and direction values in
// vector structure to compute the y component, i.e. r*sin(theta)
// Arguments:   p_vec_ptr --- points to a v_struct
// Return: The value (double type) that represents y component
double y_component(v_struct* p_vec_ptr)
{
  v_struct bVector;

  bVector = *p_vec_ptr;
  return (bVector.r * sin(bVector.theta * PI / 180));
}