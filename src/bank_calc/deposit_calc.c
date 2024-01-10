#include "bank_calc.h"

int get_rate(char* src, int total_period);

int deposit_calc(Stack* res, double total_deposit, double period,
                 double profit_rate, double tax_rate, double replenishments,
                 double withdrawals, char* replenishments_rate,
                 char* withdrawals_rate, char* pcf_rate, int profit_cap) {
  if (res == NULL) return ARGS_ERR;
  double TP = 0.0, TT = 0.0;
  double TB = total_deposit, PR = profit_rate / 100.0, TR = tax_rate / 100.0,
         R = replenishments, W = withdrawals;
  int P = (int)(period * (YEAR_DAYS / 12.0));
  int RR = get_rate(replenishments_rate, P), WR = get_rate(withdrawals_rate, P),
      PCFR = get_rate(pcf_rate, P);
  if (profit_cap == PAYMENT) {
    for (int i = 1; i <= P; i++) {
      if (RR && WR) {
        if (!(i % RR)) TB += R;
        if (!(i % WR)) TB -= W;
      }
      if (!(i % PCFR)) TP += TB * (PR * (double)PCFR / YEAR_DAYS);
    }
    TB += TP;
  } else if (profit_cap == CAPITALIZATION) {
    for (int i = 1; i <= P; i++) {
      if (RR && WR) {
        if (!(i % RR)) TB += R;
        if (!(i % WR)) TB -= W;
      }
      if (!(i % PCFR)) {
        double TMP = TB * (PR * (double)PCFR / YEAR_DAYS);
        TP += TMP;
        TB += TMP;
      }
    }
  }
  double TFP = TAX_FREE_PROFIT(TR);
  TT = TP > TFP ? (TP - TFP) * TR : 0.0;
  push(res, TP, 1), push(res, TT, 1), push(res, TB, 1);
  reverse_stack(res);
  return NO_ERR;
}

int get_rate(char* src, int total_period) {
  int res = -1;
  char buf[6] = {0};
  strncpy(buf, src, 5);
  res = (s21_strnstr(buf, " NONE", 5))   ? NONE
        : (s21_strnstr(buf, " ONCE", 5)) ? total_period
        : (s21_strnstr(buf, "ONE/Y", 5)) ? EVERY_YEAR
        : (s21_strnstr(buf, "TWO/Y", 5)) ? EVERY_HALF_YEAR
        : (s21_strnstr(buf, "ONE/Q", 5)) ? EVERY_QUARTAL
        : (s21_strnstr(buf, "ONE/M", 5)) ? EVERY_MONTH
        : (s21_strnstr(buf, "TWO/M", 5)) ? EVERY_HALF_MONTH
        : (s21_strnstr(buf, "ONE/W", 5)) ? EVERY_WEEK
        : (s21_strnstr(buf, "ONE/D", 5)) ? EVERY_DAY
                                         : -1;
  return res;
}