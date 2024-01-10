#include "../smart_calc.h"

double get_value(char** src);
double get_operator(char** src, Stack* stack);

int str_to_stack(Stack* stack, char* str, double x_value) {
  if (stack == NULL || str == NULL) return ARGS_ERR;
  while (*str && !is_full(stack)) {
    if (*str == ' ') {
      str++;
      continue;
    } else if (isdigit(*str)) {
      push(stack, get_value(&str), 1);
    } else if (*str == 'x') {
      str++;
      push(stack, x_value, 1);
    } else if (*str == '(') {
      push(stack, L_BRACKET_ID, 0);
      str++;
    } else if (*str == ')') {
      push(stack, R_BRACKET_ID, 0);
      str++;
    } else {
      double operator= get_operator(&str, stack);
      push(stack, operator, 0);
    }
  }
  reverse_stack(stack);
  return NO_ERR;
}

double get_value(char** src) {
  double res = atof(*src);
  int dot = 0;
  while ((isdigit(**src) || **src == '.') && dot < 2) {
    if (**src == '.') dot++;
    *src += 1;
  }
  return res;
}

double get_operator(char** src, Stack* stack) {
  double res = 0;
  char buf[5] = {0};
  strncpy(buf, *src, 4);
  int unary_condition =
      get_state(stack) != NUMBER && peek(stack) == L_BRACKET_ID;
  *src += (s21_strnstr(buf, "(", 1)) ? (res = L_BRACKET_ID, 1)
          : (s21_strnstr(buf, "+", 1) && unary_condition) ? (res = UADD_ID, 1)
          : (s21_strnstr(buf, "+", 1))                    ? (res = ADD_ID, 1)
          : (s21_strnstr(buf, "-", 1) && unary_condition) ? (res = USUB_ID, 1)
          : (s21_strnstr(buf, "-", 1))                    ? (res = SUB_ID, 1)
          : (s21_strnstr(buf, "*", 1))                    ? (res = MUL_ID, 1)
          : (s21_strnstr(buf, "/", 1))                    ? (res = DIV_ID, 1)
          : (s21_strnstr(buf, "%", 1))                    ? (res = MOD_ID, 1)
          : (s21_strnstr(buf, "^", 1))                    ? (res = POW_ID, 1)
          : (s21_strnstr(buf, "ln", 2))                   ? (res = LOG_ID, 2)
          : (s21_strnstr(buf, "log", 3))                  ? (res = LOG10_ID, 3)
          : (s21_strnstr(buf, "cos", 3))                  ? (res = COS_ID, 3)
          : (s21_strnstr(buf, "sin", 3))                  ? (res = SIN_ID, 3)
          : (s21_strnstr(buf, "tan", 3))                  ? (res = TAN_ID, 3)
          : (s21_strnstr(buf, "acos", 4))                 ? (res = ACOS_ID, 4)
          : (s21_strnstr(buf, "asin", 4))                 ? (res = ASIN_ID, 4)
          : (s21_strnstr(buf, "atan", 4))                 ? (res = ATAN_ID, 4)
          : (s21_strnstr(buf, "sqrt", 4))                 ? (res = SQRT_ID, 4)
                                                          : 0;
  return res;
}