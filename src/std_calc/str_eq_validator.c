#include "../smart_calc.h"

int is_func(double operator);

int str_eq_validator(char* str_eq) {
  int err_code = NO_ERR;
  Stack* buf = create_stack(255);
  if (buf == NULL) return ALLOC_ERR;
  str_to_stack(buf, str_eq, 0);
  int l_bracket_num = 0;
  int r_bracket_num = 0;
  int prev_num = 0;
  int prev_op = 0;
  double last_val = 0.0;
  if (get_state(buf) == 0 && buf->actual_size == 1) err_code = ARGS_ERR;
  if (get_state(buf) == 0 && buf->actual_size == 2 && !is_func(peek(buf)))
    err_code = ARGS_ERR;
  while (!is_empty(buf) && !err_code) {
    if (peek(buf) == L_BRACKET_ID) {
      l_bracket_num++;
    } else if (peek(buf) == R_BRACKET_ID) {
      r_bracket_num++;
    } else if (get_state(buf) == NUMBER) {
      if (prev_num != 1) {
        prev_num = 1;
        prev_op = 0;
      } else {
        err_code = ARGS_ERR;
      }
    } else {
      if (peek(buf) == UADD_ID || peek(buf) == USUB_ID) {
        if (prev_num == 1) err_code = ARGS_ERR;
      } else if (is_func(peek(buf))) {
        if (prev_num == 1 || is_func(last_val)) err_code = ARGS_ERR;
      } else if (prev_op != 1) {
        prev_num = 0;
        prev_op = 1;
      } else {
        err_code = ARGS_ERR;
      }
    }
    last_val = pop(buf);
  }
  if (prev_num != 1) err_code = ARGS_ERR;
  if (l_bracket_num != r_bracket_num) err_code = ARGS_ERR;
  destroy_stack(buf);
  return err_code;
}

int is_func(double operator) {
  int res = 0;
  res = (operator== COS_ID)     ? 1
        : (operator== SIN_ID)   ? 1
        : (operator== TAN_ID)   ? 1
        : (operator== ACOS_ID)  ? 1
        : (operator== ASIN_ID)  ? 1
        : (operator== ATAN_ID)  ? 1
        : (operator== SQRT_ID)  ? 1
        : (operator== LOG_ID)   ? 1
        : (operator== LOG10_ID) ? 1
                                : 0;
  return res;
}