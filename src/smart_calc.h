#ifndef SMART_CALC
#define SMART_CALC

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bank_calc/bank_calc.h"
#include "common/s21_strnstr.h"
#include "common/stack.h"

#ifndef EPSILON
#define EPSILON 0.0000001
#endif

#define NAN64 "0x7FF8000000000001"
#define MAX_STR_LEN 256

#ifndef NO_ERR
#define NO_ERR 0
#endif
#ifndef ALLOC_ERR
#define ALLOC_ERR 1
#endif
#ifndef ARGS_ERR
#define ARGS_ERR 2
#endif

#define L_BRACKET_ID 40.0
#define R_BRACKET_ID 41.0
#define ADD_ID 43.0
#define SUB_ID 45.0
#define MUL_ID 42.0
#define DIV_ID 47.0
#define POW_ID 94.0
#define MOD_ID 37.0
#define COS_ID 99.0
#define SIN_ID 115.0
#define TAN_ID 116.0
#define ACOS_ID 67.0
#define ASIN_ID 83.0
#define ATAN_ID 84.0
#define SQRT_ID 114.0
#define LOG_ID 108.0
#define LOG10_ID 76.0
#define UADD_ID 124.0
#define USUB_ID 126.0

int calc_label_eq(double* res, char* str_eq, double x_value);
int str_eq_validator(char* str_eq);
int str_to_stack(Stack* inf_stack, char* infix_str, double x_value);
int infix_to_rpn(Stack* rpn_stack, Stack* infix_stack);
int calc_rpn_eq(double* result, Stack* rpn_stack);

#endif