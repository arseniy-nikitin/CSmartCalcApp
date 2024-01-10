#include "../smart_calc.h"

void process_operation(Stack* stack, double operator);

double rpn_add(Stack* stack);
double rpn_sub(Stack* stack);
double rpn_mul(Stack* stack);
double rpn_div(Stack* stack);
double rpn_pow(Stack* stack);
double rpn_mod(Stack* stack);
double rpn_cos(Stack* stack);
double rpn_sin(Stack* stack);
double rpn_tan(Stack* stack);
double rpn_acos(Stack* stack);
double rpn_asin(Stack* stack);
double rpn_atan(Stack* stack);
double rpn_sqrt(Stack* stack);
double rpn_ln(Stack* stack);
double rpn_log(Stack* stack);
double rpn_uplus(Stack* stack);
double rpn_uminus(Stack* stack);

int calc_rpn_eq(double* result, Stack* rpn_stack) {
  if (rpn_stack == NULL) return ARGS_ERR;
  Stack* tmp_stack = create_stack(MAX_STR_LEN);
  if (tmp_stack == NULL) return ALLOC_ERR;
  while (!is_empty(rpn_stack)) {
    push(tmp_stack, peek(rpn_stack), get_state(rpn_stack));
    if (get_state(tmp_stack) != 1) process_operation(tmp_stack, pop(tmp_stack));
    pop(rpn_stack);
  }
  *result = pop(tmp_stack);
  destroy_stack(tmp_stack);
  return NO_ERR;
}

void process_operation(Stack* stack, double operator) {
  double res = (operator== ADD_ID)     ? rpn_add(stack)
               : (operator== SUB_ID)   ? rpn_sub(stack)
               : (operator== MUL_ID)   ? rpn_mul(stack)
               : (operator== DIV_ID)   ? rpn_div(stack)
               : (operator== MOD_ID)   ? rpn_mod(stack)
               : (operator== POW_ID)   ? rpn_pow(stack)
               : (operator== COS_ID)   ? rpn_cos(stack)
               : (operator== SIN_ID)   ? rpn_sin(stack)
               : (operator== TAN_ID)   ? rpn_tan(stack)
               : (operator== ACOS_ID)  ? rpn_acos(stack)
               : (operator== ASIN_ID)  ? rpn_asin(stack)
               : (operator== ATAN_ID)  ? rpn_atan(stack)
               : (operator== SQRT_ID)  ? rpn_sqrt(stack)
               : (operator== LOG_ID)   ? rpn_ln(stack)
               : (operator== LOG10_ID) ? rpn_log(stack)
               : (operator== UADD_ID)  ? rpn_uplus(stack)
               : (operator== USUB_ID)  ? rpn_uminus(stack)
                                       : nan(NAN64);
  push(stack, res, 1);
}

double rpn_add(Stack* stack) {
  double b = pop(stack);
  double a = pop(stack);
  return a + b;
}

double rpn_sub(Stack* stack) {
  double b = pop(stack);
  double a = pop(stack);
  return a - b;
}

double rpn_mul(Stack* stack) {
  double b = pop(stack);
  double a = pop(stack);
  return a * b;
}

double rpn_div(Stack* stack) {
  double b = pop(stack);
  double a = pop(stack);
  if (fabs(b) < EPSILON) return nan(NAN64);
  return a / b;
}

double rpn_pow(Stack* stack) {
  // a and b can be both zeroes
  // If b is fraction, then a can't be negative
  double b = pop(stack);
  double a = pop(stack);
  return pow(a, b);
}

double rpn_mod(Stack* stack) {
  double b = pop(stack);
  double a = pop(stack);
  if (fabs(b) < EPSILON) return nan(NAN64);
  return fmod(a, b);
}

double rpn_cos(Stack* stack) {
  double a = pop(stack);
  return cos(a);
}

double rpn_sin(Stack* stack) {
  double a = pop(stack);
  return sin(a);
}

double rpn_tan(Stack* stack) {
  double a = pop(stack);
  return tan(a);
}

double rpn_acos(Stack* stack) {
  double a = pop(stack);
  if (a < -1 || a > 1) return nan(NAN64);
  return acos(a);
}

double rpn_asin(Stack* stack) {
  double a = pop(stack);
  if (a < -1 || a > 1) return nan(NAN64);
  return asin(a);
}

double rpn_atan(Stack* stack) {
  double a = pop(stack);
  return atan(a);
}

double rpn_sqrt(Stack* stack) {
  double a = pop(stack);
  if (a < 0) return nan(NAN64);
  return sqrt(a);
}

double rpn_ln(Stack* stack) {
  double a = pop(stack);
  if (a < 0 || fabs(a) < EPSILON) return nan(NAN64);
  return log(a);
}

double rpn_log(Stack* stack) {
  double a = pop(stack);
  if (a < 0 || fabs(a) < EPSILON) return nan(NAN64);
  return log10(a);
}

double rpn_uplus(Stack* stack) {
  double a = pop(stack);
  return a * fabs(1.0);
}

double rpn_uminus(Stack* stack) {
  double a = pop(stack);
  return a * (-1.0);
}
