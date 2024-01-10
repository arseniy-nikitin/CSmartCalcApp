#include "../smart_calc.h"

void process_bracket_equation(Stack* dst, Stack* tmp);
void process_actual_operator(Stack* dst, Stack* tmp, double operator);
int get_priority(double operator);

int infix_to_rpn(Stack* rpn_stack, Stack* infix_stack) {
  if (rpn_stack == NULL || infix_stack == NULL) return ARGS_ERR;
  Stack* tmp_stack = create_stack(MAX_STR_LEN);
  if (tmp_stack == NULL) return ALLOC_ERR;
  while (!is_empty(infix_stack) && !is_full(rpn_stack)) {
    if (get_state(infix_stack) == NUMBER) {
      push(rpn_stack, pop(infix_stack), 1);
    } else if (peek(infix_stack) == L_BRACKET_ID) {
      push(tmp_stack, pop(infix_stack), 0);
    } else if (peek(infix_stack) == R_BRACKET_ID) {
      process_bracket_equation(rpn_stack, tmp_stack);
      pop(infix_stack);
    } else {
      process_actual_operator(rpn_stack, tmp_stack, pop(infix_stack));
    }
  }
  while (!is_empty(tmp_stack) && !is_full(rpn_stack))
    push(rpn_stack, pop(tmp_stack), 0);
  reverse_stack(rpn_stack);
  destroy_stack(tmp_stack);
  return NO_ERR;
}

void process_bracket_equation(Stack* dst, Stack* tmp) {
  while (peek(tmp) != L_BRACKET_ID && !is_empty(tmp)) push(dst, pop(tmp), 0);
  if (peek(tmp) == L_BRACKET_ID) pop(tmp);
}

void process_actual_operator(Stack* dst, Stack* tmp, double operator) {
  while (!is_empty(tmp) && get_priority(peek(tmp)) >= get_priority(operator))
    push(dst, pop(tmp), 0);
  push(tmp, operator, 0);
}

int get_priority(double operator) {
  int res = 0;
  res = (operator== L_BRACKET_ID)   ? 1
        : (operator== R_BRACKET_ID) ? 1
        : (operator== ADD_ID)       ? 2
        : (operator== SUB_ID)       ? 2
        : (operator== MUL_ID)       ? 3
        : (operator== DIV_ID)       ? 3
        : (operator== MOD_ID)       ? 3
        : (operator== POW_ID)       ? 4
        : (operator== UADD_ID)      ? 5
        : (operator== USUB_ID)      ? 5
        : (operator== COS_ID)       ? 6
        : (operator== SIN_ID)       ? 6
        : (operator== TAN_ID)       ? 6
        : (operator== ACOS_ID)      ? 6
        : (operator== ASIN_ID)      ? 6
        : (operator== ATAN_ID)      ? 6
        : (operator== SQRT_ID)      ? 6
        : (operator== LOG_ID)       ? 6
        : (operator== LOG10_ID)     ? 6
                                    : 0;
  return res;
}