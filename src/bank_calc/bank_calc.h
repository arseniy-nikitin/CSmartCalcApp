#ifndef BANK_CALC
#define BANK_CALC

#include <math.h>
#include <string.h>

#include "../common/s21_strnstr.h"
#include "../common/stack.h"

#ifndef NO_ERR
#define NO_ERR 0
#endif
#ifndef ARGS_ERR
#define ARGS_ERR 2
#endif

#define ANNUITY 0
#define DIFFERENTIATED 1

#define PAYMENT 0
#define CAPITALIZATION 1

#ifndef EPSILON
#define EPSILON 0.0000001
#endif

#define TAX_FREE_PROFIT(val) (1000000.0 * (val))

#define YEAR_DAYS 365.0
#define YEAR_MONTH 12.0
#define MONTH_DAYS 30.0

#define NONE 0
#define EVERY_YEAR 366
#define EVERY_HALF_YEAR 183
#define EVERY_QUARTAL 91
#define EVERY_MONTH 30
#define EVERY_HALF_MONTH 15
#define EVERY_WEEK 7
#define EVERY_DAY 1

int credit_calc(Stack* res, double total_credit, double period,
                double percentage, int type);
int deposit_calc(Stack* res, double total_deposit, double period,
                 double profit_rate, double tax_rate, double replenishments,
                 double withdrawals, char* replenishments_rate,
                 char* withdrawals_rate, char* pcf_rate, int profit_cap);

#endif