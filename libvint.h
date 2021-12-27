#ifndef LIBVINT_H
#define LIBVINT_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>

#define BITS_PER_VBYTE 7
#define END_MARKER 0x80

typedef uint8_t vbyte;
typedef vbyte * vint;

/* 
 * Creates a new zero-initialized vint variable.
 */
vint vint_new(void);

/* 
 * Creates a new vint variable and sets its value. 
 */
vint vint_from_uint(uint64_t value);

/* 
 * Creates a new vint variable and sets its value from a string of 
 * digits. Underscores are allowed in the digit string.
 */
//TODO
vint vint_from_str(char * value);

/* 
 * Returns the size of the vint variable as a number of vbytes. 
 */
int vint_get_size(vint vnum);

/* 
 * Changes the size of a vint variable in place. 
 */
void vint_resize(vint * vnum, int req_vbytes);

/* 
 * Creates a new copy of a vint variable. Data is copied into the new 
 * copy. 
 */
int vint_deepcopy(vint * from, vint * to);

/* 
 * Erases a vint variable from memory. 
 */
bool vint_erase(vint vnum);

/* 
 * Adds two vint variables. Result is returned as a new vint 
 * variable. 
 */
vint vint_add(vint vnum_a, vint vnum_b);

/* 
 * Shifts the bits of a vint variable. Positive amount signifies left
 * shifting and negative right shifting. 
 */
void vint_bitshift(vint * vnum, int amount);

/* 
 * Prints the bitwise representation of a vint variables. Bits are 
 * printed with the most significant bit on the left. 
 */
void vint_print_bits(vint vnum);

/*
 * Multiplies two vint variables. Result is returned as a new vint
 * variable.
 */
vint vint_multiply(vint vnum_a, vint vnum_b);

#endif



























