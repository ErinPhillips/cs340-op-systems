// ------------------------------------------------------
// CSCI 340 - Operating Systems I 
// Fall 2022 Erin Phillips
// utils.h function prototype file
// Homework Assignment 1
//
// I certify that this work is entirely my own
// ------------------------------------------------------

// ------------------------------------------------------
#define PI    3.14159265  // define of constant PI
#define DEBUG 0		  // 1 turns on debug printf(); 0 turns debugging off
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ------------------------------------------------------
// C-Style data structure to hold vector magnitude, r, 
// and direction, theta. Note: theta is in degrees
//
typedef struct {
  double r;	// magnitude value
  double theta;	// direction value (in degrees)
} v_struct;

// ------------------------------------------------------
// Function prototype for reading a text file that defines vectors.
int read(char* file_name, v_struct* p_vec_array, int n);

// ------------------------------------------------------
// Function prototype that uses the magnitude and direction values in
// the vector structure to compute the x component, i.e. r*cos(theta)
double x_component(v_struct* p_vec_ptr);

// ------------------------------------------------------
// Function prototype that uses the magnitude and direction values in
// vector structure to compute the y component, i.e. r*sin(theta)

double y_component(v_struct* p_vec_ptr);
