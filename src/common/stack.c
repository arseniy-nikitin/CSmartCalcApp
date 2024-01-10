#include "stack.h"

Stack *create_stack(int max_elem) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  if (stack != NULL) {
    stack->operands = (double *)malloc(max_elem * sizeof(double));
    stack->state = (int *)malloc(max_elem * sizeof(int));
    stack->capacity = max_elem;
    stack->actual_size = 0;
    if (stack->operands == NULL || stack->state == NULL) destroy_stack(stack);
  }
  return stack;
}

void destroy_stack(Stack *stack) {
  if (stack != NULL) {
    if (stack->operands != NULL) {
      free(stack->operands);
      stack->operands = NULL;
    }
    if (stack->state != NULL) {
      free(stack->state);
      stack->state = NULL;
    }
    free(stack);
  }
}

int push(Stack *stack, double item, int is_num) {
  if (is_full(stack)) return STACK_ERR;
  stack->operands[stack->actual_size] = item;
  stack->state[stack->actual_size] = is_num;
  stack->actual_size++;
  return SUCCESS;
}

double pop(Stack *stack) {
  if (is_empty(stack)) return STACK_ERR;
  stack->actual_size--;
  return stack->operands[stack->actual_size];
}

double peek(Stack *stack) {
  if (is_empty(stack)) return STACK_ERR;
  return stack->operands[stack->actual_size - 1];
}

int get_state(Stack *stack) {
  if (is_empty(stack)) return STACK_ERR;
  return stack->state[stack->actual_size - 1];
}

int is_full(Stack *stack) { return stack->capacity == stack->actual_size; }

int is_empty(Stack *stack) { return stack->actual_size == 0; }

// Bullshit rewrite later
void reverse_stack(Stack *stack) {
  if (is_empty(stack)) return;

  int size = stack->actual_size;
  int i = 0;
  double *temp_operands = (double *)malloc(size * sizeof(double));
  int *temp_state = (int *)malloc(size * sizeof(int));

  if (temp_operands == NULL || temp_state == NULL) return;

  for (i = size - 1; i >= 0; i--) {
    temp_operands[size - i - 1] = stack->operands[i];
    temp_state[size - i - 1] = stack->state[i];
  }

  for (i = 0; i < size; i++) {
    stack->operands[i] = temp_operands[i];
    stack->state[i] = temp_state[i];
  }

  // Free the allocated memory
  free(temp_operands);
  free(temp_state);
}
