#include "../smart_calc.h"

int calc_label_eq(double* result, char* str_eq, double x_value) {
  if (str_eq_validator(str_eq)) return ARGS_ERR;
  Stack* infix = create_stack(255);
  Stack* rpn = create_stack(255);
  if (infix == NULL || rpn == NULL) {
    destroy_stack(infix);
    destroy_stack(rpn);
    return ALLOC_ERR;
  }
  str_to_stack(infix, str_eq, x_value);
  infix_to_rpn(rpn, infix);
  calc_rpn_eq(result, rpn);
  destroy_stack(infix);
  destroy_stack(rpn);
  return NO_ERR;
}