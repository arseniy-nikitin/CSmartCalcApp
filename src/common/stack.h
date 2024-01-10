#ifndef STACK
#define STACK

#include <stdlib.h>

#define SUCCESS 1
#define STACK_ERR 0

#define NUMBER 1
#define OPERATOR 0

typedef struct {
  double *operands;
  int *state;
  int capacity;
  int actual_size;
} Stack;

Stack *create_stack(int max_elem);
void destroy_stack(Stack *stack);
int push(Stack *stack, double item, int is_num);
double pop(Stack *stack);
double peek(Stack *stack);
int get_state(Stack *stack);
int is_full(Stack *stack);
int is_empty(Stack *stack);

// Bullshit rewrite later
void reverse_stack(Stack *stack);

#endif